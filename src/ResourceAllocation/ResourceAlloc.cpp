/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ResourceAlloc.cpp
 * Author: BrunoVinicius
 * 
 * Created on November 27, 2018, 8:33 PM
 */

#include "../../include/ResourceAllocation/ResourceAlloc.h"
#include "../../include/SimulationType/SimulationType.h"
#include "../../include/Structure/Topology.h"
#include "../../include/ResourceAllocation/Routing.h"
#include "../../include/ResourceAllocation/Route.h"
#include "../../include/ResourceAllocation/SA.h"
#include "../../include/Data/Options.h"
#include "../../include/Data/Parameters.h"
#include "../../include/Calls/Call.h"
#include "../../include/ResourceAllocation/Modulation.h"

ResourceAlloc::ResourceAlloc(SimulationType *simulType)
:simulType(simulType), topology(nullptr), routing(nullptr), specAlloc(nullptr),
allRoutes(0){
    
}

ResourceAlloc::~ResourceAlloc() {
    
    for(auto it1 : this->allRoutes){
        for(auto it2 : it1){
            it2.reset();
        }
    }
    this->allRoutes.clear();
    
    this->routing.reset();
    this->specAlloc.reset();
}

void ResourceAlloc::Load() {
    this->topology = this->simulType->GetTopology();
    unsigned int numNodes = this->topology->GetNumNodes();
    
    this->allRoutes.resize(numNodes*numNodes);
       
    this->routing = std::make_shared<Routing>(this, 
        this->simulType->GetOptions()->GetRoutingOption(), this->topology);
    
    this->specAlloc = std::make_shared<SA>(this, 
        this->simulType->GetOptions()->GetSpecAllOption(), this->topology);
    
    this->modulation = std::make_shared<Modulation>(this, 
        this->simulType->GetParameters()->GetSlotBandwidth());
    
    this->resourAllocOption = this->simulType->GetOptions()->
                                               GetResourAllocOption();
    
    this->phyLayerOption = this->simulType->GetOptions()->GetPhyLayerOption();
}

void ResourceAlloc::ResourAlloc(Call* call) {
    
    switch(this->resourAllocOption){
        case ResourAllocRSA:
            call->SetModulation(FixedModulation);
            this->RSA(call);
            break;
        case ResourAllocRMSA:
            this->RMSA(call);
            break;
        default:
            std::cerr << "Invalid resource allocation option" << std::endl;
    }
}

void ResourceAlloc::RSA(Call* call) {
    this->modulation->SetModulationParam(call);
    this->routing->RoutingCall(call);
    
    if(call->IsThereTrialRoute()){
        do{
            call->SetRoute(call->PopTrialRoute());
            
            if(!this->CheckOSNR(call))
                continue;
            
            this->specAlloc->SpecAllocation(call);
            
            if(this->topology->IsValidLigthPath(call)){
                call->ClearTrialRoutes();
                call->SetStatus(Accepted);
                break;
            }
        }while(call->IsThereTrialRoute());
    }
    
    if(!this->topology->IsValidLigthPath(call))
        call->SetStatus(Blocked);
}

void ResourceAlloc::RMSA(Call* call) {
    TypeModulation mod;
    
    for(mod = LastModulation; mod >= FirstModulation; 
                              mod = TypeModulation(mod-1)){
        call->SetModulation(mod);
        this->RSA(call);
        
        if(call->GetStatus() == Accepted)
            break;
    }
}

void ResourceAlloc::SetRoute(unsigned int orN, unsigned int deN, 
std::shared_ptr<Route> route) {
    this->ClearRoutes(orN, deN);
    this->AddRoute(orN, deN, route);
}

void ResourceAlloc::SetRoutes(unsigned int orN, unsigned int deN, 
std::vector<std::shared_ptr<Route>> routes) {
    this->ClearRoutes(orN, deN);
    
    for(auto it : routes)
        this->AddRoute(orN, deN, it);
}

void ResourceAlloc::AddRoute(unsigned int orN, unsigned int deN, 
std::shared_ptr<Route> route) {
    this->allRoutes.at(orN*this->topology->GetNumNodes() + deN)
                   .push_back(route);
}

void ResourceAlloc::AddRoutes(unsigned int orN, unsigned int deN, 
std::vector<std::shared_ptr<Route>> routes) {
    
    for(auto it : routes)
        this->AddRoute(orN, deN, it);
}

