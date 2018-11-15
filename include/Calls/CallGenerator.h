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

typedef double TIME;

class SimulationType;
class Call;
class Topology;
class Data;
class Traffic;
class Event;

#include <assert.h>
#include <memory>
#include <random>
#include <queue>

#include "Event.h"

/**
 * @brief 
 */
class CallGenerator {
private:
    struct EventCompare {
        bool operator()(const std::shared_ptr<Event> eventA,
                        const std::shared_ptr<Event> eventB) const;
    };
    
public:
    /**
     * @brief Standard constructor for a CallGenerator object.
     * @param simulType SimulationType object that owns 
     * this data.
     */
    CallGenerator(SimulationType* simulType);
    
    virtual ~CallGenerator();
    
    
    void Initialize();
    
    void Finalize();
    
    void GenerateCall();
    
    std::shared_ptr<Event> GetNextEvent();
    
    /**
     * @brief Get the simulation that owns this object.
     * @return Pointer to a SimulationType object.
     */
    SimulationType* GetSimulType() const;
    /**
     * @brief Set the simulation that owns this object.
     * @param simulType Pointer to a SimulationType object.
     */
    void SetSimulType(SimulationType* const simulType);
    /**
     * @brief Get the network load.
     * @return Network load (erlang).
     */
    double GetNetworkLoad() const;
    /**
     * @brief Set the network load.
     * @param networkLoad network load (erlang).
     */
    void SetNetworkLoad(const double networkLoad);
    
    TIME GetSimulationTime() const;

    void SetSimulationTime(const TIME simulationTime);

    void PopTopEvent();
    
    void PushEvent(std::shared_ptr<Event> evt);
    
    
    /**
     * @brief List with the Event objects ordered based on those times.
     */
    std::priority_queue<std::shared_ptr<Event>,
                        std::vector<std::shared_ptr<Event>>,
                        EventCompare> queueEvents;
    
private:
    /**
     * @breif Pointer to a SimulationType object that
     * owns this object.
     */
    SimulationType* simulType;
    /**
     * @brief Pointer to a Topology object owned
     * by a SimulationType object.
     */
    Topology* topology;
    /**
     * @brief Pointer to a Data object owned by
     * a SimulationType object.
     */
    Data* data;
    /**
     * @brief Pointer to a  Traffic object owned
     * by a SimulationType object.
     */
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
    std::exponential_distribution<TIME> exponencialMuDistribution;
    /**
     * @brief Distribution responsible to generate
     * the inter-arrival time.
     */
    std::exponential_distribution<TIME> exponencialHDistribution;
    /**
     * @brief Network load (Erlangs).
     */
    double networkLoad;
    /**
     * @brief Actual simulation time.
     */
    TIME simulationTime;
};

#endif /* CALLGENERATOR_H */

