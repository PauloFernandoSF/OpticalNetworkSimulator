/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SimulationType.cpp
 * Author: bruno
 * 
 * Created on August 2, 2018, 3:50 PM
 */

#include <boost/make_unique.hpp>

#include "../../include/SimulationType/SimulationType.h"

#include "../../include/Data/Parameters.h"
#include "../../include/Data/Options.h"
#include "../../include/Data/Data.h"
#include "../../include/Data/InputOutput.h"
#include "../../include/Structure/Topology.h"
#include "../../include/Calls/Traffic.h"

SimulationType::SimulationType(unsigned int simulIndex)
:simulationIndex(simulIndex),
parameters(std::make_shared<Parameters> (this)), 
options(std::make_shared<Options> (this)), 
data(boost::make_unique<Data>(this)), 
topology(std::make_shared<Topology> (this)),
inputOutput(boost::make_unique<InputOutput>(this)),
traffic(std::make_shared<Traffic>(this)) {
    
}

SimulationType::~SimulationType() {
    parameters.~__shared_ptr();
    options.~__shared_ptr();
    data.~unique_ptr();
    topology.~__shared_ptr();
    inputOutput.~unique_ptr();
    traffic.~__shared_ptr();
}

void SimulationType::LoadFile() {
    this->parameters->LoadFile();
    this->options->LoadFile();
    this->topology->LoadFile();
    this->traffic->LoadFile();
}

void SimulationType::AdditionalSettings() {
    this->topology->SetAditionalSettings();
}

const unsigned int SimulationType::GetSimulationIndex() const {
    return simulationIndex;
}

Parameters* SimulationType::GetParameters() const {
    return parameters.get();
}

void SimulationType::SetParameters(std::shared_ptr<Parameters> parameters) {
    this->parameters = parameters;
}

Options* SimulationType::GetOptions() const {
    return options.get();
}

void SimulationType::SetOptions(std::shared_ptr<Options> options) {
    this->options = options;
}

Data* SimulationType::GetData() const {
    return data.get();
}

void SimulationType::SetData(std::unique_ptr<Data> data) {
    this->data = std::move(data);
}

Topology* SimulationType::GetTopology() const {
    return topology.get();
}

void SimulationType::SetTopology(std::shared_ptr<Topology> topology) {
    this->topology = topology;
}

InputOutput* SimulationType::GetInputOutput() const {
    return inputOutput.get();
}

void SimulationType::SetInputOutput(std::unique_ptr<InputOutput> inputOutput) {
    this->inputOutput = std::move(inputOutput);
}

Traffic* SimulationType::GetTraffic() const {
    return traffic.get();
}

void SimulationType::SetTraffic(std::shared_ptr<Traffic> traffic) {
    this->traffic = traffic;
}
