/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Topology.cpp
 * Author: bruno
 * 
 * Created on August 3, 2018, 12:00 AM
 */

#include "../../include/Structure/Topology.h"

#include "../../include/SimulationType/SimulationType.h"
#include "../../include/Data/Options.h"
#include "../../include/Data/Parameters.h"
#include "../../include/Data/InputOutput.h"
#include "../../include/Structure/Node.h"
#include "../../include/Structure/Link.h"
#include "../../include/GeneralClasses/Def.h"
#include "../../include/ResourceAllocation/Route.h"
#include "../../include/ResourceAllocation/Signal.h"
#include "../../include/Calls/Call.h"

std::ostream& operator<<(std::ostream& ostream, 
const Topology* topology) {
    ostream << "TOPOLOGY" << std::endl;
    
    ostream << "Number of nodes: " << topology->GetNumNodes() 
            << std::endl;
    ostream << "Number of links: " << topology->GetNumLinks()
            << std::endl;
    ostream << "Number of slots: " << topology->GetNumSlots()
            << std::endl;
    
    for(auto it: topology->vecNodes){
        ostream << it << std::endl;
    }
    
    for(auto it : topology->vecLinks){
        if(it != nullptr)
            ostream << it << std::endl;
    }
    
    return ostream;
}

Topology::Topology(SimulationType* simulType) 
:simulType(simulType), vecNodes(0), vecLinks(0), 
numNodes(0), numLinks(0), numSlots(0), maxLength(0.0) {

}

Topology::~Topology() {
    
    for(auto it : this->vecNodes){
        it.reset();
    }
    
    
    for(auto it : this->vecLinks){
        it.reset();
    }
}

void Topology::LoadFile() {
    std::ifstream auxIfstream;
    unsigned int auxInt;
    
    this->simulType->GetInputOutput()->LoadTopology(auxIfstream);
    
    auxIfstream >> auxInt;
    this->SetNumNodes(auxInt);
    auxIfstream >> auxInt;
    this->SetNumLinks(auxInt);
    this->SetNumSlots(this->simulType->GetParameters()->GetNumberSlots());
    
    //Create all topology nodes
    std::shared_ptr<Node> node;
    for(unsigned int a = 0; a < this->GetNumNodes(); ++a){
        node = std::make_shared<Node>(this, a);
        this->InsertNode(node);
        node.reset();
    }
    
    //Create all topology links
    unsigned  int orNode, deNode, nSec;
    double length;
    std::shared_ptr<Link> link;
    for(auxInt = 0; auxInt < this->GetNumLinks(); ++auxInt){
        auxIfstream >> orNode;
        auxIfstream >> deNode;
        auxIfstream >> length;
        auxIfstream >> nSec;
        link = std::make_shared<Link>(this, orNode, deNode, 
        length, nSec, this->GetNumSlots());
        this->InsertLink(link);
        link.reset();
    }
}

void Topology::Initialize() {
    
    for(auto it : this->vecNodes){
        it->Initialize();
    }
    
    for(auto it : this->vecLinks){
        if(it != nullptr)
            it->Initialize();
    }
}

unsigned int Topology::GetNumNodes() const {
    return numNodes;
}

void Topology::SetNumNodes(unsigned int numNodes) {
    assert(this->numNodes == 0);
    this->numNodes = numNodes;
    
    for(unsigned int a = 0; a < this->numNodes; ++a){
        this->vecNodes.push_back(nullptr);
        
        for(unsigned int b = 0; b < this->numNodes; ++b){
            this->vecLinks.push_back(nullptr);
        }
    }
}

unsigned int Topology::GetNumLinks() const {
    return numLinks;
}

void Topology::SetNumLinks(unsigned int numLinks) {
    assert(this->numLinks == 0);
    this->numLinks = numLinks;
}

unsigned int Topology::GetNumSlots() const {
    return numSlots;
}

void Topology::SetNumSlots(unsigned int numSlots) {
    assert(this->numSlots == 0);
    this->numSlots = numSlots;
}

void Topology::InsertLink(std::shared_ptr<Link> link) {
    assert( this->vecLinks.at(link->GetOrigimNode() * this->GetNumNodes()
    + link->GetDestinationNode()) == nullptr );
    
    this->vecLinks.at(link->GetOrigimNode() * this->GetNumNodes()
    + link->GetDestinationNode()) = link;
}

void Topology::InsertNode(std::shared_ptr<Node> node) {
    assert(node.get()->GetNodeId() < this->vecNodes.size());
    
    this->vecNodes.at(node->GetNodeId()) = node;
}

double Topology::GetMaxLength() const {
    return maxLength;
}

void Topology::SetMaxLength() {
    
    for(auto it : this->vecLinks){
        
        if(it == nullptr)
            continue;
        
        if(this->maxLength < it->GetLength())
            this->maxLength = it->GetLength();
    }
}

void Topology::SetAditionalSettings() {
    this->SetMaxLength();
    this->SetLinksIniCost();
}

