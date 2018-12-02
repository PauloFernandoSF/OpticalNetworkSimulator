/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Signal.h
 * Author: BrunoVinicius
 *
 * Created on November 29, 2018, 9:11 PM
 */

#ifndef SIGNAL_H
#define SIGNAL_H

#include <cassert>

class Signal {

public:
    
    Signal();
    
    virtual ~Signal();
    
    double GetSignalPower() const;

    void SetSignalPower(double signalPower);
    
    double GetAsePower() const;

    void SetAsePower(double asePower);

    double GetNonLinearPower() const;

    void SetNonLinearPower(double nonLinearPower);

    double GetOsnr();
    
    double GetOSNR();
    //fn-noise factor; gain-gain of the EDFA. pASE retorna a potência ASE
    static double pASE(double fn, double gain);
    //nASE retorna a densidade espectral de potência
    static double nASE(double fn, double gain); 
    
    static const double v;      //central frequency
    static const double h;      //Planck constant
    static const double Fn;     //Amplifier Noise Figure;
    static const double fn;     //Amplifier Noise Factor;
    static const double Bo;     //Reference Bandwidth;
    static const double Alpha;  //Fiber attenuation coefficient
    static const double alpha;  //Fiber attenuation coefficient
    static const double pIn;    //Signal Input Power in Watts
    static const double Pin;    //Signal Input Power in dBm;
    static const double pRef;   //Reference Power at the fiber input in W;
    static const double Pref;   //Reference Power at the fiber input in dBm;
    static const double OSNRin; //OSNR of the input signal in dB
    static const double osnrIn; //OSNR of the input signal in linear
    static const double Lwss;   //WSS loss in dB
    static const double lWSS;   //WSS loss in linear

private:
    
    double signalPower;
    
    double asePower;
    
    double nonLinearPower;
};

#endif /* SIGNAL_H */

