/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Core.cpp
 * Author: paulofilho
 * 
 * Created on 4 de fevereiro de 2019, 15:17
 */

#include "../../include/Structure/Core.h"

std::ostream& operator<<(std::ostream& ostream,
Core* core) {
    ostream  << "Core Id: " << core->GetCoreId() << std::endl;
    
    return ostream;
}

Core::Core(CoreId cId, NumSlots nSlots)
:coreId(cId), slotsStatus(0) {
    /*this->vDisp = new bool[nSlots];
    for(unsigned int i=0;i < nSlots;i++){
        this->vDisp[i]= false;
    }*/
    this->slotsStatus.assign(nSlots, SlotFree);
}

Core::~Core() {

}

void Core::Initialize() {
    this->slotsStatus.assign(this->slotsStatus.size(), SlotFree);
}

CoreId Core::GetCoreId(){
    return this->coreId;
}

bool Core::IsSlotOccupied(unsigned int sPosition){
    //return this->vDisp[sPosition];
    if(this->slotsStatus.at(sPosition) == SlotUsed)
        return true;
    return false;
}

bool Core::IsSlotFree(unsigned int sPosition) {
    return !this->IsSlotOccupied(sPosition);
}

void Core::OccupySlot(unsigned int sPosition){
    //this->vDisp[sPosition] = true;
    assert(sPosition < this->slotsStatus.size());
    assert(this->slotsStatus.at(sPosition) == SlotFree);
    
    this->slotsStatus.at(sPosition) = SlotUsed;
}

void Core::ReleaseSlot(unsigned int sPosition){
    //this->vDisp[sPosition]= false;
    assert(sPosition < this->slotsStatus.size());
    assert(this->slotsStatus.at(sPosition) == SlotUsed);
    
    this->slotsStatus.at(sPosition) = SlotFree;
}
