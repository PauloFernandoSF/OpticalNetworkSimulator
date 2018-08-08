/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Parameters.h
 * Author: bruno
 *
 * Created on August 8, 2018, 6:25 PM
 */

#ifndef PARAMETERS_H
#define PARAMETERS_H

class SimulationType;

class Parameters {
public:
    Parameters(SimulationType* simulType);
    Parameters(const Parameters& orig);
    virtual ~Parameters();
private:
    /**
     * @brief A pointer to the simulation this object belong
     */
    SimulationType* simulType;
};

#endif /* PARAMETERS_H */

