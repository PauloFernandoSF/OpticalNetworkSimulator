/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SimulationType.cpp
 * Author: bruno
 * 
 * Created on August 2, 2018, 3:50 PM
 */

#include "../../include/SimulationType/SimulationType.h"

#include "../../include/Data/Parameters.h"
#include "../../include/Data/Options.h"
#include "../../include/Data/Data.h"
#include "../../include/Structure/Topology.h"

SimulationType::SimulationType()
:parameters(std::make_shared<Parameters> (this)), 
options(std::make_shared<Options> (this)), 
data(boost::make_unique<Data>(this)), 
topology(std::make_shared<Topology> (this)) {
    
}

SimulationType::~SimulationType() {
    
}

void SimulationType::LoadFile() {
    
}
