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

typedef unsigned int NodeId;

class Node {
public:
    Node(NodeId nodeId);

    Node(const Node& orig);
    virtual ~Node();
    
    virtual void Initialise();
    
    /**
     * @brief 
     * @return 
     */
    NodeId GetNodeId() const;
    /**
     * @brief 
     * @param nodeId
     */
    void SetNodeId(NodeId nodeId);

private:
    NodeId nodeId;
};

#endif /* NODE_H */

