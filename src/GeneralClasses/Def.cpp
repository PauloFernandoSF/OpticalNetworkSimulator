/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Def.cpp
 * Author: BrunoVinicius
 * 
 * Created on November 21, 2018, 2:37 PM
 */

#include "../../include/GeneralClasses/Def.h"

#include <limits>

int Def::Min_Int = std::numeric_limits<int>::max();
int Def::Max_Int = std::numeric_limits<int>::lowest();
double Def::Min_Double = std::numeric_limits<double>::max();
double Def::Max_Double = std::numeric_limits<double>::lowest();
