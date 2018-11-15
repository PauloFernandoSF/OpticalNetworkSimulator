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
#include "../../include/Structure/Node.h"

const boost::unordered_map<CallStatus, std::string> 
Call::mapCallStatus = boost::assign::map_list_of
    (NotEvaluated, "Not evaluated")
    (Accepted, "Accepted call")
    (Blocked, "Blocked call");

std::ostream& operator<<(std::ostream& ostream, const Call* call) {
    
    ostream << "Status: " << call->GetStatusName() << std::endl;
    ostream << "OrNode: " << call->GetOrNode()->GetNodeId() << std::endl;
    ostream << "DeNode: " << call->GetDeNode()->GetNodeId() << std::endl;
    ostream << "Bit Rate(Gbps): " << call->GetBitRate()/1E9 << std::endl;
    ostream << "Bandwidth: " << call->GetBandwidth()/1E9 << std::endl;
    ostream << "OSNR: " << call->GetOsnrTh() << std::endl;
    ostream << "DeacTime: " << call->GetDeactivationTime() << std::endl;
    ostream << "Number of Slots: " << call->GetNumberSlots() << std::endl;
    
    return ostream;
}

Call::Call(Node* orNode, Node* deNode, double bitRate, TIME deacTime)
:status(NotEvaluated), orNode(orNode), deNode(deNode), numberSlots(0), 
slots(0), osnrTh(0.0), bandwidth(0.0), bitRate(bitRate),
deactivationTime(deacTime) {
    
}

Call::~Call() {
}

CallStatus Call::GetStatus() const {
    return status;
}

std::string Call::GetStatusName() const {
    return this->mapCallStatus.at(this->status);
}

void Call::SetStatus(CallStatus status) {
    this->status = status;
}

Node* Call::GetOrNode() const {
    return this->orNode;
}

void Call::SetOrNode(Node* orNode) {
    this->orNode = orNode;
}

Node* Call::GetDeNode() const {
    return this->deNode;
}

void Call::SetDeNode(Node* deNode) {
    this->deNode = deNode;
}

unsigned int Call::GetNumberSlots() const {
    return this->numberSlots;
}

void Call::SetNumberSlots(unsigned int numberSlots) {
    this->numberSlots = numberSlots;
}

double Call::GetOsnrTh() const {
    return osnrTh;
}

void Call::SetOsnrTh(double osnrTh) {
    this->osnrTh = osnrTh;
}

double Call::GetBandwidth() const {
    return bandwidth;
}

void Call::SetBandwidth(double bandwidth) {
    this->bandwidth = bandwidth;
}

double Call::GetBitRate() const {
    return bitRate;
}

void Call::SetBitRate(double bitRate) {
    this->bitRate = bitRate;
}

TIME Call::GetDeactivationTime() const {
    return deactivationTime;
}

void Call::SetDeactivationTime(TIME deactivationTime) {
    this->deactivationTime = deactivationTime;
}
