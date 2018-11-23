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

class Routing {

public:
    
    Routing();
    
    Routing(const Routing& orig);
    
    virtual ~Routing();
    
    
    void Dijkstra();
    
    void Dijkstra(Call* call);
    
    std::shared_ptr<Route> Dijkstra(unsigned int orNode, 
                                    unsigned int deNode);
    
    
    RSA* GetRsaAlgorithm() const;

    void SetRsaAlgorithm(RSA* rsaAlgorithm);

    Topology* GetTopology() const;

    void SetTopology(Topology* topology);

private:
    
    RSA* rsaAlgorithm;
    
    Topology* topology;
};

#endif /* ROUTING_H */

