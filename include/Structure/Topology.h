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

#include <vector>
#include <memory>
#include <assert.h>

class SimulationType;
class Node;
class Link;

/**
 * @brief Class Topology represents the topology of a simulation.
 */
class Topology {
public:
    /**
     * @brief Standard constructor for a Topology object.
     * @param simulType SimulationType object that owns 
     * this topology.
     */
    Topology(SimulationType* simulType);
    /**
     * @brief Copy constructor for a Topology object.
     * @param orig original Topology object.
     */
    Topology(const Topology& orig);
    /**
     * @brief Virtual destructor of a Topology object.
     */
    virtual ~Topology();
    
    /**
     * @brief Loads the topology from a .txt file.
     */
    void LoadFile();
    /**
     * @brief Initialise the topology, initializing all 
     * links and nodes.
     */
    void Initialise();
    
    /**
     * @brief Returns the name of this topology.
     * @return String with topology name.
     */
    std::string GetNameTopology() const;
    /**
     * @brief Sets  the topology name.
     * @param nameTopology name of topology.
     */
    void SetNameTopology(std::string nameTopology);
    /**
     * @brief Returns the number of nodes in this topology
     * @return The total number of nodes
     */
    int GetNumNodes() const;
    /**
     * @brief Sets the number of nodes in this topology
     * @param numNodes total number of nodes
     */
    void SetNumNodes(int numNodes);
    /**
     * @brief Returns the number of links in this topology
     * @return The total number of links
     */
    int GetNumLinks() const;
    /**
     * @brief Sets the number of links in this topology
     * @param numLinks total number of links
     */
    void SetNumLinks(int numLinks);
    /**
     * @brief Returns the number of slots in this topology
     * @return The total number of slots
     */
    int GetNumSlots() const;
    /**
     * @brief Sets the number of slots in this topology
     * @param numSlots total number of slots
     */
    void SetNumSlots(int numSlots);
    /**
     * @brief Insert a created link in the topology
     * The ownership belongs to the vector
     * @param link pointer to a Link object
     */
    void InsertLink(std::shared_ptr<Link> link);
    /**
     * @brief Insert a created node in the topology
     * The ownership belongs to the vector
     * @param node pointer to a Node object
     */
    void InsertNode(std::shared_ptr<Node> node);
    /**
     * @brief Returns the length of the longest link
     * @return Length of the longest link
     */
    double GetMaxLength() const;
    /**
     * @brief Set additional settings of this topology
     */
    void SetAditionalSettings();

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
    /**
     * @brief Length of the longest link
     */
    double maxLength;
    
    /**
     * @brief Calculate the maximum link in this topology
     * and sets the maxLength value.
     */
    void SetMaxLength();
    /**
     * @brief Set the  initial cost for all links in this
     * topology, based in the selected option.
     */
    void SetLinksIniCost();
};

#endif /* TOPOLOGY_H */

