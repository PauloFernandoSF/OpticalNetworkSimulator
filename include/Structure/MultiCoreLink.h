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

#include"Link.h"
#include <vector>
#include <memory>
#include <cassert>
#include <iostream>

class Core;
class Topology;

/**
* @brief Class MultiCoreLink represents a MultiCoreLink inside a topology. 
*/
class MultiCoreLink : public Link {
    
public:   
    /**
     * @brief Standard constructor for a Link object.
     * @param topPointer pointer to a Topology object that
     * owns this link.
     * @param origimNode origin node of the link.
     * @param destinationNode destination node of the link.
     * @param length length of the link (meters).
     * @param numberSections total number of sections 
     * of the link.
    */
    MultiCoreLink(Topology* topPointer, unsigned int origimNode, 
    unsigned int destinationNode, double length, 
    unsigned int numberSections, unsigned int numberSlots);
    /**
    * @brief Initialize a MultiCoreLink inside a topology. 
    */
    void Initialize();
    /**
    * @brief Destructor of MultiCoreLink. 
    */
    ~MultiCoreLink();
    /**
    * @brief  Get a specific core.
    * @return A core.  
    */
    Core* getCore(int corePosition);
    //Core*getFiberCore(int);

private:
    /**
     @brief Vector with all cores of the MultiCoreLink
    */
    std::vector<std::shared_ptr<Core>> coreVector;

};

#endif /* MULTICORELINK_H */

