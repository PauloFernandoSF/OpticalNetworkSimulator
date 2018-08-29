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
#include "../../include/Data/Parameters.h"
#include "../../include/Data/InputOutput.h"
#include "../../include/Structure/Node.h"
#include "../../include/Structure/Link.h"

std::ostream& operator<<(std::ostream& ostream, 
const Topology* topology) {
    ostream << "TOPOLOGY" << std::endl;
    
    ostream << "Number of nodes: " << topology->GetNumNodes() 
            << std::endl;
    ostream << "Number of links: " << topology->GetNumLinks()
            << std::endl;
    ostream << "Number of slots: " << topology->GetNumSlots()
            << std::endl;
    
    for(auto it: topology->vecNodes){
        ostream << it << std::endl;
    }
    
    for(auto it : topology->vecLinks){
        if(it != nullptr)
            ostream << it << std::endl;
    }
    
    return ostream;
}

Topology::Topology(SimulationType* simulType) 
:simulType(simulType), vecNodes(0), vecLinks(0), 
numNodes(0), numLinks(0), numSlots(0), maxLength(0.0) {

}

Topology::~Topology() {
    
    for(auto it : this->vecNodes){
        it.reset();
    }
    
    
    for(auto it : this->vecLinks){
        it.reset();
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
    
    //Create all topology nodes
    std::shared_ptr<Node> node;
    for(unsigned int a = 0; a < this->GetNumNodes(); ++a){
        node = std::make_shared<Node>(this, a);
        this->InsertNode(node);
        node.reset();
    }
    
    //Create all topology links
    int orNode, deNode, nSec;
    double length;
    std::shared_ptr<Link> link;
    for(auxInt = 0; auxInt < this->GetNumLinks(); ++auxInt){
        auxIfstream >> orNode;
        auxIfstream >> deNode;
        auxIfstream >> length;
        auxIfstream >> nSec;
        link = std::make_shared<Link>(this, orNode, deNode, 
        length, nSec, this->GetNumSlots());
        this->InsertLink(link);
        link.reset();
    }
}

void Topology::Initialise() {
    
    for(auto it : this->vecNodes){
        it->Initialise();
    }
    
    for(auto it : this->vecLinks){
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
    assert( this->vecLinks.at(link->GetOrigimNode() * this->GetNumNodes()
    + link->GetDestinationNode()) == nullptr );
    
    this->vecLinks.at(link->GetOrigimNode() * this->GetNumNodes()
    + link->GetDestinationNode()) = link;
}

void Topology::InsertNode(std::shared_ptr<Node> node) {
    assert(node.get()->GetNodeId() < this->vecNodes.size());
    
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

Node* Topology::GetNode(unsigned int index) const {
    return this->vecNodes.at(index).get();
}

Link* Topology::GetLink(unsigned int indexOrNode, 
unsigned int indexDeNode) const {
    return this->vecLinks.at(indexOrNode * this->numNodes + 
    indexDeNode).get();
}
