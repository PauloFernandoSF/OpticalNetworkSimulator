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

#include "IndividualBool.h"

class SimulationType;
class IndividualBool;

/**
 * @brief GA algorithm applied for RSA order.
 */
class GA_RsaOrder{

private:
    /**
     * @brief 
     */
    struct IndividualCompare{
        
        bool operator()(const std::shared_ptr<IndividualBool>& indA,
                        const std::shared_ptr<IndividualBool>& indB) const;
    };
    
    friend std::ostream& operator<<(std::ostream& ostream, 
    const GA_RsaOrder* ga_RsaOrder);

public:
    
    GA_RsaOrder(SimulationType* simul);
    
    virtual ~GA_RsaOrder();
    
    
    void Initialize();
    
    void InitializePopulation();
    
    void CreateNewPopulation();
    
    void KeepInitialPopulation();
    
    void SimulateTotalPop();
    
    void SelectPopulation();
    
    void SaveBestWorstIndividuals();
    
    const unsigned int GetNumberGenerations() const;

    const unsigned int GetNumberIndividuals() const;

    unsigned int GetNumNodes() const;

    void SetNumNodes(unsigned int numNodes);

    bool GetBoolDistribution();

    double GetProbDistribution();
    
    unsigned int GetNumTotalPopulation() const;

    SimulationType* GetSimul() const;
    
    unsigned int GetActualGeneration() const;

    void SetActualGeneration(unsigned int actualGeneration);

    IndividualBool* GetWorstIndividual() const;
    
    IndividualBool* GetBestIndividual() const;
    
    IndividualBool* GetIniIndividual(unsigned int index);
    
    const unsigned int GetMaxNumSimulation() const;
    
    
    void ApplyIndividualGene(const IndividualBool* const ind);
    
    void SetIndFitness(IndividualBool* const ind);

private:
    
    void Crossover();
    
    IndividualBool* RoullleteIndividual();
    
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
    
    
    void SetSumFitnessSelectedPop();
    
private:
    
    SimulationType* simul;
    
    const unsigned int numberIndividuals;
    
    const unsigned int numberGenerations;
    
    unsigned int numNodes; //Derived
    
    const double probCrossover;
    
    const double probMutation;
    
    std::vector<std::shared_ptr<IndividualBool>> initialPopulation;
        
    std::vector<std::shared_ptr<IndividualBool>> bestIndividuals;
    
    std::vector<std::shared_ptr<IndividualBool>> worstIndividuals;
    
    const unsigned int numBestIndividuals;
    
    unsigned int actualGeneration;
    
    const unsigned int maxNumSimulation;
    
    double sumFitness;
    
    
    static std::default_random_engine random_generator;
    
    std::uniform_int_distribution<int> boolDistribution; //Derived
    
    std::uniform_real_distribution<double> probDistribution; 
    
    std::uniform_real_distribution<double> fitnessDistribution;
    
public:
    
    std::vector<std::shared_ptr<IndividualBool>> selectedPopulation;
    
    std::vector<std::shared_ptr<IndividualBool>> totalPopulation;
};

#endif /* GA_RSAORDER_H */

