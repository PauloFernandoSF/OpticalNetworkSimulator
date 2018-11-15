/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Call.h
 * Author: bruno
 *
 * Created on August 17, 2018, 11:40 PM
 */

#ifndef CALL_H
#define CALL_H

#include <vector>
#include <memory>

class Node;
class SimulationType;

#include "../Structure/Link.h"
#include "CallGenerator.h"

/**
 * @brief Lists the possible status of a Call.
 */
enum CallStatus{
    NotEvaluated,
    Accepted,
    Blocked
};

class Call {
    friend std::ostream& operator<<(std::ostream& ostream, 
    const Call* call);
    
public:
    /**
     * @brief Standard constructor of a Call object.
     * @param orNode call origin node.
     * @param deNode call destination node.
     * @param bitRate call bit rate.
     */
    Call(Node* orNode, Node* deNode, double bitRate, TIME deacTime);
    
    Call(const Call& orig);
    virtual ~Call();
    
    /**
     * @brief Return the status of this Call.
     * @return Call status.
     */
    CallStatus GetStatus() const;
    
    std::string GetStatusName() const;
    /**
     * @brief Sets the status of this Call.
     * @param status Status of the call.
     */
    void SetStatus(CallStatus status);

    /**
     * @brief Get a pointer to a Node object
     * representing the origin node of this call.
     * @return pointer to an Node object.
     */
    Node* GetOrNode() const;
    /**
     * @brief Set a pointer to a Node object
     * representing the origin node of this Call.
     * @param orNode pointer to an Node object.
     */
    void SetOrNode(Node* orNode);
    /**
     * @brief Get a pointer to a Node object
     * representing the destination node of this Call.
     * @return pointer to an Node object.
     */
    Node* GetDeNode() const;
    /**
     * @brief Set a pointer to a Node object
     * representing the destination node of this Call.
     * @param deNode pointer to an Node object.
     */
    void SetDeNode(Node* deNode);
    
    unsigned int GetNumberSlots() const;

    void SetNumberSlots(unsigned int numberSlots);
    
    double GetOsnrTh() const;

    void SetOsnrTh(double osnrTh);
    
    double GetBandwidth() const;

    void SetBandwidth(double bandwidth);

    double GetBitRate() const;

    void SetBitRate(double bitRate); 
    
    TIME GetDeactivationTime() const;

    void SetDeactivationTime(TIME deactivationTime);

    
private:
    /**
     * @brief Status of this Call.
     */
    CallStatus status;
    /**
     * @brief Pointer of a Node object
     * representing the origin node of this call.
     */
    Node* orNode;
    /**
     * @brief Pointer of a Node object
     * representing the destination node of this call.
     */
    Node* deNode;
    /**
     * @brief Number of slots occupied by this call.
     * This value is calculate based in modulation used 
     * and bitrate of this Call and the size of slots of 
     * the fibers.
     */
    unsigned int numberSlots;
    /**
     * @brief Vector representing the slots occupied 
     * by this call.
     * This vector has size equal to the number of 
     * slots in fibers.
     */
    std::vector<SlotStatus> slots;
    /**
     * @brief OSNr of the call calculated based 
     * in the distance of origin and destination node,
     * modulation used and the bitrate of this Call.
     */
    double osnrTh;
    /**
     * @brief Bandwidth occupied by this call, based 
     * in the bitrate and modulation used.
     */
    double bandwidth;
    /**
     * @brief Bitrate of this call.
     */
    double bitRate;
    /**
     * @brief Deactivation time of this Call.
     * Not used if the call is blocked.
     */
    TIME deactivationTime;
    
    static const boost::unordered_map<CallStatus, 
    std::string> mapCallStatus;
};

#endif /* CALL_H */

