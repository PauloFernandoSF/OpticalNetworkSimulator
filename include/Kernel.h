/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Kernel.h
 * Author: bruno
 *
 * Created on August 2, 2018, 3:42 PM
 */

#ifndef KERNEL_H
#define KERNEL_H

#include <vector>
#include <memory>

class SimulationType;

/**
 * @brief The Kernel class is responsible for creating the
 * simulations, runs those simulations created and to
 * output the results of those simulations.
 */
class Kernel {
public:
    /**
     * @brief Standard constructor for a Kernel object.
     * @param numSimulations total number of 
     * simulations for this Kernel.
     */
    Kernel(int numSimulations);
    /**
     * @brief Copy constructor for a Kernel object.
     * @param orig original Kernel object.
     */
    Kernel(const Kernel& orig);
    /**
     * @brief Default destructor of a Kernel object
     */
    virtual ~Kernel();
    
    /**
     * @brief Runs the Kernel functions.
     * Three steps are done, each one for all simulation.
     */
    void Run();    
    /**
     * @brief First step called by the Kernel object.
     * Consists in create the simulations and load
     * the information needed.
     */
    void Pre_Simulation();    
    /**
     * @brief
     */
    void Simulation();    
    /**
     * @brief
     */
    void Pos_Simulation();

private:
    /**
     * @brief Total number of simulations in this kernel.
     */
    const unsigned int numberSimulations;
    /**
     * @brief Vector with all pointers to SimulationType objects.
     */
    std::vector<std::shared_ptr<SimulationType>> simulations;
};

#endif /* KERNEL_H */

