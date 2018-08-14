/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InputOutput.h
 * Author: bruno
 *
 * Created on August 8, 2018, 8:14 PM
 */

#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

#include <fstream>

class SimulationType;

/**
 * @brief The InputOutput class is responsible for ready/write
 * in simulation files.
 */
class InputOutput {
public:
    /**
     * @brief Standard constructor for a InputOutput object.
     * @param simulType SimulationType object that owns 
     * this InputOutput.
     */
    InputOutput(SimulationType* simulType);
    /**
     * @brief Copy constructor for a InputOutput object.
     * @param orig original InputOutput object.
     */
    InputOutput(const InputOutput& orig);
    /**
     * @brief Virtual destructor of a InputOutput object.
     */
    virtual ~InputOutput();
    
    /**
     * @brief Function responsible for access the Parameters file.
     * @param parameters stream that operates in Parameters file.
     */
    void LoadParameters(std::ifstream& parameters);
    /**
     * @brief Function responsible for access the Options file.
     * @param options stream that operates in Options file.
     */
    void LoadOptions(std::ifstream& options);
    /**
     * @brief Function responsible for access the Topology file.
     * @param topology stream that operates in Topology file.
     */
    void LoadTopology(std::ifstream& topology);
    /**
     * @brief Function responsible for access the Traffic file.
     * @param traffic stream that operates in Traffic file.
     */
    void LoadTraffic(std::ifstream& traffic);
    
private:
    /**
     * @brief Pointer to a SimulationType object that owns this object
     */
    SimulationType* simulType;
    
};

#endif /* INPUTOUTPUT_H */

