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

class Call {
public:
    /**
     * @brief Standard constructor of a Call object.
     * @param orNode call origin node.
     * @param deNode call destination node.
     * @param bitRate call bit rate.
     */
    Call(Node* orNode, Node* deNode, double bitRate);
    Call(const Call& orig);
    virtual ~Call();
    
    /**
     * @brief 
     * @return 
     */
    Node* GetDeNode() const;
    /**
     * @brief 
     * @param deNode
     */
    void SetDeNode(Node* deNode);
    /**
     * @brief 
     * @return 
     */
    Node* GetOrNode() const;
    /**
     * @brief 
     * @param orNode
     */
    void SetOrNode(Node* orNode);
    
private:
    Node* orNode;
    Node* deNode;
    unsigned int numberSlots;
    std::vector<SlotStatus> slots;
    double osnrTh;
    double bandwidth;
    double bitRate;
};

#endif /* CALL_H */

