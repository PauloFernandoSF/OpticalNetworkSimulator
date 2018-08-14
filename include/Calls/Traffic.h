/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Traffic.h
 * Author: bruno
 *
 * Created on August 14, 2018, 1:15 AM
 */

#ifndef TRAFFIC_H
#define TRAFFIC_H

#include <vector>

class SimulationType;

/**
 * @brief Class Traffic represents the traffic of a simulation.
 */
class Traffic {
public:
    /**
     * @brief Standard constructor for a Traffic object.
     * @param simulType SimulationType object that owns 
     * this Traffic.
     */
    Traffic(SimulationType* simulType);
    /**
     * @brief Copy constructor for a Traffic object.
     * @param orig orig original Traffic object.
     */
    Traffic(const Traffic& orig);
    /**
     * @brief Virtual destructor of a Traffic object.
     */
    virtual ~Traffic();
    
    /**
     * @brief  Loads the traffic from a .txt file.
     */
    void LoadFile();
    
    /**
     * Returns the vector with all traffic values.
     * @return traffic values.
     */
    std::vector<double> GetVecTraffic() const;
    /**
     * @brief Set the vector with all traffic values.
     * @param vecTraffic all traffic values.
     */
    void SetVecTraffic(std::vector<double> vecTraffic);
    /**
     * @brief Gets the bit error rate. 
     * This is the minimum bit error rate value accepted.
     * @return 
     */
    static const double GetBER();
    /**
     * @brief Gets the number of polarizations.
     * @return Total number of polarizations.
     */
    static const int GetPolarization();

private:
    /**
     * @brief A pointer to the simulation this object belong
     */
    SimulationType* simulType;
    std::vector<double> vecTraffic;
    static const double BER;
    static const int polarization;
};

#endif /* TRAFFIC_H */

