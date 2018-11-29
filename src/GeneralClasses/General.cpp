/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   General.cpp
 * Author: BrunoVinicius
 * 
 * Created on November 29, 2018, 1:41 AM
 */

#include "../../include/GeneralClasses/General.h"

double General::LinearTodB(const double linValue) {
    return 10 * std::log10(linValue);
}

double General::LinearWTodBm(const double powerWatts) {
    return 10 * std::log10(powerWatts*1000);
}

double General::dBToLinear(const double dBValue) {
    return std::pow(10.0, dBValue/10.0);
}
