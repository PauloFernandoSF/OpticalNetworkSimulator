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
#include "../../../include/Algorithms/GA/GACoreOrder.h"
#include <algorithm> // for std::find
#include <iterator> // for std::begin, std::end

CoreOrderIndividual::CoreOrderIndividual(GACoreOrder* ga):Individual(ga),ga(ga), 
genes(0), blockProb(0.0) {
    std::vector<unsigned int> vec;
    unsigned int num;
    const unsigned int cores = this->ga->GetNumCores();
    const unsigned int req = this->ga->GetNumReq();
    this->genes.resize(req,std::vector<unsigned int>(cores));
    
    for(unsigned int a = 0;a < req;a++)
        for(unsigned int b = 0;b < cores;b++ )
        {   
            do
                num = rand()%cores;
                
            while(std::find(vec.begin(), vec.end(), num)!= vec.end());
          
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

void CoreOrderIndividual::SetGene(unsigned int line, unsigned int column, 
        unsigned int val){
    this->genes.at(line).at(column) = val;
}

unsigned int CoreOrderIndividual::GetGene(unsigned int line, 
       unsigned int column) const{
    return (this->genes.at(line).at(column));
    //return (this->GetGene(line,column));
    
}

double CoreOrderIndividual::GetBlockProb() const {
    return blockProb;
}

void CoreOrderIndividual::SetBlockProb(double blockProb) {
    assert(this->GetCount() < this->ga->GetMaxNumSimulation());
    this->SetCount(this->GetCount()+1);
    
    if(this->GetCount() == 1)
        this->blockProb = blockProb;
    this->blockProb = (this->blockProb + blockProb) / 2.0;
}

double CoreOrderIndividual::GetMainParameter() {
    return this->GetBlockProb();
}