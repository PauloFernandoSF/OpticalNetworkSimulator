/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Topology.cpp
 * Author: bruno
 * 
 * Created on August 3, 2018, 12:00 AM
 */

#include "../../include/Structure/Topology.h"

Topology::Topology(SimulationType* simulType) {
    vecNodes.resize(numNodes);
    vecLinks.resize(numNodes*numNodes, nullptr);
}

Topology::~Topology() {
}

void Topology::initialise() {
    
    for(auto it : vecNodes){
        it->initialise();
    }
    
    for(auto it : vecLinks){
        if(it != nullptr)
            it->initialise();
    }
}