/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GACoreOrder.h
 * Author: paulofilho
 *
 * Created on 25 de fevereiro de 2019, 12:26
 */

#ifndef GACOREORDER_H
#define GACOREORDER_H

#include "GA.h"
#include "CoreOrderIndividual.h"

class GACoreOrder: public GA {
public:
    GACoreOrder();
    
    GACoreOrder(const GACoreOrder& orig);
    
    virtual ~GACoreOrder();
    
    unsigned int GetNumCores();
    
    void SetNumCores();
    
    unsigned int GetNumReq();
    
    void SetNumReq();
    
private:
    /**
     * @brief Number of cores in the network.
     */
    unsigned int numCores;
    /*
     * @brief Number of different requisitions classes that can arrive 
     * in the network.
     */
    unsigned int numReq;
};

#endif /* GACOREORDER_H */

