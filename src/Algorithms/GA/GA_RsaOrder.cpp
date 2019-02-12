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

std::default_random_engine GA_RsaOrder::random_generator(0);

bool GA_RsaOrder::IndividualCompare::operator()(
const std::shared_ptr<IndividualBool> indA, 
const std::shared_ptr<IndividualBool> indB) const {
    
    return (indA->GetBlockProb() > indB->GetBlockProb());
}

GA_RsaOrder::GA_RsaOrder(SimulationType* simul):
simul(simul), numberIndividuals(50), numberGenerations(50),
numNodes(0), probCrossover(0.5), probMutation(0.1), selectedPopulation(0), 
totalPopulation(0) {
    
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
    this->totalPopulation.clear();
    
    this->Crossover();
    
    this->Mutation();
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

SimulationType* GA_RsaOrder::GetSimul() const {
    return simul;
}

void GA_RsaOrder::Crossover() {

}

void GA_RsaOrder::Mutation() {

}
