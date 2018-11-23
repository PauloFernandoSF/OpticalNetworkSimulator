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

RSA::RSA(SimulationType *simulType)
:simulType(simulType), topology(nullptr) {
    
}

RSA::RSA(const RSA& orig) {
}

RSA::~RSA() {
}

void RSA::SetRoute(unsigned int orN, unsigned int deN, 
std::shared_ptr<Route> route) {
    this->ClearRoutes(orN, deN);
    this->allRoutes.at(orN*this->topology->GetNumNodes() + deN)
                   .push_back(route);
}

void RSA::SetRoutes(unsigned int orN, unsigned int deN, 
std::vector<std::shared_ptr<Route> > routes) {
    this->ClearRoutes(orN, deN);
    
    for(auto it : routes){
        this->allRoutes.at(orN*this->topology->GetNumNodes() + deN)
                       .push_back(it);
    }
}

void RSA::ClearRoutes(unsigned int orN, unsigned int deN) {
    
    for(auto it : this->allRoutes.at(orN*this->topology->GetNumNodes() + deN)){
        it.reset();
    }
    
    this->allRoutes.at(orN*this->topology->GetNumNodes() + deN).clear();
}

std::vector<std::shared_ptr<Route> > RSA::GetRoutes(unsigned int orN, unsigned int deN) {
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
