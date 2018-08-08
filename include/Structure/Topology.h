/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Topology.h
 * Author: bruno
 *
 * Created on August 3, 2018, 12:00 AM
 */

#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include "../Structure/Node.h"
#include "../Structure/Link.h"

#include <vector>

class SimulationType;

/**
 * 
 */
class Topology {
public:
    Topology(SimulationType* simulType);
    Topology(const Topology& orig);
    virtual ~Topology();
    
    void create();
    void initialise();
    
private:
    /**
     * @brief A pointer to the simulation this object belong
     */
    SimulationType* simulType;
    /**
     * @brief Vector with all topology nodes 
     */
    std::vector<Node*> vecNodes;
    /**
     * @brief Vector with all topology links 
     */
    std::vector<Link*> vecLinks;
    int numNodes;
    int numLinks;
    int numSlots;
};

#endif /* TOPOLOGY_H */

