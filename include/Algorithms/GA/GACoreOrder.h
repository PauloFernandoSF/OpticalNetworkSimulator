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


#include "GA.h"
#include "CoreOrderIndividual.h"

class SimulationType;

class GACoreOrder: public GA {
public:
    /**
     * @brief Default constructor for GA Core Order.
     * @param simul SimulationType that owns this GACoreOrder.
     */
    GACoreOrder(SimulationType* simul);
    /**
     * @brief Default destructor for GACoreOrder.
     */
    virtual ~GACoreOrder();
    /**
     * @brief Initialize the base class, set the number of cores and 
     * requisitions classes, that will be required to construct the matrix of 
     * genes.
     */
    void Initialize() override;
    /**
     * @brief Function to create the initial population in the selected 
     * population container. This GA create individuals of the 
     * CoreOrderIndividual type. 
     */
    void InitializePopulation() override;
    /**
     * @brief Call the functions of crossover and mutation to create a new
     * population.
     */
    void CreateNewPopulation() override;
    /**
     * @brief Get the number of cores(columns) of the matrix.
     */
    unsigned int GetNumCores();
    /**
     * @brief Set the number of cores(columns) of the matrix.
     */
    void SetNumCores(unsigned int cores);
    /**
     * @brief Get the number of requisitions classes(lines) of the matrix.
     */
    unsigned int GetNumReq();
    /**
     * @brief Set the number of requisitions classes(lines) of the matrix.
     */
    void SetNumReq(unsigned int req);
    /**
     * @brief Apply the matrix(individual)on the network to specify the order to
     * try the spectral allocation based on requisition classes.
     * @param ind Specified individual.
     */
    void ApplyIndividual(Individual* ind) override;
    
    void SetIndParameters(Individual* ind) override;
    /**
     * @brief Calculate and set Fitness values to all selected individuals,based 
     * on best Bp individual.
    */
    void SetSelectedPopFitness() override;
    /**
     * @brief Calculate and set Fitness values to total population individuals,
     * based on best Bp individual.
    */
    void SetTotalPopFitness() override;
    
private:
    /**
     * @brief Function to create new individuals by crossover.
     * Uses the roulette to choose the parents.
     */
    void Crossover();
    /**
     * @brief Function to generate two new individuals of two specified 
     * parents.
     * @param ind1 First parent.
     * @param ind2 Second parent.
     */
    void GenerateNewIndividuals(const CoreOrderIndividual* const ind1,
                                const CoreOrderIndividual* const ind2);
    /**
     * @brief One point crossover, in which two parents generate two new
     * individuals. A line index of the matrix is selected. One new individual 
     * will receive the genes of the first parent from 0 to the selected line 
     * index, and of the second from that line index to the end. The other will 
     * receive the opposite genes structure.
     * @param ind1 First parent.
     * @param ind2 Second parent.
     */
    void OnePointCrossover(const CoreOrderIndividual* const ind1,
                           const CoreOrderIndividual* const ind2);
    /**
     * @brief Two point crossover, in which two parents generate two new
     * individuals. Two index of the genes is selected. One new individual will
     * receive the genes of the first parent from 0 to the selected first index
     * and the second index to the end. The other will receive the opposite 
     * genes structure.
     * @param ind1 First parent.
     * @param ind2 Second parent.
     */
    void TwoPointCrossover(const CoreOrderIndividual* const ind1,
                           const CoreOrderIndividual* const ind2);
    /**
     * @brief Uniform crossover, in which two parents generate two new
     * individuals. the crossover is done by gene, in which the first new
     * individual has a crossover probability to receive the gene of the first
     * parent. The other new individual will receive the gene of the other 
     * parent.
     * @param ind1 First parent.
     * @param ind2 Second parent.
     */
    void UniformCrossover(const CoreOrderIndividual* const ind1,
                          const CoreOrderIndividual* const ind2);
    /**
     * @brief Apply the mutation in all selected population,until double the 
     * population.
     */
    void Mutation();
    /**
     * @brief Apply the mutation in a specified individual. Each gene of this 
     * individual has the mutation probability to be generated randomly.
     * @param ind Specified individual.
     */
    void MutateIndividual(CoreOrderIndividual* const ind);
    
private:
    /**
     * @brief Number of cores in the network.
     */
    unsigned int numCores;
    /*
     * @brief Number of different requisitions classes that can arrive 
     * in the network.
     */
    unsigned int numReq;
=======
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

