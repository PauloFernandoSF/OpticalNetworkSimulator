/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RSA.h
 * Author: BrunoVinicius
 *
 * Created on November 19, 2018, 7:56 PM
 */

#ifndef RSA_H
#define RSA_H

#include <vector>
#include <memory>

class SimulationType;
class Topology;
class Route;
class Routing;

class RSA {

public:
    
    RSA(SimulationType *simulType);
    
    RSA(const RSA& orig);
    
    virtual ~RSA();
    
    void SetRoute(unsigned int orN, unsigned int deN, 
                  std::shared_ptr<Route> route);
    
    void SetRoutes(unsigned int orN, unsigned int deN, 
                   std::vector<std::shared_ptr<Route>> routes);
    
    void ClearRoutes(unsigned int orN, unsigned int deN);
    
    std::vector<std::shared_ptr<Route>> GetRoutes(unsigned int orN,
                                                  unsigned int deN);
    
    //void AddRoute
    
    SimulationType* GetSimulType() const;

    void SetSimulType(SimulationType* simulType);

    Topology* GetTopology() const;

    void SetTopology(Topology* topology);


private:
    /**
     * @breif Pointer to a SimulationType object that
     * owns this RSA.
     */
    SimulationType* simulType;
    
    Topology* topology;
    
    std::vector<std::vector<std::shared_ptr<Route>>> allRoutes;
    
    std::shared_ptr<Routing> routing;
};

#endif /* RSA_H */

