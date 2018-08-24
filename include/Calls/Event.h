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

typedef double TIME;

/**
 * @brief Numerate the event types.
 */
enum EventType{
    CallRequest,
    CallEnd
};

class Event {
public:
    Event();
    Event(const Event& orig);
    virtual ~Event();
private:
    
};

#endif /* EVENT_H */

