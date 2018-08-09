/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: bruno
 *
 * Created on August 2, 2018, 3:35 PM
 */

#include <cstdlib>
#include <iostream>
#include <memory>

#include "include/Kernel.h"


/**
 * @brief main function
 * @param argc Number of arguments
 * @param argv Arguments
 * @return 
 */
int main(int argc, char** argv) {
    
    std::cout << "\t----OPTICAL NETWORKS SIMULATOR----"  << std::endl;
    
    int auxInt = strtol(argv[1], nullptr, 10);

    std::shared_ptr<Kernel> kernel = std::make_shared<Kernel>(auxInt);
    kernel->Run();
    kernel.~__shared_ptr();

    return 0;
}

