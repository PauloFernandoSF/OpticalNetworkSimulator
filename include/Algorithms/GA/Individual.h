/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Individual.h
 * Author: BrunoVinicius
 *
 * Created on March 8, 2019, 9:45 AM
 */

#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <memory>

class GA;

class Individual {

public:
    
    Individual(GA* ga);
    
    Individual(const std::shared_ptr<const Individual>& orig);
    
    virtual ~Individual();

    
    double GetFitness() const;

    void SetFitness(double fitness);

    unsigned int GetCount() const;

private:
    
    GA* ga;
    
    double fitness;
    
    unsigned int count;
};

#endif /* INDIVIDUAL_H */

