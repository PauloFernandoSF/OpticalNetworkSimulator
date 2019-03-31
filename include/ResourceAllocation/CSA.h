/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CSA.h
 * Author: paulofilho
 * Core Spectrum Assignment class
 * Created on 7 de fevereiro de 2019, 15:19
 */

#ifndef CSA_H
#define CSA_H

#include "SA.h"
#include "../Algorithms/GA/CoreOrderIndividual.h"
#include"../Data/Options.h"

class CSA: public SA {
public:
    /**
     * @brief Standard constructor for a CSA object.
     * @param rsa RourceAlloc that own this object.
     * @param option Spectral allocation option.
     * @param topology Topology used in this spectral allocation.
     * @param gaOption GAOption selected in the simulation.
     */
    CSA(ResourceAlloc* rsa, SpectrumAllocationOption option, 
        Topology* topology,GAOption gaOption);
    /**
     * @brief Virtual destructor of a CSA object.
     */
    virtual ~CSA();
    /**
     * @brief Spectrum allocation that chooses first core and first set of slots
     * available to allocate the call
     * @param call
     */ 
    void FirstFit(Call* call);        
    /**
     * @brief Spectrum allocation that uses MSCL in all available set of slots
     * in all cores
     * @param call pointer of call class
     * @return void
     */    
    void MSCL(Call* call);
    /**
     * @brief Set the individual for GA operation
     * @param pointer of CoreOrderIndividual class
     */    
    void SetInd(CoreOrderIndividual* ind);
private:
    /**
     * @brief Individual that will be used in the CoreOrder GA algorithm
    */  
    CoreOrderIndividual* ind;
    /**
     * @brief Spectrum allocation used when GACoreOrder is selescted
     * @param call pointer of call class
     */ 
    void GAFirstFit(Call* call);
    /**
     * @brief Spectrum allocation used when GA is NOT selected
     * @param call
     */ 
    void NormalFirstFit(Call* call);
    /**
     * @brief GA option selected.
    */
    GAOption gaOption;
};

#endif /* CSA_H */

