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
    
    for(unsigned int a = 0; a < topPointer->GetNumCores(); a++){
        this->coreVector.at(a) = std::make_shared<Core>(a, topPointer->
                                 GetNumSlots());
    }
}

MultiCoreLink::~MultiCoreLink() {
    
}

void MultiCoreLink::Initialize() {
    
    for(auto it: this->coreVector){
        it->Initialize();
    }
}

Core* MultiCoreLink::GetCore(unsigned int corePosition) {
    assert(corePosition < this->GetTopology()->GetNumCores());
    
    return this->coreVector.at(corePosition).get();
}

void MultiCoreLink::OccupySlot(unsigned int coreIndex, unsigned int slot) {
    assert(coreIndex < this->GetTopology()->GetNumCores() &&
           slot < this->GetTopology()->GetNumSlots());
    
    this->GetCore(coreIndex)->OccupySlot(slot);
}

void MultiCoreLink::ReleaseSlot(unsigned int coreIndex, unsigned int slot) {
    assert(coreIndex < this->GetTopology()->GetNumCores() &&
           slot < this->GetTopology()->GetNumSlots());
    
    this->GetCore(coreIndex)->ReleaseSlot(slot);
}
