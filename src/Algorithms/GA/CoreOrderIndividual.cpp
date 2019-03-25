/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CoreOrderIndividual.cpp
 * Author: paulofilho
 * 
 * Created on 26 de fevereiro de 2019, 22:58
 */

#include "../../../include/Algorithms/GA/CoreOrderIndividual.h"
#include "../../../include/Algorithms/GA/GACoreOrder.h"
#include <algorithm> // for std::find
#include <iterator> // for std::begin, std::end

CoreOrderIndividual::CoreOrderIndividual(GACoreOrder* ga):Individual(ga),ga(ga), 
genes(0), blockProb(0.0) {
    std::vector<unsigned int> vec;
    unsigned int num;
    const unsigned int cores = this->ga->GetNumCores();
    const unsigned int req = this->ga->GetNumReq();
    
    for(unsigned int a = 0;a < req;a++)
        for(unsigned int b = 0;b < cores;b++ )
        {   
            do
                num = rand()%cores;
                
            while(std::find(std::begin(vec), std::end(vec), num));
            
            vec.push_back(num);
            SetGene(a,b,num);
            if(b == cores - 1)
                vec.clear();
        }
}

CoreOrderIndividual::CoreOrderIndividual(
const std::shared_ptr<const CoreOrderIndividual>& orig):Individual(orig),
        ga(orig->ga),genes(orig->genes),blockProb(orig->blockProb) {
}

CoreOrderIndividual::~CoreOrderIndividual() {
}

CoreOrderIndividual::SetGene(unsigned int line, unsigned int column, 
        unsigned int value){
    this->genes.at(line).at(column) = value;
}

unsigned int CoreOrderIndividual::GetGene(unsigned int line, 
        unsigned int column){
    return this->genes.at(line).at(column);
}

double IndividualBool::GetBlockProb() const {
    return blockProb;
}

void IndividualBool::SetBlockProb(double blockProb) {
    assert(this->GetCount() < this->ga->GetMaxNumSimulation());
    this->SetCount(this->GetCount()+1);
    
    if(this->GetCount() == 1)
        this->blockProb = blockProb;
    this->blockProb = (this->blockProb + blockProb) / 2.0;
}

double IndividualBool::GetMainParameter() {
    return this->GetBlockProb();
}