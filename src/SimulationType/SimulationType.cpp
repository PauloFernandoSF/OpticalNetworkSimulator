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
#include "../../include/Calls/CallGenerator.h"

SimulationType::SimulationType(unsigned int simulIndex)
:simulationIndex(simulIndex),
parameters(std::make_shared<Parameters> (this)), 
options(std::make_shared<Options> (this)), 
data(boost::make_unique<Data>(this)),
topology(std::make_shared<Topology> (this)),
inputOutput(boost::make_unique<InputOutput>(this)),
traffic(std::make_shared<Traffic>(this)),
callGenerator(nullptr) {
    
}

SimulationType::~SimulationType() {
    this->parameters.reset();
    this->options.reset();
    this->data.release();
    this->topology.reset();
    this->inputOutput.release();
    this->traffic.reset();
    this->callGenerator.reset();
}

void SimulationType::Load() {
    this->parameters->Load();
    this->options->Load();
    this->topology->LoadFile();
    this->traffic->LoadFile();
    this->GetData()->Initialise();
}

void SimulationType::LoadFile() {
    this->parameters->LoadFile();
    this->options->LoadFile();
    this->topology->LoadFile();
    this->traffic->LoadFile();
    this->GetData()->Initialise();
}

void SimulationType::Print() {
    std::cout << this->parameters << std::endl;
    std::cout << this->options << std::endl;
    //std::cout << this->topology << std::endl;
    std::cout << this->traffic << std::endl;
    std::cout << this->GetData() << std::endl;
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

void SimulationType::SetParameters(std::shared_ptr<Parameters> 
parameters) {
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
    std::swap(this->data, data);
}

Topology* SimulationType::GetTopology() const {
    return topology.get();
}

void SimulationType::SetTopology(std::shared_ptr<Topology> 
topology) {
    this->topology = topology;
}

InputOutput* SimulationType::GetInputOutput() const {
    return inputOutput.get();
}

void SimulationType::SetInputOutput(std::unique_ptr<InputOutput> 
inputOutput) {
    this->inputOutput = std::move(inputOutput);
}

Traffic* SimulationType::GetTraffic() const {
    return traffic.get();
}

void SimulationType::SetTraffic(std::shared_ptr<Traffic> 
traffic) {
    this->traffic = traffic;
}

CallGenerator* SimulationType::GetCallGenerator() const {
    return callGenerator.get();
}

void SimulationType::SetCallGenerator(std::shared_ptr<CallGenerator> 
callGenerator) {
    this->callGenerator = callGenerator;
}
