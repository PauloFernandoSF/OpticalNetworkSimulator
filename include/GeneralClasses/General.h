/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   General.h
 * Author: BrunoVinicius
 *
 * Created on November 29, 2018, 1:41 AM
 */

#ifndef GENERAL_H
#define GENERAL_H

#include <cmath>

class General {

public:
    
    static double LinearTodB(const double linValue);
    
    static double LinearWTodBm(const double powerWatts);
    
    static double dBToLinear(const double dBValue);
    
    template <class T>
    static const T& ABS(const T& x);
    
    template <class T>
    static const T& MAX (const T& a, const T& b);
    
    template <class T>
    static const T& MIN (const T& a, const T& b);
    
private:

};

template <class T>
const T& General::ABS(const T& x){
	return (x>0)?x:-x;
}

template <class T>
const T& General::MAX (const T& a, const T& b){
	return (a>b)?a:b;
}

template <class T>
const T& General::MIN (const T& a, const T& b){
	return (a<b)?a:b;
}

#endif /* GENERAL_H */
