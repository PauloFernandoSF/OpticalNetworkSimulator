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
class Call;

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
     * @brief Function used to create all network nodes.
     * @param ifstream File stream used to load the nodes.
     */
    void CreateNodes(std::ifstream& ifstream);
    /**
     * @brief Function used to create all network links.
     * @param ifstream File stream used to load the links.
     */
    void CreateLinks(std::ifstream& ifstream);
    
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
     * @brief Function to set as valid all links in the network.
     */
    void SetAllLinksWorking();
    
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
    /**
     * @brief Checks if an specified slot is free in an specified route.
     * @param route Route to be analyzed.
     * @param slot Slot index.
     * @return True if the slot is available.
     */
    bool CheckSlotDisp(const Route* route, unsigned int slot) const;
    /**
     * @brief Checks if a block of slots is free in an specified route.
     * @param route Route to be analyzed.
     * @param iniSlot First slot index.
     * @param finSlot Last slot index.
     * @return True if the block of slots is available.
     */
    bool CheckSlotsDisp(const Route* route, unsigned int iniSlot,
                                            unsigned int finSlot) const;
    /**
     * @brief Checks if there is a contiguous block of free slots in
     * an specified route.
     * @param route Route to be analyzed.
     * @param numSlots Number of slots.
     * @return True if there is a block of avaliable slots.
     */
    bool CheckBlockSlotsDisp(const Route* route, unsigned int numSlots) const;
    /**
     * @brief Check if the specified OSNR is larger than the signal OSNR for
     * the specified route.
     * @param route Route to be analyzed.
     * @param OSNRth OSNR value for comparison.
     * @return True if the OSNR is larger.
     */
    bool CheckOSNR(const Route* route, double OSNRth);
    /**
     * @brief Checks if a specified link is valid.
     * @param link Link to evaluate.
     * @return True if the link is valid
     */
    bool IsValidLink(const Link* link);
    /**
     * @brief Checks if a specified node is valid.
     * @param node Node to evaluate.
     * @return True if the node is valid
     */
    bool IsValidNode(const Node* node);
    /**
     * @brief Check if this is a valid route.
     * @param route Route to analyze.
     * @return True if the route is valid.
     */
    bool IsValidRoute(const Route* route);
    /**
     * @brief Check if the slot is valid.
     * @param index Index of the slot.
     * @return True if the slot is valid.
     */
    bool IsValidSlot(int index);
    /**
     * @brief Check if the lightpath is valid. This function checks the route, 
     * the first and the last slot of the call.
     * @param call Call to analyze.
     * @return True if the lightpath is valid.
     */
    bool IsValidLigthPath(Call* call);
    
    /**
     * @brief Function to set a lightpath in the network of a specified request.
     * @param call Call request used.
     */
    void Connect(Call* call);
    /**
     * @brief Function to disconnect a specified lightpath from the network.
     * @param call Call request to disconnect.
     */
    void Release(Call* call);
    
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

