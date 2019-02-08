/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SA.cpp
 * Author: BrunoVinicius
 * 
 * Created on November 22, 2018, 11:36 PM
 */

#include "../../include/ResourceAllocation/SA.h"
#include "../../include/Calls/Call.h"
#include "../../include/ResourceAllocation/Route.h"
#include "../../include/Structure/Topology.h"

SA::SA(ResourceAlloc* rsa, SpectrumAllocationOption option, Topology* topology) 
:resourceAlloc(rsa), specAllOption(option), topology(topology) {
    
}

SA::~SA() {
    
}

void SA::SpecAllocation(Call* call) {
    switch(this->specAllOption){
        case SpecAllRandom:
            this->Random(call);
            break;
        case SpecAllFF:
            this->FirstFit(call);
            break;
        default:
            std::cerr << "Invalid spectrum allocation option" << std::endl;
    }
}

void SA::Random(Call* call) {
    std::vector<unsigned int> vecSlots(0);
    unsigned int auxVar;
    
    vecSlots = this->FirstFitSlots(call);
    
    if(!vecSlots.empty()){
        auxVar = vecSlots.at(std::rand() % vecSlots.size());
        call->SetFirstSlot(auxVar);
        call->SetLastSlot(auxVar + call->GetNumberSlots() - 1);
    }
}

void SA::FirstFit(Call* call) {
    Route* route = call->GetRoute();
    unsigned int numSlotsReq = call->GetNumberSlots();
    unsigned int maxSlotIndex = this->topology->GetNumSlots() - 
                                 numSlotsReq;
    
    for(unsigned int slot = 0; slot <= maxSlotIndex; slot++){
        if(this->topology->CheckSlotsDisp(route, slot, slot + numSlotsReq - 1)){
            call->SetFirstSlot(slot);
            call->SetLastSlot(slot + numSlotsReq - 1);
        }
    }

}

std::vector<unsigned int> SA::RandomSlots(Call* call) {
    std::vector<unsigned int> auxVecSlots(0);
    std::vector<unsigned int> vecSlots(0);
    unsigned int auxVar;
    
    auxVecSlots = this->FirstFitSlots(call);
    
    while(!auxVecSlots.empty()){
        auxVar = std::rand() % auxVecSlots.size();
        vecSlots.push_back(auxVecSlots.at(auxVar));
        auxVecSlots.erase(auxVecSlots.begin() + auxVar);
    }
    
    return vecSlots;
}

std::vector<unsigned int> SA::FirstFitSlots(Call* call) {
    Route* route = call->GetRoute();
    unsigned int numSlotsReq = call->GetNumberSlots();
    unsigned int maxSlotIndex = this->topology->GetNumSlots() - 
                                 numSlotsReq;
    std::vector<unsigned int> slots(0);
    
    for(unsigned int a = 0; a <= maxSlotIndex; a++){
        if(this->topology->CheckSlotsDisp(route, a, a + numSlotsReq - 1)){
            slots.push_back(a);
        }
    }
    
    return slots;
}