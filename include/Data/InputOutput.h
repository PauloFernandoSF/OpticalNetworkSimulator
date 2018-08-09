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

class InputOutput {
public:
    InputOutput(SimulationType* simulType);
    InputOutput(const InputOutput& orig);
    virtual ~InputOutput();
    
    void LoadParameters(std::ifstream& parameters);
    
    void LoadOptions(std::ifstream& options);
    
    void LoadTopology(std::ifstream& topology);
    
private:
    /**
     * @brief Pointer to a SimulationType object that owns this object
     */
    SimulationType* simulType;
    
};

#endif /* INPUTOUTPUT_H */

