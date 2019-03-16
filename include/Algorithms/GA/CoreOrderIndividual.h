/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CoreOrderIndividual.h
 * Author: paulofilho
 *
 * Created on 26 de fevereiro de 2019, 22:58
 */

#ifndef COREORDERINDIVIDUAL_H
#define COREORDERINDIVIDUAL_H

#include <iostream>;
class GACoreOrder;

class CoreOrderIndividual {
public:
    
    friend std::ostream& operator<<(std::ostream& ostream, 
    const CoreOrderIndividual* ind);
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    CoreOrderIndividual();
    CoreOrderIndividual(const CoreOrderIndividual& orig);
    virtual ~CoreOrderIndividual();
private:
    GACoreOrder* ga;

};

#endif /* COREORDERINDIVIDUAL_H */

