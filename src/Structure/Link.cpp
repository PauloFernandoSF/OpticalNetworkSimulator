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
#include "../../include/Structure/Topology.h"
#include "../../include/ResourceAllocation/Signal.h"
#include "../../include/GeneralClasses/General.h"

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
slotsStatus(0), linkWorking(true) {
    slotsStatus.resize(numberSlots, SlotFree);
}

Link::~Link() {
    
}

void Link::Initialize() {
    //Make all slots status for free
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

bool Link::IsLinkWorking() const {
    return this->linkWorking;
}

void Link::SetLinkWorking(bool linkWorking) {
    this->linkWorking = linkWorking;
}

void Link::CalcSignal(Signal* signal) const {
    double signalPower = signal->GetSignalPower();
    double asePower = signal->GetAsePower();
    double nonLinearPower = signal->GetNonLinearPower();
    
    double lSec = (double) this->GetLength()/this->GetNumberSections();
    double gLSec = 1.0/(General::dBToLinear(lSec*Signal::Alpha));
    double gAmp = 1.0/gLSec;
    
    for(unsigned int sec = 0; sec < this->numberSections; sec++){
        signalPower *= gLSec;
        asePower *= gLSec;
        nonLinearPower *= gLSec;
        nonLinearPower += 0.0;
        
        signalPower *= gAmp;
        asePower *= gAmp;
        asePower += Signal::pASE(Signal::fn, gAmp);
        nonLinearPower *= gAmp;
    }
    
    signal->SetSignalPower(signalPower);
    signal->SetAsePower(asePower);
    signal->SetNonLinearPower(nonLinearPower);
}

void Link::OccupySlot(const unsigned int index) {
    assert(this->IsSlotFree(index));
    
    this->slotsStatus.at(index) = SlotUsed;
}

void Link::ReleaseSlot(const unsigned int index) {
    assert(this->IsSlotOccupied(index));
    
    this->slotsStatus.at(index) = SlotFree;
}

bool Link::IsSlotOccupied(unsigned int index) const {
    
    if(this->slotsStatus.at(index) == SlotUsed)
        return true;
    return false;
}

bool Link::IsSlotFree(unsigned int index) const {
    
    if(this->slotsStatus.at(index) == SlotFree)
        return true;
    return false;
}

unsigned int Link::GetNumberFreeSlots() const {
    unsigned int numFreeSlots = 0;
    unsigned int numSlots = this->topPointer->GetNumSlots();
    
    for(unsigned int a = 0; a < numSlots; a++){
        if(this->IsSlotFree(a))
            numFreeSlots++;
    }
    
    return numFreeSlots;
}

unsigned int Link::GetNumberOccupiedSlots() const {
    unsigned int numOccupiedSlots = 0;
    unsigned int numSlots = this->topPointer->GetNumSlots();
    numOccupiedSlots = numSlots - this->GetNumberFreeSlots();
    
    return numOccupiedSlots;
    
}

Topology* Link::GetTopology() const{
    return this->topPointer;
}