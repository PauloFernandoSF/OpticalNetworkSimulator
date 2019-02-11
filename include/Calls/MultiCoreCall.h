/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MultiCoreCall.h
 * Author: paulofilho
 *
 * Created on 7 de fevereiro de 2019, 16:31
 */

#ifndef MULTICORECALL_H
#define MULTICORECALL_H

class Node;

#include "CallGenerator.h"

class MultiCoreCall: public Call{
public:
    MultiCoreCall(Node* orNode, Node* deNode, double bitRate, 
         TIME deacTime);
    //MultiCoreCall(const MultiCoreCall& orig);
    
    void SetCore(int core);
    
    int GetCore();
    
    virtual ~MultiCoreCall();
private:
    /**
     * @brief Index of the core where the call is allocated
     */
    int coreIndex;

};

#endif /* MULTICORECALL_H */

