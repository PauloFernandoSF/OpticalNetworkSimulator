/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Link.cpp
 * Author: bruno
 * 
 * Created on August 4, 2018, 1:54 AM
 */

#include "../../include/Structure/Link.h"

std::ostream& operator<<(std::ostream& ostream,
Link* link) {
    ostream << "Origim node: " << link->GetOrigimNode()
            << std::endl;
    ostream << "Destination node: " << link->GetDestinationNode()
            << std::endl;
    ostream  << "Length (km): " << link->GetLength() / 1E3
            << std::endl;
    ostream << "Number of sections: " << link->GetNumberSections()
            << std::endl;
    ostream << "Cost: " << link->GetCost()
            << std::endl;
    
    return ostream;
}

Link::Link(Topology* topPointer, unsigned int origimNode, 
unsigned int destinationNode, double length, 
unsigned int numberSections, unsigned int numberSlots) 
:origimNode(origimNode), destinationNode(destinationNode), 
length(length), numberSections(numberSections), cost(0.0),
slotsStatus(0) {
    slotsStatus.resize(numberSlots, SlotFree);
}

Link::~Link() {
    
}

void Link::Initialise() {
    this->slotsStatus.resize(this->slotsStatus.size(), SlotFree);  
}

unsigned int Link::GetOrigimNode() const {
    return origimNode;
}

void Link::SetOrigimNode(unsigned int origimNode) {
    this->origimNode = origimNode;
}

unsigned int Link::GetDestinationNode() const {
    return destinationNode;
}

void Link::SetDestinationNode(unsigned int destinationNode) {
    this->destinationNode = destinationNode;
}

double Link::GetLength() const {
    return length;
}

void Link::SetLength(double length) {
    this->length = length;
}

unsigned int Link::GetNumberSections() const {
    return numberSections;
}

void Link::SetNumberSections(unsigned int numberSections) {
    this->numberSections = numberSections;
}

double Link::GetCost() const {
    return cost;
}

void Link::SetCost(double cost) {
    this->cost = cost;
}
