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
#include <cassert>
#include <iostream>

class SimulationType;
class Node;
class Link;
class Route;

/**
 * @brief Class Topology represents the topology of a simulation.
 */
class Topology {
    friend std::ostream& operator<<(std::ostream& ostream, 
    const Topology* topology);
    
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
     * @brief Initialize the topology, initializing all 
     * links and nodes.
     */
    void Initialize();
    
    /**
     * @brief Returns the number of nodes in this topology
     * @return The total number of nodes
     */
    unsigned int GetNumNodes() const;
    /**
     * @brief Sets the number of nodes in this topology
     * @param numNodes total number of nodes
     */
    void SetNumNodes(unsigned int numNodes);
    /**
     * @brief Returns the number of links in this topology
     * @return The total number of links
     */
    unsigned int GetNumLinks() const;
    /**
     * @brief Sets the number of links in this topology
     * @param numLinks total number of links
     */
    void SetNumLinks(unsigned int numLinks);
    /**
     * @brief Returns the number of slots in this topology
     * @return The total number of slots
     */
    unsigned int GetNumSlots() const;
    /**
     * @brief Sets the number of slots in this topology
     * @param numSlots total number of slots
     */
    void SetNumSlots(unsigned int numSlots);
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
    
    /**
     * @brief Get a specified node in the topology.
     * @param index index of vector of nodes.
     * @return Pointer to a Node object.
     */
    Node* GetNode(unsigned int index) const;
    /**
     * @brief Get a specified link in the topology.
     * @param indexOrNode index of origin node.
     * @param indexDeNode index of destination node.
     * @return Pointer to a Link object.
     */
    Link* GetLink(unsigned int indexOrNode, 
    unsigned int indexDeNode) const;

    bool CheckSlotDisp(const Route* route, unsigned int slot) const;
    
    bool CheckSlotsDisp(const Route* route, unsigned int iniSlot,
                                            unsigned int finSlot) const;
    
    bool CheckBlockSlotsDisp(const Route* route, unsigned int numSlots) const;
    
private:
    /**
     * @brief A pointer to the simulation this object belong
     */
    SimulationType* simulType;
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
    unsigned int numNodes;
    /**
     * @brief Total number of links in the topology
     */
    unsigned int numLinks;
    /**
     * @brief Total number of slots in the topology
     */
    unsigned int numSlots;
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