void Topology::SetLinksIniCost() {
    
    switch(this->simulType->GetOptions()->GetLinkCostType()){
        case MinHops:
            for(auto it : vecLinks){
                if(it == nullptr)
                    continue;
                it->SetCost(1.0);
            }
            break;
        case MinLength:
            for(auto it : vecLinks){
                if(it == nullptr)
                    continue;
                it->SetCost(it->GetLength());
            }
            break;
        case MinLengthNormalized:
            for(auto it : vecLinks){
                if(it == nullptr)
                    continue;
                it->SetCost(it->GetLength()/this->GetMaxLength());
            }
            break;
        default:
            for(auto it : vecLinks){
                if(it == nullptr)
                    continue;
                it->SetCost(Def::Max_Double);
            }
    }
}

Node* Topology::GetNode(unsigned int index) const {
    assert(index < this->GetNumNodes());
    return this->vecNodes.at(index).get();
}

Link* Topology::GetLink(unsigned int indexOrNode, 
unsigned int indexDeNode) const {
    assert(indexOrNode < this->GetNumNodes());
    assert(indexDeNode < this->GetNumNodes());
    
    return this->vecLinks.at(indexOrNode * this->numNodes + 
    indexDeNode).get();
}

bool Topology::CheckSlotDisp(const Route* route, unsigned int slot) const {
    Link* link;
    unsigned int numHops = route->GetNumHops();
    
    for(unsigned int a = 0; a < numHops; a++){
        link = route->GetLink(a);
        
        if(link->IsSlotOccupied(slot))
            return false;
    }
    return true;
}

bool Topology::CheckSlotsDisp(const Route* route, unsigned int iniSlot, 
unsigned int finSlot) const {
    Link* link;
    unsigned int numHops = route->GetNumHops();
    
    for(unsigned int a = 0; a < numHops; a++){
        link = route->GetLink(a);
        
        for(unsigned int b = iniSlot; b <= finSlot; b++)
            if(link->IsSlotOccupied(b))
                return false;
    }
    return true;
}

bool Topology::CheckBlockSlotsDisp(const Route* route, unsigned int numSlots) 
const {
    unsigned int numContiguousSlots = 0;

    for(unsigned int s = 0; s < this->numSlots; s++){
        if(this->CheckSlotDisp(route, s))
            numContiguousSlots++;
        else
            numContiguousSlots = 0;
        if(numContiguousSlots == numSlots)
            return true;
    }
    return false;
}

bool Topology::CheckOSNR(const Route* route, double OSNRth) {
    Link* link;
    unsigned int numHops = route->GetNumHops();
    std::shared_ptr<Signal> signal = std::make_shared<Signal>();
    
    for(unsigned int a = 0; a < numHops; a++){
        link = route->GetLink(a);
        link->CalcSignal(signal.get());
    }
    
    if(signal->GetOSNR() > OSNRth)
        return true;
    return false;
}

bool Topology::IsValidLink(const Link* link) {
    Node* sourceNode = this->GetNode(link->GetOrigimNode());
    Node* destNode = this->GetNode(link->GetDestinationNode());
    
    if(link != nullptr && this->IsValidNode(sourceNode) && 
       this->IsValidNode(destNode))
        return true;
    return false;
}

bool Topology::IsValidNode(const Node* node) {
    if(node != nullptr && node->GetNodeId() < this->numNodes)
        return true;
    return false;
}

bool Topology::IsValidRoute(const Route* route) {
    
    if(route != nullptr){
        Link* link;
        for(unsigned int a = 0; a < route->GetNumHops(); a++){
            link = route->GetLink(a);
            if(link == nullptr)
                return false;   
        }
        return true;
    }
    return false;
}

bool Topology::IsValidSlot(int index) {
    if(index >= 0 && index < (int) this->numSlots)
        return true;
    return false;
}

bool Topology::IsValidLigthPath(Call* call) {
    if( (this->IsValidRoute(call->GetRoute())) && 
        (call->GetFirstSlot() <= call->GetLastSlot()) && 
        (this->IsValidSlot(call->GetFirstSlot())) && 
        (this->IsValidSlot(call->GetLastSlot())) ){
        return true;
    }
        
    return false;
}

void Topology::Connect(Call* call) {
    Link* link;
    const Route* route = call->GetRoute();
    unsigned int numHops = route->GetNumHops();
    
    for(unsigned int a = 0; a < numHops; a++){
        link = route->GetLink(a);
        
        if(this->IsValidLink(link)){
            for(int s = call->GetFirstSlot(); s <= call->GetLastSlot(); s++){
                link->OccupySlot(s);
            }
        }
    }
    
}

void Topology::Release(Call* call) {
    Link* link;
    const Route* route = call->GetRoute();
    unsigned int numHops = route->GetNumHops();
    
    for(unsigned int a = 0; a < numHops; a++){
        link = route->GetLink(a);
        
        if(this->IsValidLink(link)){
            for(int s = call->GetFirstSlot(); s <= call->GetLastSlot(); s++){
                link->ReleaseSlot(s);
            }
        }
    }
}
