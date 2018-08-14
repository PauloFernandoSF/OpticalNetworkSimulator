/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Traffic.cpp
 * Author: bruno
 * 
 * Created on August 14, 2018, 1:15 AM
 */

#include <fstream>

#include "../../include/Calls/Traffic.h"

#include "../../include/SimulationType/SimulationType.h"
#include "../../include/Data/InputOutput.h"

const double Traffic::BER = 0.001;
const int Traffic::polarization = 1;

Traffic::Traffic(SimulationType* simulType)
:simulType(simulType), vecTraffic(0) {
}

Traffic::Traffic(const Traffic& orig) {
}

Traffic::~Traffic() {
}

void Traffic::LoadFile() {
    std::ifstream auxIfstream;
    int auxInt;
    double auxDouble;
    
    this->simulType->GetInputOutput()->LoadTraffic(auxIfstream);
    
    auxIfstream >> auxInt;
    for(int a = 0; a < auxInt; a++){
        auxIfstream >> auxDouble;
        vecTraffic.push_back(auxDouble);
    }
}

std::vector<double> Traffic::GetVecTraffic() const {
    return vecTraffic;
}

void Traffic::SetVecTraffic(std::vector<double> vecTraffic) {
    this->vecTraffic = vecTraffic;
}

const double Traffic::GetBER() {
    return BER;
}

const int Traffic::GetPolarization() {
    return polarization;
}
