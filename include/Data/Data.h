/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Data.h
 * Author: bruno
 *
 * Created on August 8, 2018, 6:25 PM
 */

#ifndef DATA_H
#define DATA_H

class SimulationType;

class Data {
public:
    Data(SimulationType* simulType);
    Data(const Data& orig);
    virtual ~Data();
private:
    /**
     * @brief A pointer to the simulation this object belong
     */
    SimulationType* simulType;
};

#endif /* DATA_H */

