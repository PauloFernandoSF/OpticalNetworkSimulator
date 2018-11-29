/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ResourceAlloc.h
 * Author: BrunoVinicius
 *
 * Created on November 27, 2018, 8:33 PM
 */

#ifndef RESOURCEALLOC_H
#define RESOURCEALLOC_H

#include <vector>
#include <memory>

class SimulationType;
class Topology;
class Route;
class Routing;
class SA;
class Call;
class Modulation;

#include "../Data/Options.h"

class ResourceAlloc {
    
public:
    
    ResourceAlloc(SimulationType *simulType);
    
    virtual ~ResourceAlloc();
    
    void Load();
    
    
    void ResourAlloc(Call* call);
    
    void RSA(Call* call);
    
    void RMSA(Call* call);
    
    
    void SetRoute(unsigned int orN, unsigned int deN, 
                  std::shared_ptr<Route> route);
    
    void SetRoutes(unsigned int orN, unsigned int deN, 
                   std::vector<std::shared_ptr<Route>> routes);
    
    void AddRoute(unsigned int orN, unsigned int deN, 
                  std::shared_ptr<Route> route);
    
    void AddRoutes(unsigned int orN, unsigned int deN,
                   std::vector<std::shared_ptr<Route>> routes);
    
    void ClearRoutes(unsigned int orN, unsigned int deN);
    
    std::vector<std::shared_ptr<Route>> GetRoutes(unsigned int orN,
                                                  unsigned int deN);
    
    bool IsOfflineRouting();
    
    void RoutingOffline();
    
    
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
    
    ResourceAllocOption resourAllocOption;
    
    PhysicalLayerOption phyLayerOption;
    
    std::vector<std::vector<std::shared_ptr<Route>>> allRoutes;
    
    std::shared_ptr<Routing> routing;
    
    std::shared_ptr<SA> specAlloc;
    
    std::shared_ptr<Modulation> modulation;
};

#endif /* RESOURCEALLOC_H */
