/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Data.cpp
 * Author: bruno
 * 
 * Created on August 8, 2018, 6:25 PM
 */

#include "../../include/Data/Data.h"

#include "../../include/SimulationType/SimulationType.h"
#include "../../include/Data/Parameters.h"

std::ostream& operator<<(std::ostream& ostream, 
const Data* data) {
    unsigned int sizeLoad = data->simulType->
    GetParameters()->GetNumberLoadPoints();
        
    ostream << "DATA" << std::endl;
    
    for(unsigned int a = 0; a < sizeLoad; ++a){
        ostream << "Load " << data->simulType->
        GetParameters()->GetLoadPoint(a) << std::endl;
        
        ostream << "Number of requisitions: "
                << data->GetNumberReqLoad(a) << std::endl;
        ostream << "Number of blocked requisitions: "
                << data->GetNumberBlocReqLoad(a) << std::endl;
        ostream << "Number of accepted requisitions: "
                << data->GetNumberAccReqLoad(a) << std::endl;
        ostream << "Number of blocked slots: "
                << data->GetNumberBlocSlotsLoad(a) << std::endl;
        ostream << "Number of accepted slots: "
                << data->GetNumberAccSlotsLoad(a) << std::endl;
        ostream << "Mean hops per route: "
                << data->GetMeanHopsPerRouteLoad(a) << std::endl;
        ostream << "Network occupancy: "
                << data->GetNetOccupancyLoad(a) << std::endl;
        ostream << std::endl;
    }
    
    return ostream;
}

Data::Data(SimulationType* simulType) 
:simulType(simulType), numberReq(0), numberBlocReq(0),
numberAccReq(0), numberBlocSlots(0), numberAccSlots(0),
meanHopsPerRoute(0), netOccupancy(0) {
    
}

Data::~Data() {
    
}

void Data::Initialise() {
    int size = this->simulType->GetParameters()->GetNumberLoadPoints();
    this->numberReq.resize(size, 0.0);
    this->numberBlocReq.resize(size, 0.0);
    this->numberAccReq.resize(size, 0.0);
    this->numberBlocSlots.resize(size, 0.0);
    this->numberAccSlots.resize(size, 0.0);
    this->meanHopsPerRoute.resize(size, 0.0);
    this->netOccupancy.resize(size, 0.0);
}

std::vector<double> Data::GetNumberReq() const {
    return numberReq;
}

double Data::GetNumberReqLoad(unsigned int index) const {
    return this->numberReq.at(index);
}

void Data::SetNumberReq(std::vector<double> numberReq) {
    this->numberReq = numberReq;
}

std::vector<double> Data::GetNumberBlocReq() const {
    return numberBlocReq;
}

double Data::GetNumberBlocReqLoad(unsigned int index) const {
    return this->numberBlocReq.at(index);
}

void Data::SetNumberBlocReq(std::vector<double> numberBlocReq) {
    this->numberBlocReq = numberBlocReq;
}

std::vector<double> Data::GetNumberAccReq() const {
    return numberAccReq;
}

double Data::GetNumberAccReqLoad(unsigned int index) const {
    return this->numberAccReq.at(index);
}

void Data::SetNumberAccReq(std::vector<double> numberAccReq) {
    this->numberAccReq = numberAccReq;
}

std::vector<double> Data::GetNumberBlocSlots() const {
    return numberBlocSlots;
}

double Data::GetNumberBlocSlotsLoad(unsigned int index) const {
    return this->numberBlocSlots.at(index);
}

void Data::SetNumberBlocSlots(std::vector<double> numberBlocSlots) {
    this->numberBlocSlots = numberBlocSlots;
}

std::vector<double> Data::GetNumberAccSlots() const {
    return numberAccSlots;
}

double Data::GetNumberAccSlotsLoad(unsigned int index) const {
    return this->numberAccSlots.at(index);
}

void Data::SetNumberAccSlots(std::vector<double> numberAccSlots) {
    this->numberAccSlots = numberAccSlots;
}

std::vector<double> Data::GetMeanHopsPerRoute() const {
    return meanHopsPerRoute;
}

double Data::GetMeanHopsPerRouteLoad(unsigned int index) const {
    return this->meanHopsPerRoute.at(index);
}

void Data::SetMeanHopsPerRoute(std::vector<double> meanHopsPerRoute) {
    this->meanHopsPerRoute = meanHopsPerRoute;
}

std::vector<double> Data::GetNetOccupancy() const {
    return netOccupancy;
}

double Data::GetNetOccupancyLoad(unsigned int index) const {
    return this->netOccupancy.at(index);
}

void Data::SetNetOccupancy(std::vector<double> netOccupancy) {
    this->netOccupancy = netOccupancy;
}
