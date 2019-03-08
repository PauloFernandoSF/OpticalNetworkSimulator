/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Individual.cpp
 * Author: BrunoVinicius
 * 
 * Created on March 8, 2019, 9:45 AM
 */

#include "../../../include/Algorithms/GA/Individual.h"

Individual::Individual(GA* ga)
:ga(ga), fitness(0.0), count(0) {
    
}

Individual::Individual(const std::shared_ptr<const Individual>& orig)
:ga(orig->ga), fitness(0.0), count(0) {
    
}

Individual::~Individual() {
    
}

double Individual::GetFitness() const {
    return fitness;
}

void Individual::SetFitness(double fitness) {
    this->fitness = fitness;
}

unsigned int Individual::GetCount() const {
    return count;
}
