/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GA_RsaOrder.cpp
 * Author: BrunoVinicius
 * 
 * Created on February 11, 2019, 11:02 AM
 */

#include "../../../include/Algorithms/GA/GA_RsaOrder.h"
#include "../../../include/SimulationType/GA_SingleObjective.h"
#include "../../../include/Structure/Topology.h"
#include "../../../include/Algorithms/GA/IndividualBool.h"
#include "../../../include/SimulationType/SimulationType.h"
#include "../../../include/ResourceAllocation/ResourceAlloc.h"
#include "../../../include/Data/Data.h"

std::default_random_engine GA_RsaOrder::random_generator(0);

bool GA_RsaOrder::IndividualCompare::operator()(
const std::shared_ptr<IndividualBool>& indA, 
const std::shared_ptr<IndividualBool>& indB) const {
    
    return (indA->GetBlockProb() < indB->GetBlockProb());
}

std::ostream& operator<<(std::ostream& ostream, 
const GA_RsaOrder* ga_RsaOrder) {
    ostream << "Generation: " << ga_RsaOrder->actualGeneration << std::endl;
    ostream << "Best individual: " << ga_RsaOrder->GetBestIndividual()
            << std::endl;
    ostream << "Worst individual: " << ga_RsaOrder->GetWorstIndividual()
            << std::endl;
    
    return ostream;
}

GA_RsaOrder::GA_RsaOrder(SimulationType* simul):
simul(simul), numberIndividuals(50), numberGenerations(50),
numNodes(0), probCrossover(0.5), probMutation(0.1), selectedPopulation(0), 
totalPopulation(0), bestIndividuals(0), worstIndividuals(0), 
numBestIndividuals(30), actualGeneration(0) {
    
}

GA_RsaOrder::~GA_RsaOrder() {
    
}

void GA_RsaOrder::Initialize() {
    this->SetNumNodes(this->GetSimul()->GetTopology()->GetNumNodes());
    this->boolDistribution = std::uniform_int_distribution<int>(0, 1);
    this->probDistribution = std::uniform_real_distribution<double>(0, 1);
}

void GA_RsaOrder::InitializePopulation() {
    assert(this->selectedPopulation.empty() && this->totalPopulation.empty());
    
    for(unsigned int a = 0; a < this->numberIndividuals; a++){
        this->selectedPopulation.push_back(std::make_shared
                                           <IndividualBool>(this));
    }
}

void GA_RsaOrder::CreateNewPopulation() {
    this->actualGeneration++;
    this->totalPopulation.clear();
    this->Crossover();
    this->Mutation();
}

void GA_RsaOrder::SimulateIndividuals() {
    
    for(auto it: this->totalPopulation){
        
        if(it->GetCount() <= 3){
            this->simul->GetResourceAlloc()->
            SetResourceAllocOrder(it->GetGenes());
            
            //Check if this run is executing the base or the derived function.
            //It has to be the base class function.
            this->simul->Run();
            it->SetBlockProb(this->simul->GetData()->GetPbReq());
        }
        this->simul->GetData()->Initialize();
    }
}

void GA_RsaOrder::SelectPopulation() {
    assert(this->selectedPopulation.empty());
    
    //Order all individuals, with best(smallest) Pb at the end of the vector.
    std::make_heap(this->totalPopulation.begin(), this->totalPopulation.end(),
                   IndividualCompare());
    
    //Select numBestIndividuals best individuals (Block. Prob.)
    for(unsigned int a = 0; a < this->numBestIndividuals; a++){
        this->selectedPopulation.push_back(this->totalPopulation.back());
        this->totalPopulation.pop_back();
    }
    //Select randomly the others.
    std::shuffle(this->totalPopulation.begin(), 
                 this->totalPopulation.end(), this->random_generator);
    while(this->selectedPopulation.size() < this->numberIndividuals){
        this->selectedPopulation.push_back(this->totalPopulation.back());
        this->totalPopulation.pop_back();
    }
    
    //Sort the selected individuals, first worst last best.
    std::make_heap(this->selectedPopulation.begin(), 
                 this->selectedPopulation.end(), IndividualCompare());
    
    this->SaveBestWorstIndividuals();
}

void GA_RsaOrder::SaveBestWorstIndividuals() {
    this->bestIndividuals.push_back(this->selectedPopulation.back());
    this->worstIndividuals.push_back(this->selectedPopulation.front());
}

