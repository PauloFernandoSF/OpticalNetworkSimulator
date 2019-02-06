/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MultiCoreLink.h
 * Author: paulofilho
 *
 * Created on 5 de fevereiro de 2019, 21:13
 */

#ifndef MULTICORELINK_H
#define MULTICORELINK_H

#include "Link.h"
#include "Core.h"

//#include <iostream>

class MultiCoreLink : Link {
public:
    MultiCoreLink(Topology* topPointer, unsigned int origimNode, 
    unsigned int destinationNode, double length, 
    unsigned int numberSections, unsigned int numberSlots);
    
    MultiCoreLink(const MultiCoreLink& orig);
    virtual ~MultiCoreLink();
    bool getCoreOccupation(int sPosition,Core* core);
    Core*getFiberCore(int);

private:
    /**
     @brief Vector with all cores of the MultiCoreLink
     */
    std::vector<std::shared_ptr<Core>> coreVector;
    /**
     @brief
     */
    unsigned int numCores;

};

#endif /* MULTICORELINK_H */

