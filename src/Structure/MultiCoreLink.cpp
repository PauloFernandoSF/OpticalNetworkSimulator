/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MultiCoreLink.cpp
 * Author: paulofilho
 * 
 * Created on 5 de fevereiro de 2019, 21:13
 */

#include "MultiCoreLink.h"

MultiCoreLink::MultiCoreLink(Topology* topPointer, unsigned int origimNode, 
    unsigned int destinationNode, double length, 
    unsigned int numberSections, unsigned int numberSlots):Link(topPointer, 
    origimNode, destinationNode, length, numberSections, numberSlots){
    
}

MultiCoreLink::MultiCoreLink(const MultiCoreLink& orig) {
}

MultiCoreLink::~MultiCoreLink() {
}

