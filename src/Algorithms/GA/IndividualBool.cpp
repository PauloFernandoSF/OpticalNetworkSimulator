/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IndividualBool.cpp
 * Author: BrunoVinicius
 * 
 * Created on February 11, 2019, 11:31 AM
 */

#include "../../../include/Algorithms/GA/IndividualBool.h"
#include "../../../include/Algorithms/GA/GA_RsaOrder.h"

IndividualBool::IndividualBool(GA_RsaOrder* ga)
:Individual(ga), ga(ga), genes(0), blockProb(0.0) {
    const unsigned int numNodes = this->ga->GetNumNodes();
    
    for(unsigned int a = 0; a < numNodes*numNodes; a++){
        this->genes.push_back(this->ga->GetBoolDistribution());
    }
}

IndividualBool::IndividualBool(
const std::shared_ptr<const IndividualBool>& orig)
:Individual(orig), ga(orig->ga), genes(orig->genes), blockProb(0.0) {
    
}

IndividualBool::~IndividualBool() {
    
}

bool IndividualBool::GetGene(unsigned int orNode, unsigned int deNode) const {
    return this->genes.at(orNode*this->ga->GetNumNodes()+deNode);
}

std::vector<bool> IndividualBool::GetGenes() const {
    return genes;
}

void IndividualBool::SetGene(unsigned int orNode, unsigned int deNode, 
                             bool value) {
    this->genes.at(orNode*this->ga->GetNumNodes()+deNode) = value;
}

double IndividualBool::GetBlockProb() const {
    return blockProb;
}

void IndividualBool::SetBlockProb(double blockProb) {
    this->SetCount(this->GetCount()+1);
    
    if(this->GetCount() == 1)
        this->blockProb = blockProb;
    this->blockProb = (this->blockProb + blockProb) / 2.0;
}

double IndividualBool::GetMainParameter() {
    return this->GetBlockProb();
}
