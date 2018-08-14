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

/**
 * @brief The Data class is responsible for storage the simulation
 * data.
 */
class Data {
public:
    /**
     * @brief Standard constructor for a Data object.
     * @param simulType SimulationType object that owns 
     * this data.
     */
    Data(SimulationType* simulType);
    /**
     * @brief Copy constructor for a Data object.
     * @param orig original Data object.
     */
    Data(const Data& orig);
    /**
     * @brief Virtual destructor of a Data object.
     */
    virtual ~Data();
private:
    /**
     * @brief A pointer to the simulation this object belong
     */
    SimulationType* simulType;
};

#endif /* DATA_H */

