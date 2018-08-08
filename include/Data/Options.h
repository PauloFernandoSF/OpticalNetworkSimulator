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

/**
* @brief Numerate the options for routing algorithms
 */
enum RoutingType {
     RoutingInvalid,
     RoutingDJK,
     RoutingYEN,
     RoutingBSR
};

/**
* @brief Numerate the options for spectrum allocation algorithms
 */
enum SpectrumAllocationType {
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
    
    /**
     * @brief Returns the routing option
     * @return Routing option
     */
    RoutingType getRoutingOption() const;    
    /**
     * @brief Sets the routing option
     * @param opt routing option
     */
    void setRoutingOption(RoutingType opt);   
    /**
     * @brief Returns the spectral allocation option
     * @return Spectral allocation option
     */
    SpectrumAllocationType getSpecAllOption() const;    
    /**
     * @brief Sets the spectral allocation option
     * @param opt spectral allocation option
     */
    void setSpecAllOption(SpectrumAllocationType opt);
    
private:
    /**
     * @brief A pointer to the simulation this object belong
     */
    SimulationType* simulType;
    /**
     * @brief Routing option
     */
    RoutingType routingOption;
    /**
     * @brief Spectral allocation option
     */
    SpectrumAllocationType specAllOption;
};

#endif /* OPTIONS_H */

