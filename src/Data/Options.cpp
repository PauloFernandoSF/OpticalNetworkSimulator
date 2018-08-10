/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Options.cpp
 * Author: bruno
 * 
 * Created on August 3, 2018, 1:18 AM
 */

#include "../../include/Data/Options.h"

#include "../../include/SimulationType/SimulationType.h"
#include "../../include/Data/InputOutput.h"

Options::Options(SimulationType* simulType)
:simulType(simulType), topologyOption(TopologyInvalid),
routingOption(RoutingInvalid), specAllOption(SpecAssInvalid) {
}

Options::~Options() {

}

void Options::LoadFile() {
    std::ifstream auxIfstream;
    int auxInt;
    
    this->simulType->GetInputOutput()->LoadOptions(auxIfstream);
    auxIfstream >> auxInt;
    this->SetTopologyOption((TopologyOption) auxInt);
    auxIfstream >> auxInt;
    this->SetRoutingOption((RoutingOption) auxInt);
    auxIfstream >> auxInt;
    this->SetSpecAllOption((SpectrumAllocationOption) auxInt);
}

RoutingOption Options::GetRoutingOption() const {
    return routingOption;
}

void Options::SetRoutingOption(RoutingOption routingOption) {
    this->routingOption = routingOption;
}

SpectrumAllocationOption Options::GetSpecAllOption() const {
    return specAllOption;
}

void Options::SetSpecAllOption(SpectrumAllocationOption specAllOption) {
    this->specAllOption = specAllOption;
}

TopologyOption Options::GetTopologyOption() const {
    return topologyOption;
}

void Options::SetTopologyOption(TopologyOption topologyOption) {
    this->topologyOption = topologyOption;
}
