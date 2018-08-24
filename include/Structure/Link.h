/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Link.h
 * Author: bruno
 *
 * Created on August 4, 2018, 1:54 AM
 */

#ifndef LINK_H
#define LINK_H

#include <iostream>

/**
 * @brief Numerate the possible slot status.
 */
enum SlotStatus{
    SlotFree,
    SlotUsed
};

#include <vector>
#include <limits>
#include <iostream>

class Topology;

/**
 * @brief Class Link represents a link inside a topology. 
 */
class Link {
    friend std::ostream& operator<<(std::ostream& ostream,
    Link* link);
    
public:
    /**
     * @brief Standard constructor for a Link object.
     * @param topPointer pointer to a Topology object that
     * owns this link.
     * @param origimNode origin node of the link.
     * @param destinationNode destination node of the link.
     * @param length length of the link (meters).
     * @param numberSections total number of sections 
     * of the link.
     */
    Link(Topology* topPointer, unsigned int origimNode, 
    unsigned int destinationNode, double length, 
    unsigned int numberSections, unsigned int numberSlots);
    /**
     * @brief Copy constructor for a Link object.
     * @param orig original Link object.
     */
    Link(const Link& orig);
    /**
     * @brief Virtual destructor of a Link object.
     */
    virtual ~Link();
    
    /**
     * @brief Initialise the link, setting the start values
     * contained in it. 
     */
    void Initialise();
    
    /**
     * @brief Get the origin node of the link.
     * @return Origin node index of this link.
     */
    unsigned int GetOrigimNode() const;
    /**
     * @brief Set the origin node of the link.
     * @param origimNode origin node index of this link.
     */
    void SetOrigimNode(unsigned int origimNode);
    /**
     * @brief Get the destination node of the link.
     * @return Destination node index of this link.
     */
    unsigned int GetDestinationNode() const;
    /**
     * @brief Set the destination node of the link.
     * @param destinationNode Destination node index of this link.
     */
    void SetDestinationNode(unsigned int destinationNode);
    /**
     * @brief Get the length of the link.
     * @return Length of the link.
     */
    double GetLength() const;
    /**
     * @brief Set the length of the link.
     * @param length length of the link.
     */
    void SetLength(double length);
    /**
     * @brief Get the number of sections of the link.
     * @return Number of sections of the link.
     */
    unsigned int GetNumberSections() const;
    /**
     * @brief Set the number of sections of the link.
     * @param numberSections number of sections of the link.
     */
    void SetNumberSections(unsigned int numberSections);
    /**
     * @brief Get the cost of the link.
     * @return Cost of the link.
     */
    double GetCost() const;
    /**
     * @brief Set the cost of the link.
     * @param cost cost of the link.
     */
    void SetCost(double cost);
    
private:
    /**
     * @brief Pointer to a Topology object that
     * this link is contained
     */
    Topology* topPointer;
    /**
     * @brief Origin node of the link
     */
    unsigned int origimNode;
    /**
     * @brief Destination node of the link
     */
    unsigned int destinationNode;
    /**
     * @brief Length of this link (meters)
     */
    double length;
    /**
     * @brief Number of sections of this link
     */
    unsigned int numberSections;
    /**
     * @brief Cost of this link, based in the 
     * selected metric
     */
    double cost;
    /**
     * @brief Vector with slots status, free or occupied,
     * in this link
     */
    std::vector<SlotStatus> slotsStatus;
};

#endif /* LINK_H */

