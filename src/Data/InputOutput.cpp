/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InputOutput.cpp
 * Author: bruno
 * 
 * Created on August 8, 2018, 8:14 PM
 */

#include <iostream>

#include "../../include/Data/InputOutput.h"

#include "../../include/SimulationType/SimulationType.h"
#include "../../include/Structure/Topology.h"

InputOutput::InputOutput(SimulationType* simulType)
:simulType(simulType) {
}

InputOutput::~InputOutput() {
}

void InputOutput::LoadParameters(std::ifstream& parameters) {
    int auxInt = this->simulType->GetSimulationIndex();
    
    do{
        parameters.open("Files/Inputs/Parameters_" + 
        std::to_string(auxInt) + ".txt");
        
        if(!parameters.is_open()) {       
            std::cerr << "Wrong parameter file." << std::endl;
            std::cerr << "The file required is: Parameters_" << 
            auxInt << ".txt" << std::endl;
            std::cerr << "Fix the file then press 'Enter'" 
            << std::endl;
            
            std::cin.get();
        }

    }while(!parameters.is_open());
}

void InputOutput::LoadOptions(std::ifstream& options) {
    int auxInt = this->simulType->GetSimulationIndex();
    
    do{
        options.open("Files/Inputs/Options_" + 
        std::to_string(auxInt) + ".txt");
        
        if(!options.is_open()) {       
            std::cerr << "Wrong options file." << std::endl;
            std::cerr << "The file required is: Options_" 
            << auxInt << ".txt";
            std::cerr << "Fix the file then press 'Enter'" 
            << std::endl;
            
            std::cin.get();
        }

    }while(!options.is_open());
}

void InputOutput::LoadTopology(std::ifstream& topology) {
    std::string topologyName = 
    this->simulType->GetTopology()->GetNameTopology();
    
    do{
        topology.open("Files/Inputs/Topologies/" + 
        topologyName + ".txt");
        
        if(!topology.is_open()) {       
            std::cerr << "Wrong options file." << std::endl;
            std::cerr << "The file required is: " << topologyName << ".txt";
            std::cerr << "Fix the file then press 'Enter'" << std::endl;
            
            std::cin.get();
        }
    }while(!topology.is_open());
}

