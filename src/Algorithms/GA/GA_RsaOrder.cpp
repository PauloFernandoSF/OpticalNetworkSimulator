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
#include "../../../include/GeneralClasses/Def.h"
#include "../../../include/ResourceAllocation/ResourceAlloc.h"
#include "../../../include/Data/Data.h"

std::default_random_engine GA_RsaOrder::random_generator(Def::randomDevice());

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
simul(simul), numberIndividuals(50), numberGenerations(50), numNodes(0), 
probCrossover(0.5), probMutation(0.1), initialPopulation(0), bestIndividuals(0), 
worstIndividuals(0), numBestIndividuals(30), actualGeneration(0),
maxNumSimulation(3), selectedPopulation(0), totalPopulation(0) {
    
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

void GA_RsaOrder::KeepInitialPopulation() {
    this->initialPopulation = this->selectedPopulation;
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

IndividualBool* GA_RsaOrder::GetIniIndividual(unsigned int index) {
    return this->initialPopulation.at(index).get();
}

const unsigned int GA_RsaOrder::GetMaxNumSimulation() const {
    return maxNumSimulation;
}

void GA_RsaOrder::ApplyIndividualGene(const IndividualBool * const ind) {
    this->simul->GetResourceAlloc()->SetResourceAllocOrder(ind->GetGenes());
}

void GA_RsaOrder::SetIndFitness(IndividualBool * const ind) {
    ind->SetBlockProb(this->simul->GetData()->GetPbReq());
}

void GA_RsaOrder::Crossover() {
    assert(this->selectedPopulation.size() == this->numberIndividuals);
    IndividualBool *auxInd1, *auxInd2;
    
    while(this->totalPopulation.size() < this->numberIndividuals){
        auxInd1 = this->RoullleteIndividual();
        auxInd2 = this->RoullleteIndividual();
        
        this->GenerateNewIndividuals(auxInd1, auxInd2);
    }
}

IndividualBool* GA_RsaOrder::RoullleteIndividual() {
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
    assert(this->totalPopulation.size() == this->numberIndividuals);
    unsigned int popSize = this->totalPopulation.size();
    
    for(unsigned int a = 0; a < popSize; a++){
        this->MutateIndividual(this->totalPopulation.at(a).get());
    }
    
    this->totalPopulation.insert(this->totalPopulation.end(), 
          this->selectedPopulation.begin(), this->selectedPopulation.end());
    
    this->selectedPopulation.clear();
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

void GA_RsaOrder::SetSumFitnessSelectedPop() {
    double sum = 0.0;
    
    for(auto it: this->selectedPopulation){
        sum += (1 / it->GetBlockProb());
    }
    
    this->sumFitness = sum;
}
