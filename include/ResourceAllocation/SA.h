/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SA.h
 * Author: BrunoVinicius
 *
 * Created on November 22, 2018, 11:36 PM
 */

#ifndef SA_H
#define SA_H

#include <random>
#include <cstdlib>

class ResourceAlloc;
class Topology;
class Call;

#include "../Data/Options.h"

/**
 * @brief Class responsible for spectral allocation of the call requests.
 * @param rsa RourceAlloc that own this object.
 * @param option Spectral allocation option.
 * @param topology Topology used in this spectral allocation.
 */
class SA {

public:
    /**
     * @brief Standard constructor for a SA object.
     * @param rsa RourceAlloc that own this object.
     * @param option Spectral allocation option.
     * @param topology Topology used in this spectral allocation.
     */
    SA(ResourceAlloc* rsa, SpectrumAllocationOption option, Topology* topology);
    /**
     * @brief Virtual destructor of a SA object.
     */
    virtual ~SA();
    
    /**
     * @brief Function that choose the spectral allocation based on the option 
     * for a specified call request.
     * @param call Call request.
     */
    void SpecAllocation(Call* call);
    /**
     * @brief Function to apply random spectral allocation to a call request.
     * This SA randomly select between the available slots.
     * @param call Call request.
     */
    void Random(Call* call);
    /**
     * @brief Function to apply random spectral allocation to a call request.
     * This SA select the first available slots.
     * @param call
     */ 
    void FirstFit(Call* call);
    
    void MostUsed(Call* call);
    
    void LeastUsed(Call* call);
    
    void MaxSum(Call* call);
    
    void RCL(Call* call);
    
    void MSCL(Call* call);
    
    
    std::vector<unsigned int> RandomSlots(Call* call);
    
    std::vector<unsigned int> FirstFitSlots(Call* call);
private:
    /**
     * @brief RourceAlloc that own this object.
     */
    ResourceAlloc* resourceAlloc;
    /**
     * @brief Spectral allocation option.
     */
    SpectrumAllocationOption specAllOption;
    /**
     * @brief Topology used in this SA
     */
    Topology* topology;
};

#endif /* SA_H */

