/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Options.h
 * Author: bruno
 *
 * Created on August 3, 2018, 1:18 AM
 */

#ifndef OPTIONS_H
#define OPTIONS_H

class SimulationType;

#include <fstream>

/**
 *@brief Numerate the topology options
 */
enum TopologyOption {
    TopologyInvalid,
    TopologyNSFNet,
    TopologyRing,
    TopologyToroidal,
    TopologyGermany,
    TopologyItaly
};

/**
* @brief Numerate the options for routing algorithms
 */
enum RoutingOption {
     RoutingInvalid,
     RoutingDJK,
     RoutingYEN,
     RoutingBSR
};

/**
* @brief Numerate the options for spectrum allocation algorithms
 */
enum SpectrumAllocationOption {
     SpecAssInvalid,
     SpecAssRandom,
     SpecAssFF,
     SpecAssMSCL
};

/**
 * @brief Class that contain the data options
 */
class Options {
public:
    Options(SimulationType* simulType);
    Options(const Options& orig);
    virtual ~Options();
    
    void LoadFile();
    
    /**
     * @brief Returns the routing option
     * @return Routing option
     */
    RoutingOption GetRoutingOption() const;
    /**
     * @brief Sets the routing option
     * @param opt routing option
     */
    void SetRoutingOption(RoutingOption routingOption);
    /**
     * @brief Returns the spectral allocation option
     * @return Spectral allocation option
     */
    SpectrumAllocationOption GetSpecAllOption() const;
    /**
     * @brief Sets the spectral allocation option
     * @param opt spectral allocation option
     */
    void SetSpecAllOption(SpectrumAllocationOption specAllOption);
    /**
     * @brief Returns the topology choice
     * @return Topology option
     */
    TopologyOption GetTopologyOption() const;
    /**
     * @brief Sets the topology choice
     * @param topologyOption topology option
     */
    void SetTopologyOption(TopologyOption topologyOption);

private:
    /**
     * @brief A pointer to the simulation this object belong
     */
    SimulationType* simulType;
    /**
     * @brief Routing option
     */
    RoutingOption routingOption;
    /**
     * @brief Spectral allocation option
     */
    SpectrumAllocationOption specAllOption;
    /**
     * @brief Topology option
     */
    TopologyOption topologyOption;
};

#endif /* OPTIONS_H */

