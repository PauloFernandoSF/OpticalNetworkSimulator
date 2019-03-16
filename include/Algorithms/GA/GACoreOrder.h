/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GACoreOrder.h
 * Author: paulofilho
 *
 * Created on 25 de fevereiro de 2019, 12:26
 */

#ifndef GACOREORDER_H
#define GACOREORDER_H

#include <vector>
#include <memory>
#include <cassert>
#include <random>
#include <algorithm>

#include "CoreOrderIndividual.h"

class SimulationType;
class CoreOrderIndividual;

class GACoreOrder {
public:
    GACoreOrder(SimulationType* simul);
    
    virtual ~GACoreOrder();
        
    void Initialize();
    
    void InitializePopulation();
    
    void CreateNewPopulation();
    
    void KeepInitialPopulation();
    
    void SimulateTotalPop();
    
    void SelectPopulation();
    
    void SaveBestWorstIndividuals();
    
    const unsigned int GetNumberGenerations() const;

    const unsigned int GetNumberIndividuals() const;
       
    bool GetBoolDistribution();

    double GetProbDistribution();
    
    unsigned int GetNumTotalPopulation() const;

    SimulationType* GetSimul() const;
    
    unsigned int GetActualGeneration() const;

    void SetActualGeneration(unsigned int actualGeneration);

    CoreOrderIndividual* GetWorstIndividual() const;
    
    CoreOrderIndividual* GetBestIndividual() const;
    
    CoreOrderIndividual* GetIniIndividual(unsigned int index);
    
    const unsigned int GetMaxNumSimulation() const;
    
    
    void ApplyIndividual(const CoreOrderIndividual* const ind);
    
    void SetIndFitness(CoreOrderIndividual* const ind);

private:
    
    void Crossover();
    
    CoreOrderIndividual* RoullleteIndividual();
    
    void GenerateNewIndividuals(const CoreOrderIndividual* const ind1,
                                const CoreOrderIndividual* const ind2);
    
    void OnePointCrossover(const CoreOrderIndividual* const ind1,
                           const CoreOrderIndividual* const ind2);
    
    void TwoPointCrossover(const CoreOrderIndividual* const ind1,
                           const CoreOrderIndividual* const ind2);
    
    void UniformCrossover(const CoreOrderIndividual* const ind1,
                          const CoreOrderIndividual* const ind2);

    void Mutation();
    
    void MutateIndividual(CoreOrderIndividual* const ind);
    
    
    void SetSumFitnessSelectedPop();
    
private:
    
    SimulationType* simul;
    
    const unsigned int numberIndividuals;
    
    const unsigned int numberGenerations;
           
    const double probCrossover;
    
    const double probMutation;
    
    std::vector<std::shared_ptr<CoreOrderIndividual>> initialPopulation;
        
    std::vector<std::shared_ptr<CoreOrderIndividual>> bestIndividuals;
    
    std::vector<std::shared_ptr<CoreOrderIndividual>> worstIndividuals;
    
    const unsigned int numBestIndividuals;
    
    unsigned int actualGeneration;
    
    const unsigned int maxNumSimulation;
    
    double sumFitness;
    
    static std::default_random_engine random_generator;
    
    std::uniform_int_distribution<int> boolDistribution; //Derived
    
    std::uniform_real_distribution<double> probDistribution; 
    
    std::uniform_real_distribution<double> fitnessDistribution;
    
public:
    
    std::vector<std::shared_ptr<CoreOrderIndividual>> selectedPopulation;
    
    std::vector<std::shared_ptr<CoreOrderIndividual>> totalPopulation;
private:
    struct IndividualCompare{
        
        bool operator()(const std::shared_ptr<CoreOrderIndividual>& indA,
                        const std::shared_ptr<CoreOrderIndividual>& indB) const;
    };
    
    friend std::ostream& operator<<(std::ostream& ostream, 
    const GACoreOrder* ga_CoreOrder);
};

#endif /* GACOREORDER_H */

