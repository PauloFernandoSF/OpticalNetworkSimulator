/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Event.h
 * Author: bruno
 *
 * Created on August 19, 2018, 6:12 PM
 */

#ifndef EVENT_H
#define EVENT_H

class CallGenerator;

#include <memory>
#include <boost/assign/list_of.hpp>
#include <boost/unordered_map.hpp>

#include "Call.h"

/**
 * @brief Numerate the event types.
 */
enum EventType{
    CallInvalid,
    CallRequest,
    CallEnd,
    FirsEventType = CallRequest,
    LastEventType = CallEnd
};

/**
 * @brief 
 */
class Event {
    friend std::ostream& operator<<(std::ostream& ostream, 
    const Event* event);
    
public:
    
    Event(CallGenerator* generator, std::shared_ptr<Call> call, 
          TIME time);
    Event(const Event& orig);
    virtual ~Event();
    
    /**
     * @brief Get the type of this event.
     * @return the Type of event.
     */
    EventType GetEventType() const;
    
    std::string GetEventName() const;
    /**
     * @brief Set the type of this event.
     * @param eventType type of event.
     */
    void SetEventType(EventType eventType);

    TIME GetEventTime() const;

    void SetEventTime(TIME eventTime);
    
    Call* GetCall() const;
    
    void SetCall(std::shared_ptr<Call> call);
    
    void ImplementCallRequest();
    
    void ImplementCallEnd();

private:
    
    CallGenerator* parGenerator;
    /**
     * @brief Type of event.
     * The event can be a call request or a call end.
     */
    EventType eventType;
    /**
     * @brief Time of the event must occur.
     */
    TIME eventTime;
    /**
     * @brief Pointer to an Call object belong to this Event.
     */
    std::shared_ptr<Call> call;
    
    static const boost::unordered_map<EventType, 
    std::string> mapEventType;
};

#endif /* EVENT_H */

