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
#include "../../include/ResourceAllocation/CSA.h"
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
        case SpecAllFFC:{
            CSA* csa = static_cast<CSA *>(this);
            csa->FirstFitCore(call);
            break;
        }
        case SpecAllMC_MSCL:{
            CSA* csa = static_cast<CSA *>(this);
            csa->MulticoreMSCL(call);
            break;
        }
        default:
            std::cerr << "Invalid spectrum allocation option" << std::endl;
    }
}

void SA::Random(Call* call) {
    std::shared_ptr<Route> route = call->GetRoute();
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
    std::shared_ptr<Route> route = call->GetRoute();
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

Topology* SA::GetTopology(){
    return topology;
}

int SA::CalcNumFormAloc(int L, bool* Disp,int tam){ 
//L indica a largura da requisicao e Disp o vetor de disponibilidade
/*
	int sum = 0, si, se; //si eh o slot inicial da alocacao, que vai de 0 ate SE-L
	for(si = 0; si <= tam-L; si++){
		for(se = si; se < si+L; se++) //se checa se todos os slots de si ate si+L-1 estao disponiveis
			if(Disp[se] == false)
				break;
		if(se == si+L) // Os slots si,si+1,...,si+Lf-1 estao disponiveis
			sum++;
	}
	return sum;
}
*/
    int sum = 0, si;//si eh o slot inicial da alocacao, que vai de 0 ate SE-L
    int cont = 0;
    for(si = 0; si < tam; si++){
        if(Disp[si] == false){
            if(cont >= L){
                 sum += cont - L + 1;
                 //sum += floor (cont/L);
            }
                cont = 0;
        }
            else{
                cont++;
            }
    }
    if(cont >= L){
       sum += cont - L + 1;
    }
    return sum;
}

ResourceAlloc* SA::GetResourceAlloc(){
    return this->resourceAlloc;
}