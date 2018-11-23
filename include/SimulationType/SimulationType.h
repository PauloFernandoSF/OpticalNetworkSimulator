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

class Parameters;
class Options;
class Data;
class Topology;
class InputOutput;
class Traffic;
class CallGenerator;
class RSA;

/**
 * @brief Base class for Simulations objects.
 */
class SimulationType {
public:
    /**
     * @brief Standard constructor for a SimulationType object.
     * @param simulIndex index of this simulation.
     */
    SimulationType(unsigned int simulIndex);
    /**
     * @brief Copy constructor for a SimulationType object.
     * @param orig original SimulationType object.
     */
    SimulationType(const SimulationType& orig);
    /**
     * @brief Virtual destructor of a SimulationType object.
     */
    virtual ~SimulationType();
    
    /**
     * @brief Runs a simulation with specified parameters.
     */
    virtual void Run();
    /**
     * @brief Load parameters to the simulation from the terminal.
     */
    virtual void Load();
    /**
     * @brief Load parameters, options and such,
     * to the simulation from a .txt file.
     */
    virtual void LoadFile();
    /**
     * @brief Sets SimulationType additional settings for this simulation,
     * as maximum length and initial cost for the links in topology.
     */
    virtual void AdditionalSettings();
    /**
     * @brief Print this simulation in terminal.
     */
    virtual void Print();
    /**
     * @brief Save the results in .txt files.
     */
    virtual void Save() = 0;
    /**
     * @brief Prints a description of the simulation.
     */
    virtual void Help() = 0;
    
    /**
     * @brief Returns the simulation index
     * @return Simulation index
     */
    const unsigned int GetSimulationIndex() const;
    /**
     * @brief Returns a pointer to a Parameters object 
     * in this simulation
     * @return pointer to a Parameters object
     */
    Parameters* GetParameters() const;
    /**
     * @brief Sets a pointer to the Parameters object 
     * in this simulation with ownership 
     * @param parameters smart point for Parameters object
     */
    void SetParameters(std::shared_ptr<Parameters> parameters);
    /**
     * @brief Returns a pointer to a Options object 
     * in this simulation
     * @return pointer to a Options object
     */
    Options* GetOptions() const;
    /**
     * @brief Sets a pointer to the Options object 
     * in this simulation with ownership
     * @param options smart point for Options object
     */
    void SetOptions(std::shared_ptr<Options> options);
    /**
     * @brief Returns a pointer to a Data object 
     * in this simulation
     * @return pointer to a Data object
     */
    Data* GetData() const;
    /**
     * @brief Sets a pointer to the Options object 
     * in this simulation (object ownership transfered)
     * @param data pointer to a Data object
     */
    void SetData(std::unique_ptr<Data> data);
    /**
     * @brief Returns a pointer to a Topology object 
     * used in this simulation
     * @return pointer to a Topology object
     */
    Topology* GetTopology() const;
    /**
     * @brief Sets a pointer to the Topology object 
     * used in this simulation (with ownership)
     * @param topology pointer to a Topology object
     */
    void SetTopology(std::shared_ptr<Topology> topology);
    /**
     * @brief Returns a pointer to a InputOutput object 
     * used in this simulation.
     * @return pointer to a InputOutput object.
     */
    InputOutput* GetInputOutput() const;
    /**
     * @brief Sets a pointer to the InputOutput object 
     * in this simulation (object ownership transfered).
     * @param inputOutput pointer to a InputOutput object.
     */
    void SetInputOutput(std::unique_ptr<InputOutput> inputOutput);
    /**
     * @brief Returns a pointer to a Traffic object
     * used in this simulation.
     * @return pointer to a Traffic object.
     */
    Traffic* GetTraffic() const;
    /**
     * @brief Sets a pointer to the Traffic object 
     * in this simulation (share ownership).
     * @param traffic pointer to a Traffic object.
     */
    void SetTraffic(std::shared_ptr<Traffic> traffic);
    
    CallGenerator* GetCallGenerator() const;

    void SetCallGenerator(std::shared_ptr<CallGenerator> callGenerator);

private:
    
    void InitializeAll();
    
    void Simulate();
    
    void FinalizeAll();

public:
    
    double numberRequests;

private:
    /**
     * @brief Index of the simulation
     */
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
    /**
     * @brief pointer to Traffic object used in this simulation
     */
    std::shared_ptr<Traffic> traffic;
    /**
     * @brief pointer to a CallGenerator object.
     */
    std::shared_ptr<CallGenerator> callGenerator;
    
    std::shared_ptr<RSA> rsaAlgorithm;
};

#endif /* SIMULATIONTYPE_H */