const unsigned int GA_RsaOrder::GetNumberIndividuals() const {
    return numberIndividuals;
}

const unsigned int GA_RsaOrder::GetNumberGenerations() const {
    return numberGenerations;
}

unsigned int GA_RsaOrder::GetNumNodes() const {
    return numNodes;
}

void GA_RsaOrder::SetNumNodes(unsigned int numNodes) {
    assert(numNodes > 0);
    
    this->numNodes = numNodes;
}

bool GA_RsaOrder::GetBoolDistribution() {
    return (bool) boolDistribution(random_generator);
}

double GA_RsaOrder::GetProbDistribution() {
    return probDistribution(random_generator);
}

unsigned int GA_RsaOrder::GetNumTotalPopulation() const {
    return this->totalPopulation.size();
}

SimulationType* GA_RsaOrder::GetSimul() const {
    return simul;
}

unsigned int GA_RsaOrder::GetActualGeneration() const {
    return actualGeneration;
}

void GA_RsaOrder::SetActualGeneration(unsigned int actualGeneration) {
    this->actualGeneration = actualGeneration;
}

IndividualBool* GA_RsaOrder::GetWorstIndividual() const {
    return this->worstIndividuals.at(this->actualGeneration-1).get();
    //return this->selectedPopulation.front().get();
}

IndividualBool* GA_RsaOrder::GetBestIndividual() const{
    return this->bestIndividuals.at(this->actualGeneration-1).get();
    //return this->selectedPopulation.back().get();
}

void GA_RsaOrder::Crossover() {
    assert(this->selectedPopulation.size() == this->numberIndividuals);
    IndividualBool *auxInd1, *auxInd2;
    
    std::shuffle(this->selectedPopulation.begin(), 
                 this->selectedPopulation.end(), this->random_generator);
    
    while(!this->selectedPopulation.empty()){
        this->totalPopulation.push_back(this->selectedPopulation.back());
        auxInd1 = totalPopulation.back().get();
        this->selectedPopulation.pop_back();
        
        this->totalPopulation.push_back(this->selectedPopulation.back());
        auxInd2 = totalPopulation.back().get();
        this->selectedPopulation.pop_back();
        
        this->GenerateNewIndividuals(auxInd1, auxInd2);
    }
}

void GA_RsaOrder::GenerateNewIndividuals(const IndividualBool* const ind1, 
                                         const IndividualBool* const ind2) {
    //Put condition for choose  the crossover
    this->UniformCrossover(ind1, ind2);
}

void GA_RsaOrder::UniformCrossover(const IndividualBool* const ind1, 
                                   const IndividualBool* const ind2) {
    std::shared_ptr<IndividualBool> newInd1 = 
    std::make_shared<IndividualBool>(this);
    std::shared_ptr<IndividualBool> newInd2 = 
    std::make_shared<IndividualBool>(this);
    double auxProb;
    
    for(unsigned int a = 0; a < this->numNodes; a++){
        for(unsigned int b = 0; b < this->numNodes; b++){
            auxProb = this->GetProbDistribution();
            
            if(auxProb < this->probCrossover){
                newInd1->SetGene(a, b, ind1->GetGene(a, b));
                newInd2->SetGene(a, b, ind2->GetGene(a, b));
            }
            else{
                newInd1->SetGene(a, b, ind2->GetGene(a, b));
                newInd2->SetGene(a, b, ind1->GetGene(a, b));
            }
        }
    }
    
    this->totalPopulation.push_back(newInd1);
    this->totalPopulation.push_back(newInd2);
}

void GA_RsaOrder::Mutation() {
    assert(this->totalPopulation.size() == 2*this->numberIndividuals);
    unsigned int popSize = this->totalPopulation.size();
    std::shared_ptr<IndividualBool> newInd;
    
    for(unsigned int a = 0; a < popSize; a++){
        newInd = std::make_shared<IndividualBool>(this->totalPopulation.at(a));
        this->MutateIndividual(newInd.get());
        this->totalPopulation.push_back(newInd);
    }
}

void GA_RsaOrder::MutateIndividual(IndividualBool* const ind) {
    double auxProb;
    
    for(unsigned int a = 0; a < this->numNodes; a++){
        for(unsigned int b = 0; b < this->numNodes; b++){
            auxProb = this->GetProbDistribution();
            
            if(auxProb < this->probMutation)
                ind->SetGene(a, b, !ind->GetGene(a, b));
        }
    }    
}
