/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GA.h
 * Author: paulofilho
 *
 * Created on 27 de fevereiro de 2019, 16:30
 */

#ifndef GA_H
#define GA_H
#include "SimulationType.h"

#include <iostream>

class GA : public SimulationType {

public:
    GA(unsigned int simulIndex);
    
    virtual ~GA();
    
    void Run() override;

    void Load() override;

    void LoadFile() override;

    void Print() override;

    void Save() override;

    void Help() override;

private:
   
};

#endif /* GA_H */

