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
#include <map>
#include <boost/assign/list_of.hpp>
#include <boost/unordered_map.hpp>
#include <iostream>

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
 * @brief Numerate the options for links cost
 */
enum LinkCostType {
    Invalid,
    MinHops,
    MinLength,
    MinLengthNormalized
};

/**
 * @brief The Options class is responsible for storage the simulation
 * options.
 */
class Options {
public:
    /**
     * @brief Standard constructor for a Options object.
     * @param simulType SimulationType object that owns 
     * this Options.
     */
    Options(SimulationType* simulType);
    /**
     * @brief Copy constructor for a Options object.
     * @param orig original Options object.
     */
    Options(const Options& orig);
    /**
     * @brief Virtual destructor of a Options object.
     */
    virtual ~Options();
    
    /**
     * @brief Load the options from a .txt file.
     */
    void LoadFile();
    
    /**
     * @brief Returns the topology choice.
     * @return Topology option.
     */
    TopologyOption GetTopologyOption() const;
    /**
     * @brief Gets the name of topology based in option selected.
     * @return The name of the topology.
     */
    std::string GetTopologyName() const;
    /**
     * @brief Sets the topology choice.
     * @param topologyOption topology option.
     */
    void SetTopologyOption(TopologyOption topologyOption);
    /**
     * @brief Returns the routing option.
     * @return Routing option.
     */
    RoutingOption GetRoutingOption() const;
    /**
     * @brief Gets the name of routing algorithm based in 
     * option selected.
     * @return The name of the routing algorithm.
     */
    std::string GetRoutingName() const;
    /**
     * @brief Sets the routing option.
     * @param routingOption routing option.
     */
    void SetRoutingOption(RoutingOption routingOption);
    /**
     * @brief Returns the spectral allocation option.
     * @return Spectral allocation option.
     */
    SpectrumAllocationOption GetSpecAllOption() const;
    /**
     * @brief Gets the name of spectral allocation algorithm 
     * based in option selected.
     * @return The name of the spectral allocation algorithm.
     */
    std::string GetSpecAllName() const;
    /**
     * @brief Sets the spectral allocation option
     * @param specAllOption spectral allocation option
     */
    void SetSpecAllOption(SpectrumAllocationOption specAllOption);
    /**
     * @brief Returns the type of links cost option.
     * @return Link cost option.
     */
    LinkCostType GetLinkCostType() const;
    /**
     * @brief Gets the name of links cost based in 
     * option selected.
     * @return The name of the links cost.
     */
    std::string GetLinkCostTypeName() const;
    /**
     * @brief Sets the links cost option.
     * @param linkCostType links cost option.
     */
    void SetLinkCostType(LinkCostType linkCostType);

    
private:
    /**
     * @brief A pointer to the simulation this object belong.
     */
    SimulationType* simulType;
    /**
     * @brief Topology option.
     */
    TopologyOption topologyOption;
    /**
     * @brief Routing option.
     */
    RoutingOption routingOption;
    /**
     * @brief Spectral allocation option.
     */
    SpectrumAllocationOption specAllOption;
    
    LinkCostType linkCostType;
    /**
     * @brief Map that keeps the topology option 
     * and the name of the selected topology.
     */
    static const boost::unordered_map<TopologyOption, 
    std::string> mapTopologyOptions;
    /**
     * @brief Map that keeps the routing algorithm option 
     * and the name of the selected routing algorithm.
     */
    static const boost::unordered_map<RoutingOption,
    std::string> mapRoutingOptions;
    /**
     * @brief Map that keeps the spectral allocation algorithm 
     * option and the name of the selected spectral 
     * allocation algorithm.
     */
    static const boost::unordered_map<SpectrumAllocationOption,
    std::string> mapSpecAlgOptions;
    /**
     * @brief Map that keeps the links cost option 
     * and the name of the selected links cost.
     */
    static const boost::unordered_map<LinkCostType, 
    std::string> mapLinkCostType;
};

#endif /* OPTIONS_H */

