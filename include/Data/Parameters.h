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
#include <iostream>
#include <vector>
#include <assert.h>

/**
 * @brief The Parameters class is responsible for storage 
 * the simulation parameters.
 */
class Parameters {
    /**
     * @brief 
    */
    friend std::ostream& operator<<(std::ostream& ostream, 
    const Parameters* parameters);
    
public:
    /**
     * @brief Standard constructor for a Parameters object.
     * @param simulType SimulationType object that owns 
     * this Parameters.
     */
    Parameters(SimulationType* simulType);
    /**
     * @brief Copy constructor for a Parameters object.
     * @param orig original Parameters object.
     */
    Parameters(const Parameters& orig);
    /**
     * @brief Virtual destructor of a Parameters object.
     */
    virtual ~Parameters();
    
    /**
     * @brief Loads the parameters present in an .txt file.
     */
    void LoadFile();
    
    /**
     * @brief Returns the vector with all
     * load points of the simulation.
     * @return vector of double with all load points.
     */
    std::vector<double> GetLoadPoint() const;
    /**
     * @brief Return a specified load point.
     * @param index vector position.
     * @return Load point.
     */
    double GetLoadPoint(unsigned int index) const;
    /**
     * @brief Sets the vector with all load points.
     * @param loadPoint vector with all load points.
     */
    void SetLoadPoint(std::vector<double> loadPoint);
    /**
     * @brief Sets a specified load point.
     * @param loadPoint load point value.
     * @param index index of the load points vector.
     */
    void SetLoadPoint(double loadPoint, unsigned int index);
    /**
     * @brief Returns the minimum load point.
     * @return Minimum load point.
     */
    double GetMinLoadPoint() const;
    /**
     * @brief Sets the minimum load point.
     * @param minLoadPoint minimum load point value.
     */
    void SetMinLoadPoint(double minLoadPoint);
    /**
     * @brief Returns the maximum load point.
     * @return Maximum load point.
     */
    double GetMaxLoadPoint() const;
    /**
     * @brief Sets the maximum load point.
     * @param maxLoadPoint Maximum load point value.
     */
    void SetMaxLoadPoint(double maxLoadPoint);
    /**
     * @brief Returns the number of load points.
     * @return number of load points.
     */
    int GetNumberLoadPoints() const;
    /**
     * @brief Sets the number of load points.
     * @param numberLoadPoints number of load points.
     */
    void SetNumberLoadPoints(double numberLoadPoints);
    /**
     * @brief Returns the maximum number of requisitions.
     * @return Maximum number of requisitions.
     */
    double GetNumberReqMax() const;
    /**
     * @brief Sets the maximum number of requisitions.
     * @param numberReqMax maximum number of requisitions.
     */
    void SetNumberReqMax(double numberReqMax);  
    /**
     * @brief Returns the connection deactivation time.
     * @return Connection deactivation time.
     */
    double GetMu() const;
    /**
     * @brief Sets the connection deactivation time.
     * @param mu Connection deactivation time.
     */
    void SetMu(double mu);
    /**
     * @brief Get the number of maximum blocked requisitions.
     * @return Number of maximum blocked requisitions.
     */
    int GetNumberBloqMax() const;
    /**
     * @brief Get the number of maximum blocked requisitions.
     * @param numberBloqMax number of maximum blocked requisitions.
     */
    void SetNumberBloqMax(int numberBloqMax);


private:
    /**
     * @brief A pointer to the simulation this object belongs.
     */
    SimulationType* simulType;
    /**
     * @brief Vector that contains the load points
     * of the simulation.
     */
    std::vector<double> loadPoint;
    /**
     * @brief Minimum load point.
     */
    double minLoadPoint;
    /**
     * @brief Maximum load point.
     */
    double maxLoadPoint;
    /**
     * @brief Load step.
     */
    double loadPasso;
    /**
     * @brief Total number of load points.
     */
    int numberLoadPoints;
    /**
     * @brief Total number of requisitions.
     */
    double numberReqMax;
    /**
     * @brief Deactivation connection time.
     */
    double mu;
    /**
     * @brief Number of maximum blocked requisitions.
     */
    int numberBloqMax;
    
    /**
     * @brief Calculate the load step.
     */
    void SetLoadPasso();
    /**
     * @brief Distribute the load points uniformed.
     */
    void SetLoadPointUniform();
};

#endif /* PARAMETERS_H */

