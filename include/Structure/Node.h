/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Node.h
 * Author: bruno
 *
 * Created on August 4, 2018, 1:14 AM
 */

#ifndef NODE_H
#define NODE_H

#include <iostream>

typedef unsigned int NodeId;

class Topology;

/**
 * @brief Class Node represents a node inside a topology.
 */
class Node {
    friend std::ostream& operator<<(std::ostream& ostream,
    Node* node);
    
public:
    /**
     * @brief Standard constructor for a Node object.
     * @param topPointer pointer to a Topology object that
     * owns this node.
     * @param nodeId node index.
     */
    Node(Topology* topPointer,  NodeId nodeId);
    /**
     * @brief Copy constructor for a Node object.
     * @param orig original Node object.
     */
    Node(const Node& orig);
    /**
     * @brief Virtual destructor of a Node object.
     */
    virtual ~Node();
    
    /**
     * @brief Initialise the node, setting the start values
     * contained in it.
     */
    virtual void Initialise();
    
    /**
     * @brief Get the node index.
     * @return Node index.
     */
    NodeId GetNodeId() const;
    /**
     * @brief Set the node index.
     * @param nodeId node index.
     */
    void SetNodeId(NodeId nodeId);

private:
    /**
     * @brief Pointer to a Topology object that
     * owns this node
     */
    Topology* topPointer;
    /**
     * @brief Node index.
     */
    NodeId nodeId;
};

#endif /* NODE_H */

