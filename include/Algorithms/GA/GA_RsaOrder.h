/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GA_RsaOrder.h
 * Author: BrunoVinicius
 *
 * Created on February 11, 2019, 11:02 AM
 */

#ifndef GA_RSAORDER_H
#define GA_RSAORDER_H

#include <vector>
#include <memory>
#include <cassert>
#include <random>

class SimulationType;

#include "IndividualBool.h"

class GA_RsaOrder {

private:
    
    struct IndividualCompare{
        
        bool operator()(const std::shared_ptr<IndividualBool> indA,
                        const std::shared_ptr<IndividualBool> indB) const;
    };
public:
    
    GA_RsaOrder(SimulationType* simul);
    
    virtual ~GA_RsaOrder();
    
    
    void Initialize();
    
    void InitializePopulation();
    
    void CreateNewPopulation();
    
    
    
    const unsigned int GetNumberGenerations() const;

    const unsigned int GetNumberIndividuals() const;

    unsigned int GetNumNodes() const;

    void SetNumNodes(unsigned int numNodes);

    bool GetBoolDistribution();

    double GetProbDistribution();


    SimulationType* GetSimul() const;
    
private:
    
    void Crossover();
    
    void Mutation();

private:
    
    SimulationType* simul;
    
    const unsigned int numberIndividuals;
    
    const unsigned int numberGenerations;
    
    unsigned int numNodes; 
    
    const double probCrossover;
    
    const double probMutation;
    
    std::vector<std::shared_ptr<IndividualBool>> selectedPopulation;
    
    std::vector<std::shared_ptr<IndividualBool>> totalPopulation;
    
    
    static std::default_random_engine random_generator;
    
    std::uniform_int_distribution<int> boolDistribution;
    
    std::uniform_real_distribution<double> probDistribution;
};

#endif /* GA_RSAORDER_H */

