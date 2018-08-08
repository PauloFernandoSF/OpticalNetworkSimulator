/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Node.h
 * Author: bruno
 *
 * Created on August 4, 2018, 1:14 AM
 */

#ifndef NODE_H
#define NODE_H

class Node {
public:
    Node();
    Node(const Node& orig);
    virtual ~Node();
    
    void initialise();

private:
};

#endif /* NODE_H */

