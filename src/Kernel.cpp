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

Kernel::Kernel(int numSimulations)
:numberSimulations(numSimulations) {
    
}

Kernel::~Kernel() {
    
    for(auto it : simulations) {
        it->~SimulationType();
    }
}

void Kernel::Run() {
    
    Pre_Simulation();
    Simulation();
    Pos_Simulation();    
}

void Kernel::Pre_Simulation() {
    
    //Create the simulations vector
    
}

void Kernel::Simulation() {
    
}

void Kernel::Pos_Simulation() {
    
}

