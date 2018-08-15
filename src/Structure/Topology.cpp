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
#include "../../include/Structure/Node.h"
#include "../../include/Structure/Link.h"

Topology::Topology(SimulationType* simulType) 
:simulType(simulType), vecNodes(0), vecLinks(0), 
numNodes(0), numLinks(0), numSlots(0), maxLength(0.0) {

}

Topology::~Topology() {
    
    for(auto it : vecNodes){
        it->~Node();
    }
    
    for(auto it : vecLinks){
        if(it != nullptr)
            it->~Link();
    }
}

void Topology::LoadFile() {
    std::ifstream auxIfstream;
    int auxInt;
    
    this->simulType->GetInputOutput()->LoadTopology(auxIfstream);
    
    auxIfstream >> auxInt;
    this->SetNumNodes(auxInt);
    auxIfstream >> auxInt;
    this->SetNumLinks(auxInt);
    auxIfstream >> auxInt;
    this->SetNumSlots(auxInt);
    
    //Create a function based in the simulation options
    for(auxInt = 0; auxInt < this->GetNumNodes(); ++auxInt){
        std::shared_ptr<Node> node = 
        std::make_shared<Node> (this, auxInt);
        this->InsertNode(node);
    }
    
    int orNode, deNode, nSec;
    double length;
    for(auxInt = 0; auxInt < this->GetNumLinks(); ++auxInt){
        auxIfstream >> orNode;
        auxIfstream >> deNode;
        auxIfstream >> length;
        auxIfstream >> nSec;
        std::shared_ptr<Link> link = std::make_shared<Link>(this, 
        orNode, deNode, length, nSec);
        this->InsertLink(link);
    }
}

void Topology::Initialise() {
    
    for(auto it : vecNodes){
        it->Initialise();
    }
    
    for(auto it : vecLinks){
        if(it != nullptr)
            it->Initialise();
    }
}

int Topology::GetNumNodes() const {
    return numNodes;
}

void Topology::SetNumNodes(int numNodes) {
    assert(numNodes > 0 && this->numNodes == 0);
    this->numNodes = numNodes;
    
    for(int a = 0; a < this->numNodes; ++a){
        this->vecNodes.push_back(nullptr);
        
        for(int b = 0; b < this->numNodes; ++b){
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

void Topology::InsertNode(std::shared_ptr<Node> node) {
    assert(node->GetNodeId() < this->vecNodes.size());
    
    this->vecNodes.at(node->GetNodeId()) = node;
}

double Topology::GetMaxLength() const {
    return maxLength;
}

void Topology::SetMaxLength() {
    
    for(auto it : this->vecLinks){
        
        if(it == nullptr)
            continue;
        
        if(this->maxLength < it->GetLength())
            this->maxLength = it->GetLength();
    }
}

void Topology::SetAditionalSettings() {
    this->SetMaxLength();
    this->SetLinksIniCost();
}

void Topology::SetLinksIniCost() {
    
    switch(this->simulType->GetOptions()->GetLinkCostType()){
        case MinHops:
            for(auto it : vecLinks){
                if(it == nullptr)
                    continue;
                it->SetCost(1.0);
            }
            break;
        case MinLength:
            for(auto it : vecLinks){
                if(it == nullptr)
                    continue;
                it->SetCost(it->GetLength());
            }
            break;
        case MinLengthNormalized:
            for(auto it : vecLinks){
                if(it == nullptr)
                    continue;
                it->SetCost(it->GetLength()/this->GetMaxLength());
            }
            break;
        default:
            for(auto it : vecLinks){
                if(it == nullptr)
                    continue;
                it->SetCost(std::numeric_limits<double>::max());
            }
    }
}
