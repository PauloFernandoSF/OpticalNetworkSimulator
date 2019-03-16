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
//doubt, why take from Def?
std::default_random_engine GACoreOrder::random_generator(Def::randomDevice());

bool GACoreOrder::IndividualCompare::operator()(
const std::shared_ptr<CoreOrderIndividual>& indA, 
const std::shared_ptr<CoreOrderIndividual>& indB) const {
    
    return (indA->GetBlockProb() < indB->GetBlockProb());
}

std::ostream& operator<<(std::ostream& ostream, 
const GACoreOrder* ga_CoreOrder) {
    ostream << "Generation: " << ga_CoreOrder->actualGeneration << std::endl;
    ostream << "Best individual: " << ga_CoreOrder->GetBestIndividual()
            << std::endl;
    ostream << "Worst individual: " << ga_CoreOrder->GetWorstIndividual()
            << std::endl;
    
    return ostream;
}

GACoreOrder::GACoreOrder(SimulationType* simul):
simul(simul), numberIndividuals(50), numberGenerations(50),probCrossover(0.5), 
probMutation(0.1), initialPopulation(0), bestIndividuals(0), 
worstIndividuals(0), numBestIndividuals(30), actualGeneration(0),
maxNumSimulation(3), selectedPopulation(0), totalPopulation(0) {
    
}

GACoreOrder::~GACoreOrder() {
    
}

void GACoreOrder::Initialize() {
    //this->SetNumNodes(this->GetSimul()->GetTopology()->GetNumNodes());
    this->boolDistribution = std::uniform_int_distribution<int>(0, 1);
    this->probDistribution = std::uniform_real_distribution<double>(0, 1);
}

void GACoreOrder::InitializePopulation() {
    assert(this->selectedPopulation.empty() && this->totalPopulation.empty());
    
    for(unsigned int a = 0; a < this->numberIndividuals; a++){
        this->selectedPopulation.push_back(std::make_shared
                                           <CoreOrderIndividual>(this));
    }   
}

void GACoreOrder::CreateNewPopulation() {
    this->actualGeneration++;
    this->totalPopulation.clear();
    this->Crossover();
    this->Mutation();
}

void GACoreOrder::KeepInitialPopulation() {
    this->initialPopulation = this->selectedPopulation;
}

void GACoreOrder::SelectPopulation() {
    assert(this->selectedPopulation.empty());
    
    //Order all individuals, with best(smallest) Bp at the end of the vector.
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

void GACoreOrder::SaveBestWorstIndividuals() {
    this->bestIndividuals.push_back(this->selectedPopulation.back());
    this->worstIndividuals.push_back(this->selectedPopulation.front());
}

const unsigned int GACoreOrder::GetNumberIndividuals() const {
    return numberIndividuals;
}

const unsigned int GACoreOrder::GetNumberGenerations() const {
    return numberGenerations;
}

bool GACoreOrder::GetBoolDistribution() {
    return (bool) boolDistribution(random_generator);
}

double GACoreOrder::GetProbDistribution() {
    return probDistribution(random_generator);
}

unsigned int GACoreOrder::GetNumTotalPopulation() const {
    return this->totalPopulation.size();
}

SimulationType* GACoreOrder::GetSimul() const {
    return simul;
}

unsigned int GACoreOrder::GetActualGeneration() const {
    return actualGeneration;
}

void GACoreOrder::SetActualGeneration(unsigned int actualGeneration) {
    this->actualGeneration = actualGeneration;
}

CoreOrderIndividual* GACoreOrder::GetWorstIndividual() const {
    return this->worstIndividuals.at(this->actualGeneration-1).get();
    //return this->selectedPopulation.front().get();
}

CoreOrderIndividual* GACoreOrder::GetBestIndividual() const{
    return this->bestIndividuals.at(this->actualGeneration-1).get();
    //return this->selectedPopulation.back().get();
}

CoreOrderIndividual* GACoreOrder::GetIniIndividual(unsigned int index) {
    return this->initialPopulation.at(index).get();
}

const unsigned int GACoreOrder::GetMaxNumSimulation() const {
    return maxNumSimulation;
}
//Find a way to aplly individual in the net to simulate
void GACoreOrder::ApplyIndividual(const CoreOrderIndividual * const ind) {
    //this->simul->GetResourceAlloc()->SetResourceAllocOrder(ind->GetGenes());
}
//Implement individual functions
void GACoreOrder::SetIndFitness(CoreOrderIndividual * const ind) {
    ind->SetBlockProb(this->simul->GetData()->GetPbReq());
}

void GACoreOrder::Crossover() {
    assert(this->selectedPopulation.size() == this->numberIndividuals);
    CoreOrderIndividual *auxInd1, *auxInd2;
    
    while(this->totalPopulation.size() < this->numberIndividuals){
        auxInd1 = this->RoullleteIndividual();
        auxInd2 = this->RoullleteIndividual();
        
        this->GenerateNewIndividuals(auxInd1, auxInd2);
    }
}

CoreOrderIndividual* GACoreOrder::RoullleteIndividual() {
    double auxDouble = 0.0;
    unsigned int index;
       
    this->fitnessDistribution = std::uniform_real_distribution<double>(0, 
                                this->sumFitness);
    double fitness = this->fitnessDistribution(random_generator);
    
    for(index = 0; index < this->selectedPopulation.size(); index++){
        auxDouble += 1/this->selectedPopulation.at(index)->GetBlockProb();
        
        if(auxDouble > fitness)
            break;
    }
    
    return this->selectedPopulation.at(index).get();
}

void GACoreOrder::GenerateNewIndividuals(const CoreOrderIndividual* const ind1, 
                                         const CoreOrderIndividual* const ind2) {
    //Put condition for choose  the crossover
    this->UniformCrossover(ind1, ind2);
}
//Change to CoreOrder application
void GACoreOrder::UniformCrossover(const CoreOrderIndividual* const ind1, 
                                   const CoreOrderIndividual* const ind2) {
    std::shared_ptr<CoreOrderIndividual> newInd1 = 
    std::make_shared<CoreOrderIndividual>(this);
    std::shared_ptr<CoreOrderIndividual> newInd2 = 
    std::make_shared<CoreOrderIndividual>(this);
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

void GACoreOrder::Mutation() {
    assert(this->totalPopulation.size() == this->numberIndividuals);
    unsigned int popSize = this->totalPopulation.size();
    
    for(unsigned int a = 0; a < popSize; a++){
        this->MutateIndividual(this->totalPopulation.at(a).get());
    }
    
    this->totalPopulation.insert(this->totalPopulation.end(), 
          this->selectedPopulation.begin(), this->selectedPopulation.end());
    
    this->selectedPopulation.clear();
}

void GACoreOrder::MutateIndividual(CoreOrderIndividual* const ind) {
    double auxProb;
    
    for(unsigned int a = 0; a < this->numNodes; a++){
        for(unsigned int b = 0; b < this->numNodes; b++){
            auxProb = this->GetProbDistribution();
            
            if(auxProb < this->probMutation)
                ind->SetGene(a, b, !ind->GetGene(a, b));
        }
    }    
}

void GACoreOrder::SetSumFitnessSelectedPop() {
    double sum = 0.0;
    
    for(auto it: this->selectedPopulation){
        sum += (1 / it->GetBlockProb());
    }
    
    this->sumFitness = sum;
}