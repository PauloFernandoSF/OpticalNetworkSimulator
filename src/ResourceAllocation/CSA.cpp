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
#include "../../include/Calls/Call.h"
#include "../../include/Calls/Traffic.h"
#include "../../include/SimulationType/SimulationType.h"
#include "../../include/ResourceAllocation/Route.h"
#include "../../include/ResourceAllocation/ResourceAlloc.h"
#include "../../include/Structure/Topology.h"

CSA::CSA(ResourceAlloc* rsa, SpectrumAllocationOption option,Topology* topology,
        GAOption gaOption):gaOption(gaOption),SA(rsa, option, topology){;

}

CSA::~CSA() {
    
}
void CSA::FirstFit(Call* call){
    switch(this->gaOption){
        case GAOptionDisabled:
            this->NormalFirstFit(call);
            break;
        case GaCoreOrder:
            this->GAFirstFit(call);
            break;
        default:
            std::cerr << "Invalid Heuristic" << std::endl;
        
    }
}
void CSA::NormalFirstFit(Call* call){
    Route* route = call->GetRoute();
    bool flag = false;
    int numSlotsReq = call->GetNumberSlots();
    int slot_range = this->GetTopology()->GetNumSlots() - numSlotsReq + 1;
    //Tries to find a set of available slots in a core- vary slots and later 
    //cores
    for(unsigned int core = 0; core < this->GetTopology()->GetNumCores(); 
    core++){
        for(int s = 0; s < slot_range; s++){
            if(this->GetTopology()->CheckSlotsDispCore(route, s, s + 
            call->GetNumberSlots() - 1, core)){
                call->SetFirstSlot(s);
                call->SetLastSlot(s + call->GetNumberSlots() - 1);
                call->SetCore(core);
                flag = true;
                break;
            }
        }
        if(flag)
            break;
    }
}

void CSA::GAFirstFit(Call* call){
    Route* route = call->GetRoute();
    std::vector<double> vecTraffic = this->GetResourceAlloc()->GetSimulType()
    ->GetTraffic()->GetVecTraffic();
    double traffic = call->GetBitRate();
    bool flag = false;
    int numSlotsReq = call->GetNumberSlots();
    int slot_range = this->GetTopology()->GetNumSlots() - numSlotsReq + 1;
    unsigned int reqIndex,core;
    //Bandwidth WON'T be equal to any vecTraffic positions!FIX IT!
    for(unsigned int i = 0;i < vecTraffic.size();i++){
        if(vecTraffic.at(i) == traffic){
            reqIndex = i;
            break;
        }
    }
    //Tries to find a set of available slots in a core- vary slots and later 
    //cores
    for(unsigned int a = 0; a < this->GetTopology()->GetNumCores(); 
    a++){
        core = this->ind->GetGene(reqIndex,a);
        for(int s = 0; s < slot_range; s++){
            if(this->GetTopology()->CheckSlotsDispCore(route, s, s + 
            call->GetNumberSlots() - 1,core)){
                call->SetFirstSlot(s);
                call->SetLastSlot(s + call->GetNumberSlots() - 1);
                call->SetCore(core);
                flag = true;
                break;
            }
        }
        if(flag)
            break;
    }
}

void CSA::SetInd(CoreOrderIndividual* ind){
    this->ind = ind;
}

void CSA::MSCL(Call* call){
    /*Set Interfering routes to aplly Multicore MSCL*/
    //this->SA::GetResourceAlloc()->SetInterferingRoutes();
    int totalSlots=this->GetTopology()->GetNumSlots(),s,core;
    Route *route = call->GetRoute(), *route_aux;
    int NslotsReq = call->GetNumberSlots(),slot_range = 
    totalSlots - NslotsReq + 1;
    int core_size = this->GetTopology()->GetNumCores(),orNode = 
    route->GetOrNodeId(),desNode = route->GetDeNodeId();
    //Ponteiro que receberá todas as rotas que interferem com route
    std::vector<std::shared_ptr<Route>> RouteInt = this->SA::GetResourceAlloc()
    ->GetInterRoutes(orNode,desNode,0);
    //int a = RouteInt.size();
    int vetCapInic,vetCapFin,si;
    double perda, perdaMin = std::numeric_limits<double>::max();
    Topology* topology = this->GetTopology();
    //Vetor de disponibilidade das rotas que interferem
    bool vetDispInt[totalSlots],vetDispFin[totalSlots];
    //Route* q = RouteInt.at(0);
    //q->print();
    //Route* p = RouteInt.at(1);
    //p->print();
    //route->print();

    //Obtem quais slots podem começar a requisição:
    bool DispFitSi = false;
    //Percorre os núcleos que possuem disponibilidade para alocar a requisição
        for(int e = 0;e < core_size;e++){
            //Verifica quais conjuntos de slots podem ser alocados
            for(s = 0; s < slot_range; s++){
                perda = 0.0;
                DispFitSi = topology->CheckSlotsDispCore(route, s,
                s + NslotsReq - 1,e);
                if(DispFitSi == true){
                    //Percorre rotas interferentes
	 	    for(unsigned int r = 0; r <= RouteInt.size(); r++){
                        if(r == RouteInt.size())
                            route_aux = route;
                        else
                            route_aux = RouteInt.at(0).get();
                        for(int se = 0;se < totalSlots;se++){
				if(!(topology->CheckSlotsDispCore(route_aux,
                                se,se,e))){
					vetDispInt[se] = false;
					vetDispFin[se] = false;
				}
				else{
					vetDispInt[se] = true;
					if(se >= s && se < s + NslotsReq)
                                            vetDispFin[se] = false;
                                        else
                                            vetDispFin[se] = true;
				}
			}
			vetCapInic = 0;
			vetCapFin  = 0;
			//Calcula a capacidade inicial baseada no número de 
                        //formas de alocação,requisições->2,4,8
			for(int b=2; b <= 8; b++){
                            if(b == 2 || b == 4 || b == 8)
                                vetCapInic += this->SA::CalcNumFormAloc(b,
                                vetDispInt,totalSlots);
			}
			//Requisições->2,4,8
			for(int d=2; d <= 8; d++){
			    if(d == 2 || d == 4 || d == 8)
                                vetCapFin += this->SA::CalcNumFormAloc(d,
                                vetDispFin,totalSlots);
			}
							
                            /*
							for(int b=2; b <= 5; b = b + 1){
								  vetCapInic += Heuristics::calcNumFormAloc(b,vetDispInt,Topology::getNumSlots());
							}
							for(int d=2; d <= 5; d = d + 1){
								 vetCapFin += Heuristics::calcNumFormAloc(d,vetDispFin,Topology::getNumSlots());
							}*/
			perda += vetCapInic - vetCapFin;
		    }//Fim da verificação das rotas interferentes
		    if(perda < perdaMin){
		        perdaMin = perda;
		        core = e;
		        si = s;
		    }
		}
            }//Fim da verificação dos slots
        }//Fim da verificação dos núcleos
        if(perdaMin < std::numeric_limits<double>::max()){
            call->SetFirstSlot(si);
            call->SetLastSlot(si+NslotsReq-1);
            call->SetCore(core);
            /*if(numSlotsReq == 2){
                Def::numReq_Acc_2slots.at(core)++;
            }
            if(numSlotsReq == 4){
                Def::numReq_Acc_4slots.at(core)++;
            }
            if(numSlotsReq == 8){
                Def::numReq_Acc_8slots.at(core)++;
            }*/
        }
}



