/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Link.cpp
 * Author: bruno
 * 
 * Created on August 4, 2018, 1:54 AM
 */

#include "../../include/Structure/Link.h"

Link::Link() {
}

Link::Link(unsigned int origimNode, unsigned int destinationNode, 
double length, unsigned int numberSections) 
:origimNode(origimNode), destinationNode(destinationNode), 
length(length), numberSections(numberSections) {
}


Link::~Link() {
}

void Link::initialise() {
    
}

unsigned int Link::GetOrigimNode() const {
    return origimNode;
}

void Link::SetOrigimNode(unsigned int origimNode) {
    this->origimNode = origimNode;
}

unsigned int Link::GetDestinationNode() const {
    return destinationNode;
}

void Link::SetDestinationNode(unsigned int destinationNode) {
    this->destinationNode = destinationNode;
}

double Link::GetLength() const {
    return length;
}

void Link::SetLength(double length) {
    this->length = length;
}

unsigned int Link::GetNumberSections() const {
    return numberSections;
}

void Link::SetNumberSections(unsigned int numberSections) {
    this->numberSections = numberSections;
}