void ResourceAlloc::ClearRoutes(unsigned int orN, unsigned int deN) {
    
    for(auto it : this->allRoutes.at(orN*this->topology->GetNumNodes() + deN))
        it.reset();
    
    this->allRoutes.at(orN*this->topology->GetNumNodes() + deN).clear();
}

std::vector<std::shared_ptr<Route>> ResourceAlloc::GetRoutes(unsigned int orN, 
unsigned int deN) {
    unsigned int numNodes = this->topology->GetNumNodes();
    
    return this->allRoutes.at(orN*numNodes + deN);
}

bool ResourceAlloc::IsOfflineRouting() {
    switch(this->routing->GetRoutingOption()){
        case RoutingDJK:
        case RoutingYEN:
        case RoutingBSR:
            return true;
        default:
            return false;
    }
}

void ResourceAlloc::RoutingOffline() {
    switch(this->routing->GetRoutingOption()){
        case RoutingDJK:
            this->routing->Dijkstra();
            //this->SetInterferingRoutes();
            break;
        case RoutingYEN:
        case RoutingBSR:
        default:
            std::cerr << "Invalid offline routing option" << std::endl;
    }
}

bool ResourceAlloc::CheckOSNR(Call* call) {
    
    if(this->phyLayerOption == PhyLayerEnabled)
        if(!this->topology->CheckOSNR(call->GetRoute(), call->GetOsnrTh()))
            return false;
    
    return true;
}

SimulationType* ResourceAlloc::GetSimulType() const {
    return simulType;
}

void ResourceAlloc::SetSimulType(SimulationType* simulType) {
    this->simulType = simulType;
}

Topology* ResourceAlloc::GetTopology() const {
    return topology;
}

void ResourceAlloc::SetTopology(Topology* topology) {
    this->topology = topology;
}

void ResourceAlloc::SetInterferingRoutes(){
    std::shared_ptr<Route> routeAux, routeAux2;
    int nodeRoute[2], nodeRouteInt[2], totalRoutes = 0, countRoutes = 0;
    bool flag = true;
    
    /*Initialize vector of vector of route pointer for Interfering Routes*/
    for(int r = 1;r < this->allRoutes.size() - 1;r++){
        if(r%(this->topology->GetNumNodes() + 1) == 0)
            r += 1;
        totalRoutes = totalRoutes + allRoutes.at(r).size();
    }
    this->interRoutes.resize(totalRoutes); 
    /*Vary the first position of allRoutes*/
    for(unsigned int a = 1; a < allRoutes.size() - 1; a++){
      if(a%(this->topology->GetNumNodes() + 1) == 0)
            a += 1;
      /*Vary second position of allRoutes*/
      for(unsigned int e = 0;e < allRoutes.at(a).size();e++){  
        routeAux = this->allRoutes.at(a).at(e);
        /*Search links to verify interfering routes*/
        for(unsigned int b = 0; b < routeAux->GetNumHops() - 1; b++){
            nodeRoute[0] = routeAux->GetNode(b);
            nodeRoute[1] = routeAux->GetNode(b+1);
            /*Search in allRoutes to extract all interfering routes*/
            for(unsigned int c = 1; c < allRoutes.size() - 1; c++){
              if(c%(this->topology->GetNumNodes() + 1) == 0)
                 c += 1;
              for(unsigned int f = 0;f < allRoutes.at(c).size();f++){
                routeAux2 = allRoutes.at(c).at(f);
                if(routeAux == routeAux2)
                   continue;
                for(unsigned int d = 0; d < (routeAux2->GetNumHops()-1); d++){
                   nodeRouteInt[0] = routeAux2->GetNode(d);
                   nodeRouteInt[1] = routeAux2->GetNode(d+1);
                   if(nodeRoute[0]==nodeRouteInt[0] && 
                          nodeRoute[1]==nodeRouteInt[1]){
                      /*Verify if interfering route is already in interRoutes*/
                       for(unsigned int e = 0; e < interRoutes.at(countRoutes)
                               .size(); e++){
                          if(interRoutes.at(countRoutes).at(e) == routeAux2){
                              flag = false;
                              d = routeAux2->GetNumHops()-1;
                              break;
                          }
                       }
                       if(flag){
                         this->interRoutes.at(countRoutes).push_back(routeAux2);
                         break;
                       }
                       flag = true;
                   }
                }
              }
            }
        }
        countRoutes++;
      }
    }
}