/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RSA.cpp
 * Author: BrunoVinicius
 * 
 * Created on November 19, 2018, 7:56 PM
 */

#include "../../include/RSA/RSA.h"
#include "../../include/SimulationType/SimulationType.h"
#include "../../include/Structure/Topology.h"
#include "../../include/RSA/Routing.h"
#include "../../include/RSA/SA.h"
#include "../../include/Data/Options.h"
#include "../../include/Calls/Call.h"

RSA::RSA(SimulationType *simulType)
:simulType(simulType), topology(nullptr), allRoutes(0), routing(nullptr),
specAlloc(nullptr) {
    
}

RSA::~RSA() {
    
    for(auto it1 : this->allRoutes){
        for(auto it2 : it1){
            it2.reset();
        }
    }
    this->allRoutes.clear();
    
    this->routing.reset();
    this->specAlloc.reset();
}

void RSA::Load() {
    this->topology = this->simulType->GetTopology();
    
    unsigned int numNodes = this->topology->GetNumNodes();
    this->allRoutes.resize(numNodes*numNodes);
    
    this->routing = std::make_shared<Routing>(this, 
        this->simulType->GetOptions()->GetRoutingOption(), this->topology);
    
    this->specAlloc = std::make_shared<SA>(this, 
        this->simulType->GetOptions()->GetSpecAllOption(), this->topology);
}

void RSA::RSACall(Call* call) {
    this->routing->RoutingCall(call);
    
    if(call->IsThereTrialRoute()){
        do{
            call->SetRoute(call->PopTrialRoute());
            this->specAlloc->SpecAllocation(call);
            
            if(call->GetStatus() == Accepted)
                break;
                        
        }while(call->IsThereTrialRoute());
    }
}

void RSA::SetRoute(unsigned int orN, unsigned int deN, 
std::shared_ptr<Route> route) {
    this->ClearRoutes(orN, deN);
    this->AddRoute(orN, deN, route);
}

void RSA::SetRoutes(unsigned int orN, unsigned int deN, 
std::vector<std::shared_ptr<Route>> routes) {
    this->ClearRoutes(orN, deN);
    
    for(auto it : routes)
        this->AddRoute(orN, deN, it);
}

void RSA::AddRoute(unsigned int orN, unsigned int deN, 
std::shared_ptr<Route> route) {
    this->allRoutes.at(orN*this->topology->GetNumNodes() + deN)
                   .push_back(route);
}

void RSA::AddRoutes(unsigned int orN, unsigned int deN, 
std::vector<std::shared_ptr<Route>> routes) {
    
    for(auto it : routes)
        this->AddRoute(orN, deN, it);
}

void RSA::ClearRoutes(unsigned int orN, unsigned int deN) {
    
    for(auto it : this->allRoutes.at(orN*this->topology->GetNumNodes() + deN))
        it.reset();
    
    this->allRoutes.at(orN*this->topology->GetNumNodes() + deN).clear();
}

std::vector<std::shared_ptr<Route>> RSA::GetRoutes(unsigned int orN, 
unsigned int deN) {
    unsigned int numNodes = this->topology->GetNumNodes();
    
    return this->allRoutes.at(orN*numNodes + deN);
}

SimulationType* RSA::GetSimulType() const {
    return simulType;
}

void RSA::SetSimulType(SimulationType* simulType) {
    this->simulType = simulType;
}

Topology* RSA::GetTopology() const {
    return topology;
}

void RSA::SetTopology(Topology* topology) {
    this->topology = topology;
}
