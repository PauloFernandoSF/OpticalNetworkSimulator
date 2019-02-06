/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Route.h
 * Author: BrunoVinicius
 *
 * Created on November 15, 2018, 10:40 PM
 */

#ifndef ROUTE_H
#define ROUTE_H

#include <vector>
#include <cassert>
#include <iostream>
#include <memory>

class Link;
class ResourceAlloc;
class Topology;
class Node;

class Route {
    
    friend std::ostream& operator<<(std::ostream& ostream, 
    const Route* route);
    
public:
    
    Route(ResourceAlloc* rsaAlg, const std::vector<int>& path);
    
    Route(const Route& orig);
    
    virtual ~Route();
    
    bool operator==(const Route& right) const;
    
    
    int GetOrNode() const;
    
    Node* GetOrNodePointer() const;
    
    int GetDeNode() const;
    
    Node* GetDeNodePointer() const;
    
    int GetNode(unsigned int index) const;
    
    Node* GetNodePointer(unsigned int index) const;
    
    unsigned int GetNumHops() const;
    
    unsigned int GetNumNodes() const;
    
    std::vector<int> GetPath();
    
    double GetCost();
    
    Link* GetLink(unsigned int index) const;
    
    void SetAllNodesWorking();
    
    std::shared_ptr<Route> CreatePartialRoute(unsigned int ind1, 
                                              unsigned int ind2);
    
    std::shared_ptr<Route> AddRoute(std::shared_ptr<Route>& route);

private:
    
    ResourceAlloc* resourceAlloc;
    
    Topology* topology;
    
    std::vector<int> path;
    
    std::vector<Node*> pathNodes;
};

#endif /* ROUTE_H */

