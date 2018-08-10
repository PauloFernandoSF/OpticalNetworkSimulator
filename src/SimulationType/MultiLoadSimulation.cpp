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

MultiLoadSimulation::MultiLoadSimulation(unsigned int simulIndex)
:SimulationType(simulIndex){
    
}

MultiLoadSimulation::~MultiLoadSimulation() {
    
}

void MultiLoadSimulation::Run() {

}

void MultiLoadSimulation::Load() {

}

void MultiLoadSimulation::LoadFile() {
    SimulationType::LoadFile();
    
    //Additional load functions
    //singular to that simulation
}

void MultiLoadSimulation::Print() {

}

void MultiLoadSimulation::Save() {

}

void MultiLoadSimulation::Help() {

}
