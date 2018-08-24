/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Parameters.cpp
 * Author: bruno
 * 
 * Created on August 8, 2018, 6:25 PM
 */

#include "../../include/Data/Parameters.h"

#include "../../include/SimulationType/SimulationType.h"
#include "../../include/Data/InputOutput.h"

std::ostream& operator<<(std::ostream& ostream, 
const Parameters* parameters) {
    
    ostream << "PARAMETERS" << std::endl;
    ostream << "Mu: " << parameters->GetMu() << std::endl;
    ostream << "Minimum load point(erlang): " 
            << parameters->GetMinLoadPoint() << std::endl;
    ostream << "Maximum load point(erlang): " 
            << parameters->GetMaxLoadPoint() << std::endl;
    ostream << "Number of points: " << parameters->GetNumberLoadPoints() 
            << std::endl;
    ostream << "Total number of requisitions: " 
            << parameters->GetNumberReqMax() << std::endl;
    ostream << "Maximum blocked requests: "
            << parameters->GetNumberBloqMax() << std::endl;
    ostream << "Slot bandwidth(GHz): "
            << parameters->GetSlotBandwidth() << std::endl;
    
    return ostream;
}

Parameters::Parameters(SimulationType* simulType)
:simulType(simulType), loadPoint(0), minLoadPoint(0.0),
maxLoadPoint(0.0), loadPasso(0.0), numberLoadPoints(0),
numberReqMax(0.0), mu(0.0), numberBloqMax(0),
slotBandwidth(0.0) {
    
}

Parameters::~Parameters() {
    
}

void Parameters::LoadFile() {
    std::ifstream auxIfstream;
    int auxInt;
    double auxDouble;
    
    this->simulType->GetInputOutput()->LoadParameters(auxIfstream);
    auxIfstream >> auxDouble;
    this->SetMu(auxDouble);
    auxIfstream >> auxDouble;
    this->SetMinLoadPoint(auxDouble);
    auxIfstream >> auxDouble;
    this->SetMaxLoadPoint(auxDouble);
    auxIfstream >> auxInt;
    this->SetNumberLoadPoints(auxInt);
    auxIfstream >> auxDouble;
    this->SetNumberReqMax(auxDouble);
    auxIfstream >> auxInt;
    this->SetNumberBloqMax(auxInt);
    auxIfstream >> auxDouble;
    this->SetSlotBandwidth(auxDouble);
    
    this->SetLoadPointUniform();
}

std::vector<double> Parameters::GetLoadPoint() const {
    return loadPoint;
}

double Parameters::GetLoadPoint(unsigned int index) const {
    assert(index < this->loadPoint.size());
    return loadPoint.at(index);
}

void Parameters::SetLoadPoint(std::vector<double> loadPoint) {
    assert(loadPoint.size() > 0);
    this->loadPoint = loadPoint;
}

void Parameters::SetLoadPoint(double loadPoint, unsigned int index) {
    assert(index < this->loadPoint.size());
    this->loadPoint.at(index) = loadPoint;
}

double Parameters::GetMinLoadPoint() const {
    return minLoadPoint;
}

void Parameters::SetMinLoadPoint(double minLoadPoint) {
    assert(minLoadPoint > 0.0);
    this->minLoadPoint = minLoadPoint;
}

double Parameters::GetMaxLoadPoint() const {
    return maxLoadPoint;
}

void Parameters::SetMaxLoadPoint(double maxLoadPoint) {
    assert(maxLoadPoint > 0.0);
    this->maxLoadPoint = maxLoadPoint;
}

unsigned int Parameters::GetNumberLoadPoints() const {
    return numberLoadPoints;
}

void Parameters::SetNumberLoadPoints(unsigned int numberLoadPoints) {
    this->numberLoadPoints = numberLoadPoints;
}

double Parameters::GetNumberReqMax() const {
    return numberReqMax;
}

void Parameters::SetNumberReqMax(double numberReqMax) {
    assert(numberReqMax > 0.0);
    this->numberReqMax = numberReqMax;
}

double Parameters::GetMu() const {
    return mu;
}

void Parameters::SetMu(double mu) {
    assert(mu > 0.0);
    this->mu = mu;
}

void Parameters::SetLoadPasso() {
    int auxInt = this->numberLoadPoints;
    
    if(auxInt == 1)
        auxInt++;
   
    this->loadPasso = (this->maxLoadPoint - this->minLoadPoint) / (auxInt - 1);
}

void Parameters::SetLoadPointUniform() {
    this->SetLoadPasso();
    
    for(int a = 0; a < this->numberLoadPoints; ++a){
        loadPoint.push_back(this->minLoadPoint + a*this->loadPasso);
    }
}

double Parameters::GetNumberBloqMax() const {
    return numberBloqMax;
}

void Parameters::SetNumberBloqMax(double numberBloqMax) {
    assert(numberBloqMax > 0.0);
    this->numberBloqMax = numberBloqMax;
}

double Parameters::GetSlotBandwidth() const {
    return slotBandwidth/10E9;
}

void Parameters::SetSlotBandwidth(double slotBandwidth) {
    assert(slotBandwidth > 0.0);
    this->slotBandwidth = slotBandwidth*10E9;
}
