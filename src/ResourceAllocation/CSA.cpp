/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CSA.cpp
 * Author: paulofilho
 * 
 * Created on 7 de fevereiro de 2019, 15:19
 */

#include "../../include/ResourceAllocation/CSA.h"
#include "../../include/ResourceAllocation/SA.h"
#include "../../include/Calls/Call.h"
#include "../../include/ResourceAllocation/Route.h"
#include "../../include/Structure/Topology.h"
#include "../../include/Calls/MultiCoreCall.h"

CSA::CSA(ResourceAlloc* rsa, SpectrumAllocationOption option,
        Topology* topology):SA(rsa, option, topology){
}

void CSA::FirstFitCore(Call* call){
    MultiCoreCall* mcCall = static_cast<MultiCoreCall *>(call);
    Route *route = mcCall->GetRoute();bool flag = false;
    int numSlotsReq = mcCall->GetNumberSlots();
    int slot_range = this->GetTopology()->GetNumSlots() - numSlotsReq + 1;
    //Tries to find a set of available slots in a core- vary slots and later 
    //cores
    for(int core = 0;core < this->GetTopology()->GetNumCores();core++){
        for(int s = 0; s < slot_range;s++){
            if(this->GetTopology()->CheckSlotsDispCore(route, s,
                    s + mcCall->GetNumberSlots() - 1,core)){
                mcCall->SetFirstSlot(s);
                mcCall->SetLastSlot(s + mcCall->GetNumberSlots() - 1);
                mcCall->SetCore(core);
                flag = true;
                break;
            }
        }
        if(flag)
            break;
    }
}

CSA::~CSA() {
}

