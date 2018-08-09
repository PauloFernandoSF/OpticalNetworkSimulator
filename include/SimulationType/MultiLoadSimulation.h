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


class MultiLoadSimulation : public SimulationType {
public:
    MultiLoadSimulation(unsigned int simulIndex);
    MultiLoadSimulation(const MultiLoadSimulation& orig);
    virtual ~MultiLoadSimulation();

    void Run() override;
    void Load() override;
    void LoadFile() override;
    void Print() override;
    void Save() override;
    void Help() override;
    
private:
    
};

#endif /* MULTILOADSIMULATION_H */

