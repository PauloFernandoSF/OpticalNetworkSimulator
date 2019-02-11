/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MultiCoreCall.cpp
 * Author: paulofilho
 * 
 * Created on 7 de fevereiro de 2019, 16:31
 */

#include "../../include/Calls/MultiCoreCall.h"
#include "../../include/ResourceAllocation/SA.h"
#include "../../include/Calls/Call.h"
#include "../../include/ResourceAllocation/Route.h"
#include "../../include/Structure/Topology.h"

MultiCoreCall::MultiCoreCall(Node* orNode, Node* deNode, double bitRate, 
TIME deacTime):Call(orNode, deNode, bitRate, deacTime) {
    
}

//MultiCoreCall::MultiCoreCall(const MultiCoreCall& orig) {
//}

MultiCoreCall::~MultiCoreCall() {
}

void MultiCoreCall::SetCore(int core){
    coreIndex = core;
}

int MultiCoreCall::GetCore(){
    return coreIndex;
}