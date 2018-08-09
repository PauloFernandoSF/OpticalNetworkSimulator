/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SimulationType.h
 * Author: bruno
 *
 * Created on August 2, 2018, 3:50 PM
 */

#ifndef SIMULATIONTYPE_H
#define SIMULATIONTYPE_H

#include <memory>
#include <boost/make_unique.hpp>

class Parameters;
class Options;
class Data;
class Topology;
class InputOutput;

/**
 * @brief Base class for simulation objects
 */
class SimulationType {
public:
    SimulationType(unsigned int simulIndex);
    SimulationType(const SimulationType& orig);
    virtual ~SimulationType();
    
    /**
     * @brief Runs a simulation with specified parameters
     */
    virtual void run() = 0;
    /**
     * @brief Load parameters to the simulation from the terminal
     */
    virtual void load() = 0;    
    /**
     * @brief Load parameters to the simulation from a file
     */
    virtual void LoadFile();    
    /**
     * @brief Print the results in the terminal
     */
    virtual void print() = 0;    
    /**
     * @brief Save the results in files
     */
    virtual void save() = 0;    
    /**
     * @brief Prints a description of the simulation
     */
    virtual void help() = 0;
    
    /**
     * @brief
     * @return 
     */
    Parameters* GetParameters() const;
    /**
     * @brief
     * @param parameters
     */
    void SetParameters(std::shared_ptr<Parameters> parameters);
    /**
     * @brief
     * @return 
     */
    Options* GetOptions() const;
    /**
     * @brief 
     * @param options
     */
    void SetOptions(std::shared_ptr<Options> options);
    /**
     * @brief
     * @return 
     */
    Data* GetData() const;
    /**
     * @brief
     * @param data
     */
    void SetData(std::unique_ptr<Data> data);
    /**
     * @brief
     * @return 
     */
    Topology* GetTopology() const;
    /**
     * @brief
     * @param topology
     */
    void SetTopology(std::shared_ptr<Topology> topology);
    /**
     * @brief
     * @return 
     */
    InputOutput* GetInputOutput() const;
    /**
     * @brief
     * @param inputOutput
     */
    void SetInputOutput(std::unique_ptr<InputOutput> inputOutput);

private:
    const unsigned int simulationIndex;
    /**
     * @brief pointer to an Parameters object used in this simulation
     */
    std::shared_ptr<Parameters> parameters;
    /**
     * @brief pointer to an Options object used in this simulation
     */
    std::shared_ptr<Options> options;
    /**
     * @brief pointer to an Data object used in this simulation
     */
    std::unique_ptr<Data> data;
    /**
     * @brief pointer to Topology object used in this simulation
     */
    std::shared_ptr<Topology> topology;
    /**
     * @brief pointer to InputOutput object used in this simulation
     */
    std::unique_ptr<InputOutput> inputOutput;
};

#endif /* SIMULATIONTYPE_H */

