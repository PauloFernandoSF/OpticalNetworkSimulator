/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Route.cpp
 * Author: BrunoVinicius
 * 
 * Created on November 15, 2018, 10:40 PM
 */

#include "../../include/ResourceAllocation/Route.h"
#include "../../include/ResourceAllocation/ResourceAlloc.h"
#include "../../include/Structure/Topology.h"
#include "../../include/Structure/Link.h"
#include "../../include/Structure/Node.h"

Route::Route(ResourceAlloc* rsaAlg, const std::vector<int>& path)
:resourceAlloc(rsaAlg), topology(rsaAlg->GetTopology()), path(path),
pathNodes(0) {
    
    for(auto it: this->path){
        this->pathNodes.push_back(this->topology->GetNode(it));
    }
}

Route::Route(const Route& orig) {
}

Route::~Route() {
    
}

bool Route::operator==(const Route& right) const {
    
    if(right.path == this->path)
        return true;
    
    return false;
}

int Route::GetOrNode() const {
    assert(this->path.size() > 0);
    
    return this->path.front();
}

Node* Route::GetOrNodePointer() const {
    assert(this->pathNodes.size() > 0);
    
    return this->pathNodes.front();
}

int Route::GetDeNode() const {
    assert(this->path.size() > 0);
    
    return this->path.back();
}

Node* Route::GetDeNodePointer() const {
    assert(this->pathNodes.size() > 0);
    
    return this->pathNodes.back();
}

int Route::GetNode(unsigned int index) const {
    assert(index >= 0 && index < this->path.size());
    
    return this->path.at(index);
}

Node* Route::GetNodePointer(unsigned int index) const {
    assert(index >= 0 && index < this->pathNodes.size());
    
    return this->pathNodes.at(index);
}

unsigned int Route::GetNumHops() const {
    return this->path.size() - 1;
}

unsigned int Route::GetNumNodes() const {
    return this->path.size();
}

std::vector<int> Route::GetPath() {
    return this->path;
}

double Route::GetCost() {
    Link *link;
    double cost = 0.0;
    
    for(unsigned int a = 0; a < this->GetNumHops(); a++){
        link = this->topology->GetLink(this->path.at(a), this->path.at(a+1));
        cost += link->GetCost();
    }
    
    return cost;
}

Link* Route::GetLink(unsigned int index) const {
    assert(index < this->path.size());
    
    return this->topology->GetLink(this->GetNode(index), 
                                   this->GetNode(index + 1));
}

void Route::SetAllNodesWorking() {
    
    for(auto it: this->pathNodes){
        it->SetNodeState(true);
    }
}

std::shared_ptr<Route> Route::CreatePartialRoute(unsigned int ind1, 
unsigned int ind2) {
    std::vector<int> newPath(0);
    
    for(unsigned int a = ind1; a <= ind2; a++){
        newPath.push_back(this->GetNode(a));
    }
    
    return std::make_shared<Route>(this->resourceAlloc, newPath);
}

std::shared_ptr<Route> Route::AddRoute(std::shared_ptr<Route>& route) {
    assert(this->GetDeNodePointer() == route->GetOrNodePointer());
    std::vector<int> newPath = this->GetPath();
    
    for(unsigned int a = 1; a < route->GetNumNodes(); a++){
        newPath.push_back(route->GetNode(a));
    }
    
    return std::make_shared<Route>(this->resourceAlloc, newPath);
}
