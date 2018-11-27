/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Routing.h
 * Author: BrunoVinicius
 *
 * Created on November 19, 2018, 11:43 PM
 */

#ifndef ROUTING_H
#define ROUTING_H

#include <memory>

class RSA;
class Call;
class Route;
class Topology;

#include "../Data/Options.h"
#include "../../include/Structure/Node.h"

class Routing {

public:
    
    Routing();
    
    Routing(RSA* rsa, RoutingOption option, Topology* topology);
    
    virtual ~Routing();
    
    void RoutingCall(Call* call);
    
    void Dijkstra(Call* call);
    
    void Dijkstra();
    
    std::shared_ptr<Route> Dijkstra(NodeId orNode, NodeId deNode);
    
    
    RSA* GetRsaAlgorithm() const;

    void SetRsaAlgorithm(RSA* rsaAlgorithm);

    Topology* GetTopology() const;

    void SetTopology(Topology* topology);

private:
    
    RSA* rsaAlgorithm;
    
    RoutingOption routingOption;
    
    Topology* topology;
};

#endif /* ROUTING_H */

