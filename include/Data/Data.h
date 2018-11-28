/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Data.h
 * Author: bruno
 *
 * Created on August 8, 2018, 6:25 PM
 */

#ifndef DATA_H
#define DATA_H

class SimulationType;
class Call;

#include <vector>
#include <ostream>

/**
 * @brief The Data class is responsible for storage the simulation
 * data.
 */
class Data {
    
    friend std::ostream& operator<<(std::ostream& ostream, 
    const Data* data);

public:
    /**
     * @brief Standard constructor for a Data object.
     * @param simulType SimulationType object that owns 
     * this data.
     */
    Data(SimulationType* simulType);
    /**
     * @brief Copy constructor for a Data object.
     * @param orig original Data object.
     */
    Data(const Data& orig);
    /**
     * @brief Virtual destructor of a Data object.
     */
    virtual ~Data();
    
    void Initialize();
    
    void StorageCall(Call* call);
    
    std::vector<double> GetNumberReq() const;
    
    double GetNumberReqLoad(unsigned int index) const;

    void SetNumberReq(std::vector<double> numberReq);
    
    std::vector<double> GetNumberBlocReq() const;
    
    double GetNumberBlocReqLoad(unsigned int index) const;

    void SetNumberBlocReq(std::vector<double> numberBlocReq);
    
    std::vector<double> GetNumberAccReq() const;
    
    double GetNumberAccReqLoad(unsigned int index) const;

    void SetNumberAccReq(std::vector<double> numberAccReq);
    
    std::vector<double> GetNumberBlocSlots() const;
    
    double GetNumberBlocSlotsLoad(unsigned int index) const;

    void SetNumberBlocSlots(std::vector<double> numberBlocSlots);
    
    std::vector<double> GetNumberAccSlots() const;
    
    double GetNumberAccSlotsLoad(unsigned int index) const;

    void SetNumberAccSlots(std::vector<double> numberAccSlots);
    
    std::vector<double> GetNumHopsPerRoute() const;
    
    double GetNumHopsPerRouteLoad(unsigned int index) const;

    void SetNumHopsPerRoute(std::vector<double> meanHopsPerRoute);

    std::vector<double> GetNetOccupancy() const;
    
    double GetNetOccupancyLoad(unsigned int index) const;

    void SetNetOccupancy(std::vector<double> netOccupancy);
    
    unsigned int GetActualIndex() const;

    void SetActualIndex(unsigned int actualIndex);

    
private:
    /**
     * @brief A pointer to the simulation this object belong
     */
    SimulationType* simulType;
    /**
     * @brief Actual number of requisitions simulated, per load.
     */
    std::vector<double> numberReq;
    /**
     * @brief Actual number of blocked requisitions simulated,
     * per load.
     */
    std::vector<double> numberBlocReq;
    /**
     * @brief Actual number of accepted requisitions simulated,
     * per load.
     */
    std::vector<double> numberAccReq;
    /**
     * @brief Actual number of blocked slots simulated,
     * per load.
     */
    std::vector<double> numberBlocSlots;
    /**
     * @brief Actual number of accepted slots simulated,
     * per load.
     */
    std::vector<double> numberAccSlots;
    /**
     * @brief Mean of hops per route, per load.
     */
    std::vector<double> numHopsPerRoute;
    /**
     * @brief Network occupancy, per load.
     * It is Calculated multiplying the number of slots
     * occupied by the number of route hops.
     */
    std::vector<double> netOccupancy;
    
    unsigned int actualIndex;
};

#endif /* DATA_H */

