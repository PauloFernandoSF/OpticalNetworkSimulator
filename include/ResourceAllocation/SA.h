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

#include "../Data/Options.h"

class ResourceAlloc;
class Topology;
class Call;

class SA {

public:
    
    SA();
    
    SA(ResourceAlloc* rsa, SpectrumAllocationOption option, Topology* topology);
    
    virtual ~SA();
    
    void SpecAllocation(Call* call);

private:
    
    ResourceAlloc* resourceAlloc;
    
    SpectrumAllocationOption specAllOption;
    
    Topology* topology;
};

#endif /* SA_H */

