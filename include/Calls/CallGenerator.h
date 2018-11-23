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

#include <cassert>
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
    
    /**
     * @brief Initialize this CallGenerator, defining the range of
     * the distributions (Node, Traffic and Arriaval/Deactivation times).
     * Also sets initial simulation time.
     */
    void Initialize();
    /**
     * @brief Erase the entire list of Events.
     */
    void Finalize();
    /**
     * @brief Generate the Call and the Event, based in the distributions.
     * Push to the ordered list the new created event.
     */
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
    /**
     * @brief Return the simulation time of this CallGenerator.
     * @return Simulation time.
     */
    TIME GetSimulationTime() const;
    /**
     * @brief Sets the simulation time of this CallGenerator.
     * @param simulationTime
     */
    void SetSimulationTime(const TIME simulationTime);

    /**
     * @brief Return the first Event of the ordered list.
     * Also remove the same element of this list.
     * Update the simulation time.
     * @return Top event object from the ordered list of events.
     */
    std::shared_ptr<Event> GetNextEvent();
    /**
     * @brief Push an Event object to the ordered list of events.
     * @param evt
     */
    void PushEvent(std::shared_ptr<Event> evt);
    
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
    /**
     * @brief List with the Event objects ordered based on those times.
     */
    std::priority_queue<std::shared_ptr<Event>,
                        std::vector<std::shared_ptr<Event>>,
                        EventCompare> queueEvents;
};

#endif /* CALLGENERATOR_H */

