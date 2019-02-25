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
    ostream  << "Core Id: " << core->getCoreId() << std::endl;
    
    return ostream;
}

Core::Core(CoreId cId,NumSlots nSlots)
:coreId (cId){
    this->vDisp = new bool[nSlots];
    for(int i=0;i < nSlots;i++){
        this->vDisp[i]= false;
    }
}

bool Core::getSlotOccupation(int sPosition){
    return this->vDisp[sPosition];
}

//Ocupa o slot atribuindo o valor 1
void Core::occupySlot(int sPosition){
    //vDisp.at(sPosition)= true;
    this->vDisp[sPosition] = true;
}

void Core::releaseSlot(int sPosition){
    this->vDisp[sPosition]= false;

}

CoreId Core::getCoreId(){
    return this->coreId;
}


