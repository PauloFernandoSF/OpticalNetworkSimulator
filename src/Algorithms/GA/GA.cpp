/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GA.cpp
 * Author: BrunoVinicius
 * 
 * Created on February 27, 2019, 10:07 PM
 */

#include "../../../include/Algorithms/GA/GA.h"
#include "../../../include/GeneralClasses/Def.h"

std::default_random_engine GA::random_generator(Def::randomDevice());

bool GA::IndividualCompare::operator()(
const std::shared_ptr<Individual>& indA, 
const std::shared_ptr<Individual>& indB) const {
    
    return (indA->GetFitness() < indB->GetFitness());
}

std::ostream& operator<<(std::ostream& ostream, 
const GA* ga) {
    ostream << "Generation: " << ga->actualGeneration << std::endl;
    ostream << "Best individual: " << ga->GetBestIndividual()
            << std::endl;
    ostream << "Worst individual: " << ga->GetWorstIndividual()
            << std::endl;
    
    return ostream;
}

GA::GA(SimulationType* simul)
:simul(simul), numberIndividuals(50), numberGenerations(50), 
probCrossover(1), probMutation(0.2), numBestIndividuals(30), 
actualGeneration(0), maxNumSimulation(3), sumFitness(0.0),
initialPopulation(0), bestIndividuals(0), worstIndividuals(0),  
selectedPopulation(0), totalPopulation(0) {
    
}

GA::~GA() {
    
}

void GA::Initialize() {
    this->probDistribution = std::uniform_real_distribution<double>(0, 1);
}

void GA::KeepInitialPopulation() {
    this->initialPopulation = this->selectedPopulation;
    std::sort(this->initialPopulation.begin(), 
                   this->initialPopulation.end(), IndividualCompare());
}

void GA::SelectPopulation() {
    
    assert(this->selectedPopulation.empty());
    
    //Order all individuals, with best(smallest) Pb at the end of the vector.
    std::sort(this->totalPopulation.begin(), this->totalPopulation.end(),
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
    std::sort(this->selectedPopulation.begin(), 
                 this->selectedPopulation.end(), IndividualCompare());
}

void GA::SaveIndividuals() {
    this->bestIndividuals.push_back(this->selectedPopulation.back());
    this->worstIndividuals.push_back(this->selectedPopulation.front());
}

const unsigned int GA::GetNumberGenerations() const {
    return numberGenerations;
}

const unsigned int GA::GetNumberIndividuals() const {
    return numberIndividuals;
}

const double GA::GetProbCrossover() const {
    return probCrossover;
}

const double GA::GetProbMutation() const {
    return probMutation;
}

const unsigned int GA::GetMaxNumSimulation() const {
    return maxNumSimulation;
}

void GA::SetSumFitness(double sumFitness) {
    assert(sumFitness > 0);
    this->sumFitness = sumFitness;
}

double GA::GetProbDistribution() {
    return probDistribution(random_generator);
}

unsigned int GA::GetNumTotalPopulation() const {
    return this->totalPopulation.size();
}

SimulationType* GA::GetSimul() const {
    return simul;
}

unsigned int GA::GetActualGeneration() const {
    return actualGeneration;
}

void GA::SetActualGeneration(unsigned int actualGeneration) {
    this->actualGeneration = actualGeneration;
}

void GA::SetSumFitnessSelectedPop() {
    double sum = 0.0;
    
    for(auto it: this->selectedPopulation){
        sum += (it->GetFitness());
    }
    
    this->SetSumFitness(sum);
}

Individual* GA::GetWorstIndividual() const {
    return this->worstIndividuals.at(this->actualGeneration-1).get();
}

Individual* GA::GetBestIndividual() const {
    return this->bestIndividuals.at(this->actualGeneration-1).get();
}

Individual* GA::GetIniIndividual(unsigned int index) {
    assert(index < this->initialPopulation.size());
    return this->initialPopulation.at(index).get();
}

Individual* GA::RouletteIndividual() {
    double auxDouble = 0.0;
    unsigned int index;
    
    this->fitnessDistribution = std::uniform_real_distribution<double>(0, 
                                this->sumFitness);
    double fitness = this->fitnessDistribution(random_generator);
    
    for(index = 0; index < this->selectedPopulation.size(); index++){
        auxDouble += this->selectedPopulation.at(index)->GetFitness();
        
        if(auxDouble > fitness)
            break;
    }
    
    return this->selectedPopulation.at(index).get();
}
