/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GACoreOrder.cpp
 * Author: paulofilho
 * 
 * Created on 25 de fevereiro de 2019, 12:26
 */

#include "../../../include/Algorithms/GA/GACoreOrder.h"
#include "../../../include/Structure/Topology.h"
#include "../../../include/ResourceAllocation/ResourceAlloc.h"
#include "../../../include/Data/Data.h"
#include "../../../include/SimulationType/GA_SingleObjective.h"
#include "../../../include/Calls/Traffic.h"
#include "../../../include/GeneralClasses/Def.h"

GACoreOrder::GACoreOrder(SimulationType* simul):GA(simul),numCores(0),numReq(0) 
{
}

GACoreOrder::~GACoreOrder() {
}

void GACoreOrder::Initialize(){
    GA::Initialize();
    this->SetNumCores(this->GetSimul()->GetTopology()->GetNumCores());
    this->SetNumReq(this->GetSimul()->GetTraffic()->GetRequisitionClasses());
}

void GACoreOrder::InitializePopulation(){
    assert(this->selectedPopulation.empty() && this->totalPopulation.empty());
    for(unsigned int a = 0; a < this->GetNumberIndividuals(); a++){
        this->selectedPopulation.push_back(std::make_shared
                                           <CoreOrderIndividual>(this));
        //this->selectedPopulation.push_back(NULL);
    }
}

void GACoreOrder::SetNumCores(unsigned int cores){
    this->numCores = cores;
}

unsigned int GACoreOrder::GetNumCores(){
    return this->numCores;
}

void GACoreOrder::SetNumReq(unsigned int req){
    this->numReq = req;
}

unsigned int GACoreOrder::GetNumReq(){
    return this->numReq;
}
//FIX IT TO MY APP
void GACoreOrder::ApplyIndividual(Individual* ind){
    CoreOrderIndividual* indCore = dynamic_cast<CoreOrderIndividual*>(ind);
    this->GetSimul()->GetResourceAlloc()->GetSpecAlloc()->SetInd(indCore);
}

void GACoreOrder::SetIndParameters(Individual* ind){
    double blockProb = this->GetSimul()->GetData()->GetPbReq();
    CoreOrderIndividual* indCore = dynamic_cast<CoreOrderIndividual*>(ind);
    
    indCore->SetBlockProb(blockProb);
}

void GACoreOrder::CreateNewPopulation(){
    SimulationType* single = this->GetSimul();
    GA_SingleObjective* singleObjective = dynamic_cast<GA_SingleObjective*>(single);
    
    this->totalPopulation.clear();
    this->SetSumFitnessSelectedPop();
    this->Crossover();
    //Select numBestIndividuals based on Bp and the rest randomly
    singleObjective->RunTotalPop();
    singleObjective->GetGA()->SelectPopulation();
    this->Mutation();
 }

void GACoreOrder::SetSelectedPopFitness() {
    double bestPb = Def::Max_Double;
    CoreOrderIndividual* auxInd;
    
    //Find the best blocking probability of the selectedPop container
    for(auto it: this->selectedPopulation){
        auxInd = dynamic_cast<CoreOrderIndividual*>(it.get());
        
        if(bestPb > auxInd->GetBlockProb())
            bestPb = auxInd->GetBlockProb();
    }
    
    for(auto it: this->selectedPopulation){
        auxInd = dynamic_cast<CoreOrderIndividual*>(it.get());
        auxInd->SetFitness(1.0 / (bestPb + auxInd->GetBlockProb()));
    }
}

void GACoreOrder::SetTotalPopFitness() {
    double bestPb = Def::Max_Double;
    CoreOrderIndividual* auxInd;
    
    //Find the best blocking probability of the selectedPop container
    for(auto it: this->totalPopulation){
        auxInd = dynamic_cast<CoreOrderIndividual*>(it.get());
        
        if(bestPb > auxInd->GetBlockProb())
            bestPb = auxInd->GetBlockProb();
    }
    
    for(auto it: this->totalPopulation){
        auxInd = dynamic_cast<CoreOrderIndividual*>(it.get());
        auxInd->SetFitness(1.0 / (bestPb + auxInd->GetBlockProb()));
    }
}

