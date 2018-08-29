/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CallGenerator.h
 * Author: bruno
 *
 * Created on August 17, 2018, 10:53 PM
 */

#ifndef CALLGENERATOR_H
#define CALLGENERATOR_H

#include <random>

class SimulationType;
class Call;
class Topology;
class Data;
class Traffic;

#include <assert.h>
#include <memory>

#include "Traffic.h"

class CallGenerator {
public:
    /**
     * @brief Standard constructor for a CallGenerator object.
     * @param simulType SimulationType object that owns 
     * this data.
     */
    CallGenerator(SimulationType* simulType);
    
    virtual ~CallGenerator();
        
    void GenerateCall();
    
    /**
     * @brief Get the simulation that owns this object.
     * @return Pointer to a SimulationType object.
     */
    SimulationType* GetSimulType() const;
    /**
     * @brief Set the simulation that owns this object.
     * @param simulType Pointer to a SimulationType object.
     */
    void SetSimulType(SimulationType* simulType);
    /**
     * @brief Get the network load.
     * @return Network load (erlang).
     */
    double GetNetworkLoad() const;
    /**
     * @brief Set the network load.
     * @param networkLoad network load (erlang).
     */
    void SetNetworkLoad(double networkLoad);
    
private:
    /**
     * @breif Pointer to a SimulationType object that
     * owns this object.
     */
    SimulationType* simulType;
    
    Topology* topology;
    
    Data* data;
    
    Traffic* traffic;
    /**
     * @brief Random engine responsible for the
     * random distributions.
     */
    static std::default_random_engine random_generator;
    /**
     * @brief Distribution responsible to generate 
     * the random node index.
     */
    std::uniform_int_distribution<int> uniformNodeDistribution;
    /**
     * @brief Distribution responsible to generate 
     * the random traffic index.
     */
    std::uniform_int_distribution<int> uniformTrafficDistribution;
    /**
     * @brief Distribution responsible to generate
     * the deactivation connection time.
     */
    std::exponential_distribution<double> exponencialMuDistribution;
    /**
     * @brief Distribution responsible to generate
     * the inter-arrival time.
     */
    std::exponential_distribution<double> exponencialHDistribution;
    
    double networkLoad;

    //Fazer container com as chamadas (Calls) criadas.
    //Evento? Connection?
};

#endif /* CALLGENERATOR_H */

