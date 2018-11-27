/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SA.cpp
 * Author: BrunoVinicius
 * 
 * Created on November 22, 2018, 11:36 PM
 */

#include "../../include/RSA/SA.h"
#include "../../include/Calls/Call.h"

SA::SA() {
}

SA::SA(RSA* rsa, SpectrumAllocationOption option, Topology* topology) 
:rsaAlgorithm(rsa), specAllOption(option), topology(topology) {
    
}

SA::~SA() {
}

void SA::SpecAllocation(Call* call) {
    
    //For tests.
    call->SetStatus(Accepted);
}
