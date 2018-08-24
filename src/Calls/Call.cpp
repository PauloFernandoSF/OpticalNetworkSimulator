/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Call.cpp
 * Author: bruno
 * 
 * Created on August 17, 2018, 11:40 PM
 */

#include "../../include/Calls/Call.h"

Call::Call(Node* orNode, Node* deNode, double bitRate)
:orNode(orNode), deNode(deNode), bitRate(bitRate),
numberSlots(0), slots(0), osnrTh(0.0), bandwidth(0.0) {
    
}

Call::~Call() {
}

Node* Call::GetOrNode() const {
    return orNode;
}

void Call::SetOrNode(Node* orNode) {
    this->orNode = orNode;
}

Node* Call::GetDeNode() const {
    return deNode;
}

void Call::SetDeNode(Node* deNode) {
    this->deNode = deNode;
}
