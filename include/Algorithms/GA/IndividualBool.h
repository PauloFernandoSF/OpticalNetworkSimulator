/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IndividualBool.h
 * Author: BrunoVinicius
 *
 * Created on February 11, 2019, 11:31 AM
 */

#ifndef INDIVIDUALBOOL_H
#define INDIVIDUALBOOL_H

#include <vector>

class GA_RsaOrder;

class IndividualBool {

public:
    
    IndividualBool(GA_RsaOrder* ga);
    
    virtual ~IndividualBool();
    
    
    void CreateGene(unsigned int orNode, unsigned int deNode);
    
    double GetBlockProb() const;

    void SetBlockProb(double blockProb);

private:
    
    GA_RsaOrder* ga;
    
    std::vector<bool> genes;
    
    double blockProb;
    
    unsigned int count;
};

#endif /* INDIVIDUALBOOL_H */

