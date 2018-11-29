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

SA::SA() {
}

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
            std::cerr << "Innvalid spectrum allocation option" << std::endl;
    }
    //For tests.
    call->SetStatus(Accepted);
}

void SA::Random(Call* call) {
    Route* route = call->GetRoute();
    unsigned int numSlotsReq = call->GetNumberSlots(), sumslots = 0;
    unsigned int numSlotsTotal = this->topology->GetNumSlots();
    int firstSlot = 0;
    std::vector<int> vecSlots;
    
    for(unsigned int a = 0; a < numSlotsTotal; a++){
        if(this->topology->CheckSlotDisp(route, a)) {
            sumslots++;
            
            if(sumslots == numSlotsReq){
                firstSlot = (int) a-numSlotsReq+1;
                vecSlots.push_back(firstSlot);
                a = a-numSlotsReq+1;
                sumslots = 0;
            }
        }
        else
            sumslots = 0;
    }
    
    if(vecSlots.size() > 0){
        firstSlot = vecSlots.at(std::rand() % vecSlots.size());
        call->SetFirstSlot(firstSlot);
        call->SetLastSlot(firstSlot + numSlotsReq - 1);
    }
}

void SA::FirstFit(Call* call) {
    Route* route = call->GetRoute();
    unsigned int numSlotsReq = call->GetNumberSlots(), sumslots = 0;
    unsigned int numSlotsTotal = this->topology->GetNumSlots();
    
    for(unsigned int a = 0; a < numSlotsTotal; a++){
        if(this->topology->CheckSlotDisp(route, a)){
            sumslots++;
            
            if(sumslots == numSlotsReq){
                call->SetFirstSlot((int) a-numSlotsReq+1);
                call->SetLastSlot((int) a);
                break;
            }
        }
        else
            sumslots = 0;
    }
}



