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

#include "../../include/SimulationType/SimulationType.h"
#include "../../include/Data/Options.h"
#include "../../include/Data/InputOutput.h"

Topology::Topology(SimulationType* simulType) 
:simulType(simulType), nameTopology("Invalid"), 
vecNodes(0), vecLinks(0), numNodes(0), numLinks(0), 
numSlots(0){

}

Topology::~Topology() {
    
    for(auto it : vecNodes){
        it->~Node();
    }
    
    for(auto it : vecLinks){
        it->~Link();
    }
}

void Topology::LoadFile() {
    this->SetNameTopology(this->simulType->GetOptions()->GetTopologyName());
    std::ifstream auxIfstream;
    int auxInt;
    
    this->simulType->GetInputOutput()->LoadTopology(auxIfstream);
    
    auxIfstream >> auxInt;
    this->SetNumNodes(auxInt);
    auxIfstream >> auxInt;
    this->SetNumLinks(auxInt);
    auxIfstream >> auxInt;
    this->SetNumSlots(auxInt);
    
    int orNode, deNode, nSec;
    double length;
    for(auxInt = 0; auxInt < this->GetNumNodes(); ++auxInt){
        auxIfstream >> orNode;
        auxIfstream >> deNode;
        auxIfstream >> length;
        auxIfstream >> nSec;
        std::shared_ptr<Link> link = std::make_shared<Link>(orNode,
        deNode, length, nSec);
        this->InsertLink(link);
    }
}


void Topology::Initialise() {
    
    for(auto it : vecNodes){
        it->initialise();
    }
    
    for(auto it : vecLinks){
        if(it != nullptr)
            it->initialise();
    }
}

std::string Topology::GetNameTopology() const {
    return nameTopology;
}

void Topology::SetNameTopology(std::string nameTopology) {
    this->nameTopology = nameTopology;
}

int Topology::GetNumNodes() const {
    return numNodes;
}

void Topology::SetNumNodes(int numNodes) {
    assert(numNodes > 0 && this->numNodes == 0);
    this->numNodes = numNodes;
    
    for(int a = 0; a < this->numNodes; ++a){
        this->vecNodes.push_back(std::make_shared<Node>());
        
        for(int b = 0; a < this->numNodes; ++b){
            this->vecLinks.push_back(nullptr);
        }
    }
}

int Topology::GetNumLinks() const {
    return numLinks;
}

void Topology::SetNumLinks(int numLinks) {
    assert(numLinks > 0 && this->numLinks == 0);
    this->numLinks = numLinks;
}

int Topology::GetNumSlots() const {
    return numSlots;
}

void Topology::SetNumSlots(int numSlots) {
    assert(numSlots > 0 && this->numSlots == 0);
    this->numSlots = numSlots;
}

void Topology::InsertLink(std::shared_ptr<Link> link) {
    assert( this->vecLinks.at(link->GetOrigimNode()*this->GetNumNodes()
    + link->GetDestinationNode()) == nullptr );
    
    this->vecLinks.at(link->GetOrigimNode()*this->GetNumNodes()
    + link->GetDestinationNode()) = link;
}

