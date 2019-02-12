/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GA_SingleObjective.cpp
 * Author: BrunoVinicius
 * 
 * Created on February 11, 2019, 10:53 PM
 */

#include "../../include/SimulationType/GA_SingleObjective.h"
#include "../../include/Algorithms/GA/GA_RsaOrder.h"
#include "../../include/SimulationType/SimulationType.h"
#include "../../include/Data/InputOutput.h"

GA_SingleObjective::GA_SingleObjective(unsigned int simulIndex) 
:SimulationType(simulIndex), gaAlgorithm(std::make_shared<GA_RsaOrder>(this)) {
    
}

GA_SingleObjective::~GA_SingleObjective() {
    
}

void GA_SingleObjective::Run() {
    unsigned int numGenerations = this->gaAlgorithm->GetNumberGenerations();
    this->gaAlgorithm->InitializePopulation();
    
    for(unsigned int a = 0; a < numGenerations; a++){
        
        this->GetInputOutput()->PrintProgressBar(a, numGenerations);
    }
    
    this->GetInputOutput()->PrintProgressBar(numGenerations, numGenerations);
}

void GA_SingleObjective::Load() {
    SimulationType::Load();
    this->gaAlgorithm->Initialize();
}

void GA_SingleObjective::LoadFile() {
    SimulationType::LoadFile();
    this->gaAlgorithm->Initialize();
}

void GA_SingleObjective::Print() {
    this->Help();
    SimulationType::Print();
}

void GA_SingleObjective::Save() {
    SimulationType::Save();
}

void GA_SingleObjective::Help() {
    std::cout << "GA SINGLE OBJECTIVE SIMULATION" << std::endl
              << "this type of simulation applies the genetic algorithm "
              << "for single objective. "
              << std::endl << std::endl;
}
