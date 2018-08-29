/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MultiLoadSimulation.cpp
 * Author: bruno
 * 
 * Created on August 8, 2018, 7:18 PM
 */

#include "../../include/SimulationType/MultiLoadSimulation.h"

#include "../../include/Data/Parameters.h"
#include "../../include/Calls/CallGenerator.h"
#include "../../include/Calls/Traffic.h"
#include "../../include/Structure/Topology.h"

MultiLoadSimulation::MultiLoadSimulation(unsigned int simulIndex)
:SimulationType(simulIndex){
    
}

MultiLoadSimulation::~MultiLoadSimulation() {
    
}

void MultiLoadSimulation::Run() {
    unsigned int numLoadPoints = this->GetParameters()->
    GetNumberLoadPoints();
    
    for(unsigned int a = 0; a < numLoadPoints; ++a){       
        this->SetCallGenerator(std::make_shared<CallGenerator>(this));
        this->GetCallGenerator()->SetNetworkLoad
        (this->GetParameters()->GetLoadPoint(a));
        this->GetTopology()->Initialise();
        
        //Continue calling functions from CallGenerator object.
    }
}

void MultiLoadSimulation::Load() {
    SimulationType::Load();
}

void MultiLoadSimulation::LoadFile() {
    SimulationType::LoadFile();
    
    //Additional load functions
    //singular to that simulation
}

void MultiLoadSimulation::Print() {
    this->Help();
    SimulationType::Print();
}

void MultiLoadSimulation::Save() {

}

void MultiLoadSimulation::Help() {
    std::cout << "MULTIPLE LOADS SIMULATION" << std::endl
              << "This type of simulation varies the network load "
              << "and analyzes the network performance. "
              << std::endl << std::endl;
}
