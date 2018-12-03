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
#include "../../include/Data/Options.h"

InputOutput::InputOutput(SimulationType* simulType)
:simulType(simulType) {
    this->LoadLog(this->logFile);
    this->LoadResults(this->resultFile);
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
            std::cerr << "The file required is: Parameters_" 
                      << auxInt << ".txt" << std::endl;
            std::cerr << "Add/Fix the file then press 'Enter'" 
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
            std::cerr << "Add/Fix the file then press 'Enter'" 
                      << std::endl;
            
            std::cin.get();
        }

    }while(!options.is_open());
}

void InputOutput::LoadTopology(std::ifstream& topology) {
    std::string topologyName = 
    this->simulType->GetOptions()->GetTopologyName();
    
    do{
        topology.open("Files/Inputs/Topologies/" + 
        topologyName + ".txt");
        
        if(!topology.is_open()) {       
            std::cerr << "Wrong topology file." << std::endl;
            std::cerr << "The file required is: " 
                      << topologyName << ".txt";
            std::cerr << "Add/Fix the file then press 'Enter'" 
                      << std::endl;
            
            std::cin.get();
        }
    }while(!topology.is_open());
}

void InputOutput::LoadTraffic(std::ifstream& traffic) {
    std::string trafficName = 
    this->simulType->GetOptions()->GetTrafficName();
    
    do{
        traffic.open("Files/Inputs/Traffics/Traffic_" + 
        trafficName + ".txt");
        
        if(!traffic.is_open()) {       
            std::cerr << "Wrong traffic file." << std::endl;
            std::cerr << "The file required is: Traffic_" 
                      << trafficName << ".txt";
            std::cerr << "Add/Fix the file then press 'Enter'" 
                      << std::endl;
            
            std::cin.get();
        }
    }while(!traffic.is_open());
}

void InputOutput::LoadResults(std::ofstream& results) {
    unsigned int auxInt = this->simulType->GetSimulationIndex();
    
    do{
        results.open("Files/Outputs/" + std::to_string(auxInt) 
                     + "/Results.txt");
        
        if(!results.is_open()){
            std::cerr << "Wrong result file." << std::endl;
            std::cerr << "The folder required is: " << auxInt 
                      << "/" << std::endl;
            std::cerr << "Add/Fix the folder, then press 'Enter'"
                      << std::endl;
            
            std::cin.get();
        }
    }while(!results.is_open());
}

void InputOutput::LoadLog(std::ofstream& log) {
    unsigned int auxInt = this->simulType->GetSimulationIndex();
    
    do{
        log.open("Files/Outputs/" + std::to_string(auxInt) 
                     + "/Log.txt");
        
        if(!log.is_open()){
            std::cerr << "Wrong log file." << std::endl;
            std::cerr << "The folder required is: " << auxInt 
                      << "/" << std::endl;
            std::cerr << "Add/Fix the folder, then press 'Enter'"
                      << std::endl;
            
            std::cin.get();
        }
    }while(!log.is_open());
}

std::ofstream& InputOutput::GetLogFile() {
    return this->logFile;
}

std::ofstream& InputOutput::GetResultFile() {
    return this->resultFile;
}

