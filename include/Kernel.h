/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Kernel.h
 * Author: bruno
 *
 * Created on August 2, 2018, 3:42 PM
 */

#ifndef KERNEL_H
#define KERNEL_H

#include <vector>
#include <memory>

class SimulationType;

class Kernel {
public:
    Kernel(int numSimulations);
    Kernel(const Kernel& orig);
    virtual ~Kernel();
    
    /**
     * @brief Runs the kernel
     */
    void Run();    
    /**
     * @brief 
     */
    void Pre_Simulation();    
    /**
     * @brief
     */
    void Simulation();    
    /**
     * @brief
     */
    void Pos_Simulation();

private:
    /**
     * @brief Total number of simulations in this kernel
     */
    unsigned int numberSimulations;
    /**
     * @brief Vector with all pointers to SimulationType objects
     */
    std::vector<std::shared_ptr<SimulationType>> simulations;
};

#endif /* KERNEL_H */

