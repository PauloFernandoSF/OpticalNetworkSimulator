/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Node.cpp
 * Author: bruno
 * 
 * Created on August 4, 2018, 1:14 AM
 */

#include "../../include/Structure/Node.h"

Node::Node(Topology* topPointer, NodeId nodeId) :
topPointer(topPointer), nodeId(nodeId) {
    
}

Node::Node(const Node& orig) {
}

Node::~Node() {
}

void Node::Initialise() {
    
}

NodeId Node::GetNodeId() const {
    return nodeId;
}

void Node::SetNodeId(NodeId nodeId) {
    this->nodeId = nodeId;
}
