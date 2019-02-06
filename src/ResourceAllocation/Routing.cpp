/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Routing.cpp
 * Author: BrunoVinicius
 * 
 * Created on November 19, 2018, 11:43 PM
 */

#include "../../include/ResourceAllocation/Routing.h"
#include "../../include/ResourceAllocation/Route.h"
#include "../../include/Structure/Topology.h"
#include "../../include/Structure/Link.h"
#include "../../include/ResourceAllocation/ResourceAlloc.h"
#include "../../include/GeneralClasses/Def.h"
#include "../../include/Calls/Call.h"

bool Routing::RouteCompare::operator()(const std::shared_ptr<Route> routeA, 
                                       const std::shared_ptr<Route> routeB) {
    
    return (routeA->GetCost() > routeB->GetCost());
}

Routing::Routing(ResourceAlloc* rsa, RoutingOption option, Topology* topology)
:resourceAlloc(rsa), routingOption(option), topology(topology), K(3) {

}

Routing::~Routing() {
}

void Routing::RoutingCall(Call* call) {
    switch(this->routingOption){
        case RoutingDJK:
        case RoutingYEN:
        case RoutingBSR:
            this->SetOfflineRouting(call);
            break;
        default:
            std::cerr << "Invalid routing option" << std::endl;
    }
}

void Routing::SetOfflineRouting(Call* call) {
    NodeId orNode = call->GetOrNode()->GetNodeId();
    NodeId deNode = call->GetDeNode()->GetNodeId();

    call->PushTrialRoutes(this->resourceAlloc->GetRoutes(orNode, deNode));
}

void Routing::Dijkstra() {
    std::shared_ptr<Route> route;
    unsigned int numNodes = this->topology->GetNumNodes();
    
    for(unsigned int orN = 0; orN < numNodes; orN++){
        for(unsigned int deN = 0; deN < numNodes; deN++){
            if(orN != deN){
                route = this->Dijkstra(orN, deN);
            }
            else{
                route = nullptr;
            }
            this->resourceAlloc->SetRoute(orN, deN, route);
        }
    }
}

std::shared_ptr<Route> Routing::Dijkstra(NodeId orNode, NodeId deNode) {
    int k=-1, h, hops;
    unsigned int i, j, VA;
    long double min;
    unsigned int numNodes = this->topology->GetNumNodes();
    std::vector<int> r;
    Link *link;
    std::shared_ptr<Route> routeDJK = nullptr;
    
    double *CustoVertice = new double[numNodes];
    int *Precedente = new int[numNodes];
    int *PathRev = new int[numNodes];
    bool *Status = new bool[numNodes];
    assert(orNode != deNode);
    bool networkDisconnected = false;

    //Initializes all vertices with infinite cost
    //and the source vertice with cost zero
    for(i = 0; i < numNodes; i++){
        if(i != orNode)
            CustoVertice[i] = Def::Max_Double;
        else
            CustoVertice[i] = 0.0;
        
        Precedente[i] = -1;
        Status[i] = 0;
    }
    VA = numNodes;

    while(VA > 0 && !networkDisconnected){

        min = Def::Max_Double;
        
        for(i = 0; i < numNodes; i++)
            if((Status[i] == 0) && (CustoVertice[i] < min)){
                min = CustoVertice[i];
                k = i;
            }

        if(k == (int) deNode)
            break;
        
        Status[k] = 1;
        VA = VA - 1;
        bool outputLinkFound = false;

        for(j = 0; j < numNodes; j++){
            link = this->topology->GetLink((unsigned int) k, 
                                           (unsigned int) j);
            //(link->GetCost() < Def::Max_Double)
            if((link != NULL) && (link->IsLinkWorking()) && 
               (this->topology->GetNode(link->GetOrigimNode())->
               IsNodeWorking()) &&
               (this->topology->GetNode(link->GetDestinationNode())->
               IsNodeWorking())){
                outputLinkFound = true;

                if((Status[j] == 0) && 
                   (CustoVertice[k] + link->GetCost() < CustoVertice[j])){
                    CustoVertice[j] = CustoVertice[k] + link->GetCost();
                    Precedente[j] = k;
                }
            }
        }
        
        if(!outputLinkFound)
            networkDisconnected = true;
    }//Fim do while

    if(!networkDisconnected){
        PathRev[0] = deNode;
        hops = 0;
        j = deNode;
        
        while(j != orNode){
            hops = hops + 1;
            PathRev[hops] = Precedente[j];
            j = Precedente[j];
        }
        r.clear();
        
        for(h = 0; h <= hops; h++)
            r.push_back(PathRev[hops-h]);
        
        routeDJK = std::make_shared<Route>(this->GetResourceAlloc(), r);
    }

    delete []CustoVertice; delete []Precedente; 
    delete []Status; delete []PathRev;
    
    if(routeDJK != nullptr)
        return routeDJK;
    else
        return nullptr;
}

