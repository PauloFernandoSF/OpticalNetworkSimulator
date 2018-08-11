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
#include <memory>
#include <assert.h>

class SimulationType;

/**
 * 
 */
class Topology {
public:
    Topology(SimulationType* simulType);
    Topology(const Topology& orig);
    virtual ~Topology();
    
    void LoadFile();
    void Initialise();
    /**
     * @brief Returns the name of this topology
     * @return String with topology name
     */
    std::string GetNameTopology() const;
    /**
     * @brief Sets  the topology name
     * @param nameTopology name of topology
     */
    void SetNameTopology(std::string nameTopology);
    
    int GetNumNodes() const;

    void SetNumNodes(int numNodes);
    
    int GetNumLinks() const;

    void SetNumLinks(int numLinks);

    int GetNumSlots() const;

    void SetNumSlots(int numSlots);
    
    void InsertLink(std::shared_ptr<Link> link);
    
    void InsertNode(std::shared_ptr<Node> node);
    
    double GetMaxLength() const;

    void SetMaxLength();


    
private:
    /**
     * @brief A pointer to the simulation this object belong
     */
    SimulationType* simulType;
    /**
     * @brief Name of the selected topology
     */
    std::string nameTopology;
    /**
     * @brief Vector with all topology nodes 
     */
    std::vector<std::shared_ptr<Node>> vecNodes;
    /**
     * @brief Vector with all topology links 
     */
    std::vector<std::shared_ptr<Link>> vecLinks;
    /**
     * @brief Total number of nodes in the topology
     */
    int numNodes;
    /**
     * @brief Total number of links in the topology
     */
    int numLinks;
    /**
     * @brief Total number of slots in the topology
     */
    int numSlots;
    
    double maxLength;
};

#endif /* TOPOLOGY_H */

