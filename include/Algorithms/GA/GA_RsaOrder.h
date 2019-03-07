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
#include <algorithm>

#include "GA.h"
#include "IndividualBool.h"

class SimulationType;

/**
 * @brief GA algorithm applied for RSA order.
 */
class GA_RsaOrder : public GA {

public:
    
    GA_RsaOrder(SimulationType* simul);
    
    virtual ~GA_RsaOrder();
    
    
    void Initialize() override;
    
    void InitializePopulation() override;
    
    void CreateNewPopulation() override;

    
    unsigned int GetNumNodes() const;

    void SetNumNodes(unsigned int numNodes);

    bool GetBoolDistribution();
    
    
    void ApplyIndividualGene(const IndividualBool* const ind) override;
    
    void SetIndFitness(IndividualBool* const ind) override;

private:
    
    void Crossover();
    
    void GenerateNewIndividuals(const IndividualBool* const ind1,
                                const IndividualBool* const ind2);
    
    void OnePointCrossover(const IndividualBool* const ind1,
                           const IndividualBool* const ind2);
    
    void TwoPointCrossover(const IndividualBool* const ind1,
                           const IndividualBool* const ind2);
    
    void UniformCrossover(const IndividualBool* const ind1,
                          const IndividualBool* const ind2);

    void Mutation();
    
    void MutateIndividual(IndividualBool* const ind);
    
private:
    
    unsigned int numNodes;
    
    std::uniform_int_distribution<int> boolDistribution;
};

#endif /* GA_RSAORDER_H */

