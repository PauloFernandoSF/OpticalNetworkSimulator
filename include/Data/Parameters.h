/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Parameters.h
 * Author: bruno
 *
 * Created on August 8, 2018, 6:25 PM
 */

#ifndef PARAMETERS_H
#define PARAMETERS_H

class SimulationType;

#include <fstream>
#include <vector>
#include <assert.h>

class Parameters {
public:
    Parameters(SimulationType* simulType);
    Parameters(const Parameters& orig);
    virtual ~Parameters();
    
    void LoadFile();
    
    /**
     * @brief 
     * @return 
     */
    std::vector<double> GetLoadPoint() const;
    
    double GetLoadPoint(unsigned int index) const;

    void SetLoadPoint(std::vector<double> loadPoint);
    
    void SetLoadPoint(double loadPoint, unsigned int index);

    double GetMinLoadPoint() const;

    void SetMinLoadPoint(double minLoadPoint);
    
    double GetMaxLoadPoint() const;

    void SetMaxLoadPoint(double maxLoadPoint);
    
    int GetNumberLoadPoints() const;

    void SetNumberLoadPoints(double numberLoadPoints);
    
    double GetNumberReqMax() const;

    void SetNumberReqMax(double numberReqMax);  

    double GetMu() const;

    void SetMu(double mu);
    
    void SetLoadPasso();
    
    void SetLoadPointUniform();

private:
    /**
     * @brief A pointer to the simulation this object belong
     */
    SimulationType* simulType;
    /**
     * @brief
     */
    std::vector<double> loadPoint;
    /**
     * @brief
     */
    double minLoadPoint;
    /**
     * @brief
     */
    double maxLoadPoint;
    /**
     * @brief
     */
    double loadPasso;
    /**
     * @brief
     */
    int numberLoadPoints;
    /**
     * @brief
     */
    double numberReqMax;
    /**
     * @brief
     */
    double mu;
};

#endif /* PARAMETERS_H */

