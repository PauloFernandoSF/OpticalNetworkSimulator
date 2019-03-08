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
#include <memory>
#include <iostream>

class GA_RsaOrder;

#include "Individual.h"

class IndividualBool : public Individual {

public:
    
    IndividualBool(GA_RsaOrder* ga);
    
    IndividualBool(const std::shared_ptr<const IndividualBool>& orig);
    
    virtual ~IndividualBool();
    
    
    bool GetGene(unsigned int orNode, unsigned int deNode) const;
    
    std::vector<bool> GetGenes() const;
    
    void SetGene(unsigned int orNode, unsigned int deNode, bool value);
    
    double GetBlockProb() const;

    void SetBlockProb(double blockProb);

    double GetMainParameter() override;

private:
    
    GA_RsaOrder* ga;
    
    std::vector<bool> genes;
    
    double blockProb;
};

#endif /* INDIVIDUALBOOL_H */

