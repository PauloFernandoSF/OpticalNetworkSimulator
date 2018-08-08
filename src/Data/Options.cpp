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

Options::Options(SimulationType* simulType)
:routingOption(RoutingInvalid), specAllOption(SpecAssInvalid),
simulType(simulType) {
}

Options::~Options() {
}

RoutingType Options::getRoutingOption() const {
    return routingOption;
}

void Options::setRoutingOption(RoutingType opt) {
    routingOption = opt;
}

SpectrumAllocationType Options::getSpecAllOption() const {
    return specAllOption;
}

void Options::setSpecAllOption(SpectrumAllocationType opt) {
    specAllOption = opt;
}