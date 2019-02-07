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
#include "../../include/GeneralClasses/Def.h"

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

Call::Call()
:status(NotEvaluated), orNode(nullptr), deNode(nullptr), firstSlot(-1), 
lastSlot(-1), numberSlots(0), osnrTh(0.0), bandwidth(0.0), bitRate(0.0), 
modulation(InvalidModulation), deactivationTime(Def::Max_Double), 
route(nullptr), trialRoutes(0){

}


Call::Call(Node* orNode, Node* deNode, double bitRate, 
TIME deacTime)
:status(NotEvaluated), orNode(orNode), deNode(deNode), firstSlot(-1), 
lastSlot(-1), numberSlots(0), osnrTh(0.0), bandwidth(0.0), bitRate(bitRate), 
modulation(InvalidModulation), deactivationTime(deacTime), 
route(nullptr), trialRoutes(0) {
    
}

Call::~Call() {
    this->route.reset();
    
    for(auto it : trialRoutes){
       it.reset(); 
    }
    this->trialRoutes.clear();
}

CallStatus Call::GetStatus() const {
    return this->status;
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

int Call::GetFirstSlot() const {
    return firstSlot;
}

void Call::SetFirstSlot(int firstSlot) {
    this->firstSlot = firstSlot;
}

int Call::GetLastSlot() const {
    return lastSlot;
}

void Call::SetLastSlot(int lastSlot) {
    this->lastSlot = lastSlot;
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

void Call::SetModulation(TypeModulation modulation) {
    assert(modulation >= FirstModulation && 
           modulation <= LastModulation);
    
    this->modulation = modulation;
}

TypeModulation Call::GetModulation() const {
    return modulation;
}

TIME Call::GetDeactivationTime() const {
    return deactivationTime;
}

void Call::SetDeactivationTime(TIME deactivationTime) {
    this->deactivationTime = deactivationTime;
}

Route* Call::GetRoute() const {
    return this->route.get();
}

std::shared_ptr<Route> Call::GetRoute(unsigned int index) const {
    assert(index < this->trialRoutes.size());
    
    return this->trialRoutes.at(index);
}

unsigned int Call::GetNumRoutes() const {
    return this->trialRoutes.size();
}

void Call::SetRoute(std::shared_ptr<Route> route) {
    this->route = route;
}

void Call::PushTrialRoute(std::shared_ptr<Route> route) {
    this->trialRoutes.push_back(route);
}

void Call::PushTrialRoutes(std::vector<std::shared_ptr<Route> > routes) {
    
    for(auto it : routes)
        if(it != nullptr)
            this->trialRoutes.push_back(it);
    routes.clear();
}

std::shared_ptr<Route> Call::PopTrialRoute() {
    std::shared_ptr<Route> route = nullptr;
    
    //Verify with and without reset function.
    if(!this->trialRoutes.empty()){
        route = this->trialRoutes.front();
        this->trialRoutes.front().reset();
        this->trialRoutes.pop_front();
    }
    
    return route;
}

bool Call::IsThereTrialRoute() const {
    
    return !this->trialRoutes.empty();
}

void Call::ClearTrialRoutes() {
    
    while(!this->trialRoutes.empty()){
        this->trialRoutes.front().reset();
        this->trialRoutes.pop_front();
    }
}

