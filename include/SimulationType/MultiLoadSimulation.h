/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MultiLoadSimulation.h
 * Author: bruno
 *
 * Created on August 8, 2018, 7:18 PM
 */

#ifndef MULTILOADSIMULATION_H
#define MULTILOADSIMULATION_H

#include "SimulationType.h"

#include <iostream>

/**
 * @brief Derived class from SimulationType.
 * This type of simulation runs for a specified number 
 * of load points, simulating for each one.
 */
class MultiLoadSimulation : public SimulationType {
public:
    /**
     * @brief Standard constructor for a MultiLoadSimulation object.
     * @param simulIndex index of this simulation.
     */
    MultiLoadSimulation(unsigned int simulIndex);
    /**
     * @brief Copy constructor for a MultiLoadSimulation object.
     * @param orig original MultiLoadSimulation object.
     */
    MultiLoadSimulation(const MultiLoadSimulation& orig);
    /**
     * @brief Destructor of a MultiLoadSimulation object.
     */
    virtual ~MultiLoadSimulation();
    
    /**
     * @brief Runs a simulation with specified parameters.
     */
    void Run() override;
    /**
     * @brief Load parameters to the simulation from the terminal.
     */
    void Load() override;
    /**
     * @brief Load parameters, options and others
     * to the simulation, from a .txt file.
     */
    void LoadFile() override;
    /**
     * @brief Print this simulation in terminal.
     */
    void Print() override;
    /**
     * @brief Save the results in .txt files.
     */
    void Save() override;
    /**
     * @brief Prints a description of the simulation.
     */
    void Help() override;
    
private:
    
};

#endif /* MULTILOADSIMULATION_H */

