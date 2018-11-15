/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Event.cpp
 * Author: bruno
 * 
 * Created on August 19, 2018, 6:12 PM
 */

#include "../../include/Calls/Event.h"

//#include "../../include/Calls/Call.h"
#include "../../include/Calls/CallGenerator.h"

const boost::unordered_map<EventType, std::string> 
Event::mapEventType = boost::assign::map_list_of
    (CallInvalid, "Invalid")
    (CallRequest, "Call request")
    (CallEnd, "Call end");

std::ostream& operator<<(std::ostream& ostream, const Event* event){
    
    ostream << "Event" << std::endl;
    ostream << "Time: " << event->GetEventTime() << std::endl;
    ostream << "Type: " << event->GetEventName() << std::endl << std::endl;
    
    if(event->GetCall() != nullptr)
        ostream << event->GetCall() << std::endl;
    
    return ostream;
}

Event::Event(CallGenerator* generator, std::shared_ptr<Call> call, TIME time)
:parGenerator(generator), eventType(CallRequest), eventTime(time),
call(call) {

}

Event::~Event() {
    //this->call.release();
}

EventType Event::GetEventType() const {
    return eventType;
}

std::string Event::GetEventName() const {
    return mapEventType.at(this->eventType);
}

void Event::SetEventType(EventType eventType) {
    assert(eventType >= FirsEventType && eventType <= LastEventType);
    this->eventType = eventType;
}

TIME Event::GetEventTime() const {
    return eventTime;
}

void Event::SetEventTime(TIME eventTime) {
    this->eventTime = eventTime;
}

Call* Event::GetCall() const {
    return this->call.get();
}

void Event::SetCall(std::shared_ptr<Call> call) {
    this->call = call;
}

void Event::ImplementCallRequest() {
    //Funções de tentativa de alocação da requisição.
    
    this->call->SetStatus(Accepted);
    //Change the Event type for CallEnd
    //and sets the Event time from the call deacTime.
    switch(this->call->GetStatus()){
        case Accepted:
            this->SetEventType(CallEnd);
            this->SetEventTime(this->parGenerator->GetSimulationTime() + 
                               this->call->GetDeactivationTime());
            //Função para fazer
            break;
        case Blocked:    
            call.reset();
            break;
        default:
            std::cout << "Invalid Call status" << std::endl;
    }
}

void Event::ImplementCallEnd() {
    //Functions for release the connection.
    
    
    //Pop the event from the list.
    //this->parGenerator->PopTopEvent();
}
