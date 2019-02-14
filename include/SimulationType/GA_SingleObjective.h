/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GA_SingleObjective.h
 * Author: BrunoVinicius
 *
 * Created on February 11, 2019, 10:53 PM
 */

#ifndef GA_SINGLEOBJECTIVE_H
#define GA_SINGLEOBJECTIVE_H

#include "SimulationType.h"

class GA_RsaOrder;

#include <iostream>

class GA_SingleObjective : public SimulationType {

public:
    
    GA_SingleObjective(unsigned int simulIndex);
    
    virtual ~GA_SingleObjective();
    
    void Run() override;

    void Load() override;

    void LoadFile() override;

    void Print() override;

    void Save() override;

    void Help() override;

    GA_RsaOrder* GetGA_RsaOrder() const;
private:
    
    std::shared_ptr<GA_RsaOrder> gaAlgorithm;
};

#endif /* GA_SINGLEOBJECTIVE_H */

