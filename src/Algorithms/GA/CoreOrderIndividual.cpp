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
        }
}

CoreOrderIndividual::CoreOrderIndividual(const CoreOrderIndividual& orig) {
}

CoreOrderIndividual::~CoreOrderIndividual() {
}

CoreOrderIndividual::SetGene(unsigned int line, unsigned int column, 
        unsigned int value){
    this->genes.at(line).at(column) = value;
}