void GACoreOrder::Crossover() {
    assert(this->selectedPopulation.size() == this->GetNumberIndividuals());
    CoreOrderIndividual *auxInd1, *auxInd2;
    
    while(this->totalPopulation.size() < this->GetNumberIndividuals()){
        auxInd1 = dynamic_cast<CoreOrderIndividual*>(this->RouletteIndividual());
        do{
            auxInd2 = dynamic_cast<CoreOrderIndividual*>
                      (this->RouletteIndividual());
        }while(auxInd1 == auxInd2);
        
        this->GenerateNewIndividuals(auxInd1, auxInd2);
    }
    this->totalPopulation.insert(this->totalPopulation.end(), 
          this->selectedPopulation.begin(), this->selectedPopulation.end());
    
    this->selectedPopulation.clear();
}

void GACoreOrder::GenerateNewIndividuals(const CoreOrderIndividual* const ind1, 
                                         const CoreOrderIndividual* const ind2) {
    //Put condition for choose  the crossover
    this->UniformCrossover(ind1, ind2);
}

void GACoreOrder::UniformCrossover(const CoreOrderIndividual* const ind1, 
                                   const CoreOrderIndividual* const ind2) {
    std::shared_ptr<CoreOrderIndividual> newInd1 = 
    std::make_shared<CoreOrderIndividual>(this);
    std::shared_ptr<CoreOrderIndividual> newInd2 = 
    std::make_shared<CoreOrderIndividual>(this);
    //double auxProb;
    unsigned int crossoverPoint = rand()%(this->numReq-1);
    for(unsigned int a = 0; a < this->numReq; a++){
        for(unsigned int b = 0; b < this->numCores; b++){
            
            //auxProb = this->GetProbDistribution();
            if(a >= crossoverPoint+1){
                newInd1->SetGene(a,b,ind2->GetGene(a,b));
                newInd2->SetGene(a,b,ind1->GetGene(a,b));
            }
            else{
                newInd1->SetGene(a,b,ind1->GetGene(a,b));
                newInd2->SetGene(a,b,ind2->GetGene(a,b));
            }
            
        }
    }
    
    this->totalPopulation.push_back(newInd1);
    this->totalPopulation.push_back(newInd2);
    
    
}

void GACoreOrder::Mutation() {
    assert(this->selectedPopulation.size() == this->GetNumberIndividuals());
    unsigned int popSize = this->selectedPopulation.size();
    std::shared_ptr<CoreOrderIndividual> newInd;
    
    //Create a copy of each individual generated by the crossover
    for(unsigned int a = 0; a < popSize; a++){
        //newInd = std::make_shared<CoreOrderIndividual>(std::static_pointer_cast
        //<CoreOrderIndividual>(this->totalPopulation.at(a)));
        this->totalPopulation.at(a) = this->selectedPopulation.at(a);
    }
    
    //Apply the mutation only in the copies created.
    for(unsigned int a = 0; a < popSize; a++){
        this->MutateIndividual(dynamic_cast<CoreOrderIndividual*>
                               (this->selectedPopulation.at(a).get()));
    }
    
    this->totalPopulation.insert(this->totalPopulation.end(), 
          this->selectedPopulation.begin(), this->selectedPopulation.end());
    
    this->selectedPopulation.clear();
}

void GACoreOrder::MutateIndividual(CoreOrderIndividual* const ind) {
    double auxProb;
    unsigned int pos_1,pos_2,aux_1,aux_2;
    for(unsigned int a = 0; a < this->numReq; a++){
        for(unsigned int b = 0; b < this->numCores; b++){
            auxProb = this->GetProbDistribution();
            
            if(auxProb < this->GetProbMutation()){
                pos_1 = b;
                do
                    pos_2 = rand()%this->numCores;
                while(pos_1 == pos_2); 
                aux_1 = ind->GetGene(a, pos_1);
                aux_2 = ind->GetGene(a,pos_2);
                ind->SetGene(a,pos_1,aux_2);
                ind->SetGene(a,pos_2,aux_1);
            }
        }
    }
}