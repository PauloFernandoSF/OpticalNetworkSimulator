/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GA.h
 * Author: BrunoVinicius
 *
 * Created on February 27, 2019, 10:07 PM
 */

#ifndef GA_H
#define GA_H

class SimulationType;

#include <vector>
#include <memory>
#include <cassert>
#include <random>
#include <algorithm>

#include "IndividualBool.h"

class GA {
    
private:
    /**
     * @brief 
     */
    struct IndividualCompare{
        
        bool operator()(const std::shared_ptr<IndividualBool>& indA,
                        const std::shared_ptr<IndividualBool>& indB) const;
    };
    
    friend std::ostream& operator<<(std::ostream& ostream, 
    const GA* ga);

public:
    
    GA(SimulationType* simul);
    
    virtual ~GA();

    
    virtual void Initialize();
    
    virtual void InitializePopulation() = 0;
    
    virtual void CreateNewPopulation();
    
    void KeepInitialPopulation();
    
    void SelectPopulation();
    
    virtual void SaveIndividuals();
    
    
    const unsigned int GetNumberGenerations() const;

    const unsigned int GetNumberIndividuals() const;
    
    const double GetProbCrossover() const;

    const double GetProbMutation() const;

    const unsigned int GetMaxNumSimulation() const;
    
    void SetSumFitness(double sumFitness);

    
    double GetProbDistribution();
    
    unsigned int GetNumTotalPopulation() const;

    SimulationType* GetSimul() const;
    
    unsigned int GetActualGeneration() const;
    
    void SetActualGeneration(unsigned int actualGeneration);

    void SetSumFitnessSelectedPop();
    
    
    IndividualBool* GetWorstIndividual() const;
    
    IndividualBool* GetBestIndividual() const;
    
    IndividualBool* GetIniIndividual(unsigned int index);
    
    
    virtual void ApplyIndividualGene(const IndividualBool* const ind) = 0;
    
    virtual void SetIndFitness(IndividualBool* const ind) = 0;
    
    IndividualBool* RoullleteIndividual();
    
private:
    
    SimulationType* simul;
    
    const unsigned int numberIndividuals;
    
    const unsigned int numberGenerations;
    
    const double probCrossover;
    
    const double probMutation;
    
    
    std::vector<std::shared_ptr<IndividualBool>> initialPopulation;
        
    std::vector<std::shared_ptr<IndividualBool>> bestIndividuals;
    
    std::vector<std::shared_ptr<IndividualBool>> worstIndividuals;
    
    
    const unsigned int numBestIndividuals;
    
    unsigned int actualGeneration;
    
    const unsigned int maxNumSimulation;
    
    double sumFitness;
    
    
    std::uniform_real_distribution<double> probDistribution; 
    
    std::uniform_real_distribution<double> fitnessDistribution;
    
public:
    
    std::vector<std::shared_ptr<IndividualBool>> selectedPopulation;
    
    std::vector<std::shared_ptr<IndividualBool>> totalPopulation;
    
    static std::default_random_engine random_generator;
};

#endif /* GA_H */

