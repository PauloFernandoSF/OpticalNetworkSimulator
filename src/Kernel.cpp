/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Kernel.cpp
 * Author: bruno
 * 
 * Created on August 2, 2018, 3:42 PM
 */

#include "../include/Kernel.h"

#include "../include/SimulationType/SimulationType.h"
#include "../include/SimulationType/MultiLoadSimulation.h"

Kernel::Kernel(int numSimulations)
:numberSimulations(numSimulations),
simulations(0) {
    
}

Kernel::~Kernel() {
    
    for(auto it : simulations) {
        it.reset();
    }
}

void Kernel::Run() {
    
    Pre_Simulation();
    Simulation();
    Pos_Simulation();
}

void Kernel::Pre_Simulation() {
    
    //Create the simulations vector
    for(unsigned int a = 1; a <= this->numberSimulations; ++a){
        simulations.push_back(std::make_shared<MultiLoadSimulation> (a));
    }
    
    for(auto it : simulations){
        it->Load();
        it->AdditionalSettings();
    }
    
    for(auto it : simulations){
        it->Print();
    }
}

void Kernel::Simulation() {
    
    for(auto it : this->simulations){
        it->Run();
    }
}

void Kernel::Pos_Simulation() {
    
}