/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CallGenerator.cpp
 * Author: bruno
 * 
 * Created on August 17, 2018, 10:53 PM
 */

#include "../../include/Calls/CallGenerator.h"

#include "../../include/SimulationType/SimulationType.h"
#include "../../include/Structure/Topology.h"
#include "../../include/Data/Parameters.h"
#include "../../include/Calls/Traffic.h"
#include "../../include/Calls/Call.h"

std::default_random_engine CallGenerator::random_generator(0);

CallGenerator::CallGenerator(SimulationType* simulType) 
:simulType(simulType), topology(simulType->GetTopology()), 
data(simulType->GetData()), traffic(simulType->GetTraffic()),
networkLoad(0.0) {
    this->uniformNodeDistribution = std::uniform_int_distribution<int>
    (0, this->topology->GetNumNodes() - 1);
    this->uniformTrafficDistribution = std::uniform_int_distribution<int>
    (0, this->traffic->GetVecTraffic().size() - 1);
    this->exponencialMuDistribution = std::exponential_distribution<double>
    (1.0L / this->simulType->GetParameters()->GetMu());
}

CallGenerator::~CallGenerator() {
    
}

void CallGenerator::GenerateCall() {
    unsigned int auxIndexOrNode = uniformNodeDistribution(random_generator);
    unsigned int auxIndexDeNode;
    
    do{
        auxIndexDeNode = uniformNodeDistribution(random_generator);
    }while(auxIndexOrNode == auxIndexDeNode);
    
    unsigned int auxIndexTraffic = uniformTrafficDistribution(random_generator);
    
    //Create the call with the above parameters.
    //Change this current creation.
    Call* call = new Call( this->simulType->GetTopology()->
    GetNode(auxIndexOrNode), this->simulType->GetTopology()->
    GetNode(auxIndexDeNode),  this->simulType->GetTraffic()->
    GetTraffic(auxIndexTraffic));
}

SimulationType* CallGenerator::GetSimulType() const {
    return simulType;
}

void CallGenerator::SetSimulType(SimulationType* simulType) {
    this->simulType = simulType;
}

double CallGenerator::GetNetworkLoad() const {
    return networkLoad;
}

void CallGenerator::SetNetworkLoad(double networkLoad) {
    assert(networkLoad >= 0.0);
    this->networkLoad = networkLoad;
    
    this->exponencialHDistribution = std::exponential_distribution<double>
    (networkLoad);
}
