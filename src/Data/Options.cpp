/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Options.cpp
 * Author: bruno
 * 
 * Created on August 3, 2018, 1:18 AM
 */

#include "../../include/Data/Options.h"

#include "../../include/SimulationType/SimulationType.h"
#include "../../include/Data/InputOutput.h"

const boost::unordered_map<TopologyOption, std::string> 
Options::mapTopologyOptions = boost::assign::map_list_of
    (TopologyInvalid, "Invalid")
    (TopologyNSFNet, "NSFNet")
    (TopologyRing, "Ring")
    (TopologyToroidal, "Toroidal")
    (TopologyGermany,  "Germany")
    (TopologyItaly, "Italy");

const boost::unordered_map<RoutingOption, std::string>
Options::mapRoutingOptions = boost::assign::map_list_of
    (RoutingInvalid, "Invalid")
    (RoutingDJK, "Dijkstra")
    (RoutingYEN, "YEN")
    (RoutingBSR, "BSR");

const boost::unordered_map<SpectrumAllocationOption, std::string>
Options::mapSpecAlgOptions = boost::assign::map_list_of
    (SpecAllInvalid, "Invalid")
    (SpecAllRandom, "Random")
    (SpecAllFF, "First Fit")
    (SpecAllMSCL, "MSCL");

const boost::unordered_map<LinkCostType, std::string>
Options::mapLinkCostType = boost::assign::map_list_of
    (Invalid, "Invalid cost type")
    (MinHops, "Minimum hops")
    (MinLength, "Minimum length")
    (MinLengthNormalized, "Minimum length normalized");

const boost::unordered_map<TrafficOption, std::string>
Options::mapTrafficOptions = boost::assign::map_list_of
    (TrafficInvalid, "Invalid")
    (Traficc_100_200_400, "100-200-400")
    (Traffic_10_40_100_200_400, "10-40-100-200-400");

std::ostream& operator<<(std::ostream& ostream,
    const Options* options) {
    ostream << "OPITIONS" << std::endl;
    ostream << "Topology: " << options->GetTopologyName()
            << std::endl;
    ostream << "Routing algorithm: " << options->GetRoutingName()
            << std::endl;
    ostream << "Spectral allocation algorithm: " << 
            options->GetSpecAllName() << std::endl;
    ostream << "Links cost type: " << options->GetLinkCostTypeName()
            << std::endl;
    ostream << "Traffic requests(Gbps): " << options->GetTrafficName()
            << std::endl;
    
    return ostream;
}

Options::Options(SimulationType* simulType)
:simulType(simulType), topologyOption(TopologyInvalid),
routingOption(RoutingInvalid), specAllOption(SpecAllInvalid),
linkCostType(Invalid), trafficOption(TrafficInvalid) {
    
}

Options::~Options() {

}

void Options::LoadFile() {
    std::ifstream auxIfstream;
    int auxInt;
    
    this->simulType->GetInputOutput()->LoadOptions(auxIfstream);
    auxIfstream >> auxInt;
    this->SetTopologyOption((TopologyOption) auxInt);
    auxIfstream >> auxInt;
    this->SetRoutingOption((RoutingOption) auxInt);
    auxIfstream >> auxInt;
    this->SetSpecAllOption((SpectrumAllocationOption) auxInt);
    auxIfstream >> auxInt;
    this->SetLinkCostType((LinkCostType) auxInt);
    auxIfstream >> auxInt;
    this->SetTrafficOption((TrafficOption) auxInt);
}

TopologyOption Options::GetTopologyOption() const {
    return topologyOption;
}

std::string Options::GetTopologyName() const {
    return mapTopologyOptions.at(this->topologyOption);
}

void Options::SetTopologyOption(TopologyOption topologyOption) {
    assert(topologyOption >= FirstTopology && 
           topologyOption <= LastTopology);
    this->topologyOption = topologyOption;
}

RoutingOption Options::GetRoutingOption() const {
    return routingOption;
}

std::string Options::GetRoutingName() const {
    return mapRoutingOptions.at(this->routingOption);
}

void Options::SetRoutingOption(RoutingOption routingOption) {
    assert(routingOption >= FirstRoutingOption && 
           routingOption <= LastRoutingOption);
    this->routingOption = routingOption;
}

SpectrumAllocationOption Options::GetSpecAllOption() const {
    return specAllOption;
}

std::string Options::GetSpecAllName() const {
    return mapSpecAlgOptions.at(this->specAllOption);
}

void Options::SetSpecAllOption(SpectrumAllocationOption specAllOption) {
    assert(specAllOption >= FirstSpecAllOption &&
           specAllOption <= LastSpecAllOption);
    this->specAllOption = specAllOption;
}

LinkCostType Options::GetLinkCostType() const {
    return linkCostType;
}

std::string Options::GetLinkCostTypeName() const {
    return mapLinkCostType.at(this->linkCostType);
}

void Options::SetLinkCostType(LinkCostType linkCostType) {
    assert(linkCostType >= FirstLinkCostType &&
           linkCostType <= LastLinkCostType);
    this->linkCostType = linkCostType;
}

TrafficOption Options::GetTrafficOption() const {
    return trafficOption;
}

std::string Options::GetTrafficName() const {
    return mapTrafficOptions.at(this->trafficOption);
}

void Options::SetTrafficOption(TrafficOption trafficOption) {
    assert(trafficOption >= FirstTrafficOption &&
           trafficOption <= LastTrafficOption);
    this->trafficOption = trafficOption;
}
