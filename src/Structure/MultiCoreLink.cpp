/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MultiCoreLink.cpp
 * Author: paulofilho
 * 
 * Created on 5 de fevereiro de 2019, 21:13
 */

#include "../../include/Structure/MultiCoreLink.h"
#include "../../include/Structure/Core.h"
#include "../../include/Structure/Topology.h"

MultiCoreLink::MultiCoreLink(Topology* topPointer, unsigned int origimNode, 
unsigned int destinationNode, double length, unsigned int numberSections, 
unsigned int numberSlots)
:Link(topPointer, origimNode, destinationNode, length, numberSections, 
numberSlots){
    this->coreVector.resize(topPointer->GetNumCores()); 
}

void MultiCoreLink::Initialize(){
    
    for(unsigned int c = 0;c < this->Link::GetTopology()->GetNumCores();c++){
        this->coreVector.at(c) = (std::make_shared<Core>(c,
                                  this->Link::GetTopology()->GetNumSlots()));   
    }
}

Core* MultiCoreLink::getCore(int corePosition){
    return this->coreVector.at(corePosition).get();
}

void MultiCoreLink::OccupySlot(int coreIndex,int slot){
    this->getCore(coreIndex)->occupySlot(slot);
}

void MultiCoreLink::ReleaseSlot(int coreIndex, int slot){
    this->getCore(coreIndex)->releaseSlot(slot);
}


MultiCoreLink::~MultiCoreLink() {
    
}