void Routing::YEN() {
    std::vector<std::shared_ptr<Route>> routes;
    unsigned int numNodes = this->topology->GetNumNodes();
    
    for(unsigned int orN = 0; orN < numNodes; orN++){
        for(unsigned int deN = 0; deN < numNodes; deN++){
            if(orN != deN){
                routes = this->YEN(orN, deN);
            }
            else{
                routes.resize(this->GetK(), nullptr);
            }
            this->resourceAlloc->SetRoutes(orN, deN, routes);
            routes.clear();
        }
    }
}

std::vector<std::shared_ptr<Route> > Routing::YEN(NodeId orNode, 
                                                  NodeId deNode) {
    assert(orNode != deNode);
    std::vector<std::shared_ptr<Route>> routesYEN;
    std::priority_queue<std::shared_ptr<Route>, 
                        std::vector<std::shared_ptr<Route>>,
                        RouteCompare> candidateRoutes;
    Node* spurNode;
    std::shared_ptr<Route> spurPath;
    std::shared_ptr<Route> rootPath;
    std::shared_ptr<Route> totalPath;
    
    // Determine the shortest path from the source to the destination.
    std::shared_ptr<Route> newRoute = this->Dijkstra(orNode, deNode);
    routesYEN.push_back(newRoute);
    
    for(unsigned int k = 1; k < this->K; k++){
        unsigned int auxSize = routesYEN.at(k-1)->GetNumNodes() - 2;
        
        //The spurNode ranges from the first node to the next to last node 
        //in the previous k-shortest path.
        for(unsigned int i = 0; i <= auxSize; i++){
            //spurNode is retrieved from the previous k-shortest path, k − 1.
            spurNode = routesYEN.at(k-1)->GetNodePointer(i);
            // The sequence of nodes from the source to the spurNode of the 
            //previous k-shortest path.
            rootPath = routesYEN.at(k-1)->CreatePartialRoute(0, i);
            
            for(auto it: routesYEN){
                // Remove the links that are part of the previous shortest 
                //paths which share the same rootPath.
                newRoute = it->CreatePartialRoute(0, i);
                if(rootPath->GetPath() == newRoute->GetPath()){
                    it->GetLink(i)->SetLinkState(false);
                }
            }
            
            for(unsigned int  a = 0; a < rootPath->GetNumNodes(); a++){
                if(rootPath->GetNodePointer(a)->GetNodeId() == spurNode->GetNodeId())
                    continue;
                rootPath->GetNodePointer(a)->SetNodeState(false);
            }
            
            // Calculate the spurPath from the spurNode to the destination.
            spurPath = this->Dijkstra(spurNode->GetNodeId(), deNode);
            
            if(spurPath != nullptr){
                // Entire path is made up of the rootPath and spurPath.
                totalPath = rootPath->AddRoute(spurPath);
                // Add the potential k-shortest path to the queue.
                candidateRoutes.push(totalPath);
            }
            
            // Add back the edges and nodes that were removed from the graph.
            this->topology->SetAllLinksWorking();
            rootPath->SetAllNodesWorking();
        }
        if(candidateRoutes.empty())
            break;    
        
        //Get the first route and store it in vector candidateRoutes
        routesYEN.push_back(candidateRoutes.top());
        candidateRoutes.pop();
    }
    
    while(routesYEN.size() < this->K){
        routesYEN.push_back(nullptr);
    }
    
    return routesYEN;
}

ResourceAlloc* Routing::GetResourceAlloc() const {
    return resourceAlloc;
}

void Routing::SetResourceAlloc(ResourceAlloc* rsaAlgorithm) {
    this->resourceAlloc = rsaAlgorithm;
}

RoutingOption Routing::GetRoutingOption() const {
    return routingOption;
}

void Routing::SetRoutingOption(RoutingOption routingOption) {
    this->routingOption = routingOption;
}

Topology* Routing::GetTopology() const {
    return topology;
}

void Routing::SetTopology(Topology* topology) {
    this->topology = topology;
}

unsigned int Routing::GetK() const {
    return K;
}

void Routing::SetK(unsigned int K) {
    this->K = K;
}
