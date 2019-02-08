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
#include "../../include/ResourceAllocation/SA.h"
#include "../../include/Data/Options.h"
#include "../../include/Data/Parameters.h"
#include "../../include/Calls/Call.h"
#include "../../include/ResourceAllocation/Modulation.h"

ResourceAlloc::ResourceAlloc(SimulationType *simulType)
:simulType(simulType), topology(nullptr), routing(nullptr), specAlloc(nullptr),
allRoutes(0), resourceAllocOrder(0) {
    
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
            if(!this->CheckResourceAllocOrder(call))
                this->RSA(call);
            else
                this->SAR(call);
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

void ResourceAlloc::SAR(Call* call) {
    assert(this->simulType->GetOptions()->GetSpecAllOption() == SpecAllFF);
    this->modulation->SetModulationParam(call);
    this->routing->RoutingCall(call);
    bool allocFound = false;
    
    unsigned int size = this->topology->GetNumSlots() - call->GetNumberSlots();
    unsigned int numRoutes = call->GetNumRoutes();
    
    for(unsigned int a = 0; a <= size; a++){
        
        for(unsigned int b = 0; b < numRoutes; b++){
            call->SetRoute(call->GetRoute(b));
            
            if(this->topology->CheckSlotsDisp(call->GetRoute(), a, a + 
               call->GetNumberSlots() - 1)){
                call->SetFirstSlot((int) a);
                call->SetLastSlot(a + call->GetNumberSlots() - 1);
                call->ClearTrialRoutes();
                call->SetStatus(Accepted);
                allocFound = true;
                break;
            }
        }
        if(allocFound)
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
            break;
        case RoutingYEN:
            this->routing->YEN();
            break;
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

bool ResourceAlloc::CheckResourceAllocOrder(Call* call) {
    return this->resourceAllocOrder.at(call->GetOrNode()->GetNodeId()*
    this->topology->GetNumNodes()+call->GetDeNode()->GetNodeId());
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

std::vector<bool> ResourceAlloc::GetResourceAllocOrder() const {
    return resourceAllocOrder;
}

void ResourceAlloc::SetResourceAllocOrder(std::vector<bool> resourceAllocOrder) {
    this->resourceAllocOrder = resourceAllocOrder;
}
