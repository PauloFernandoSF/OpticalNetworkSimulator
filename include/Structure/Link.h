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

class Link {
public:
    Link();
    Link(unsigned int origimNode, unsigned int destinationNode, 
    double length, unsigned int numberSections);

    Link(const Link& orig);
    virtual ~Link();
    
    void initialise();
    
    unsigned int GetOrigimNode() const;

    void SetOrigimNode(unsigned int origimNode);
    
    unsigned int GetDestinationNode() const;

    void SetDestinationNode(unsigned int destinationNode);

    double GetLength() const;

    void SetLength(double length);

    unsigned int GetNumberSections() const;

    void SetNumberSections(unsigned int numberSections);

private:
    /**
     * @brief 
     */
    unsigned int origimNode;
    /**
     * @brief 
     */
    unsigned int destinationNode;
    /**
     * @brief 
     */
    double length;
    /**
     * @brief 
     */
    unsigned int numberSections;
    /**
     * @brief 
     */
    double cost;
    /**
     * @brief 
     */
    bool status;
};

#endif /* LINK_H */

