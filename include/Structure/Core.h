/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Core.h
 * Author: paulofilho
 *
 * Created on 4 de fevereiro de 2019, 15:17
 */

#ifndef CORE_H
#define CORE_H

#include <vector>
#include <cstddef>
#include <iostream>
#include <cassert>

#include "Link.h"

typedef unsigned int CoreId;
typedef unsigned int NumSlots;

/**
 * @brief Core Class represents a core inside a Fiber. 
 */
class Core {
    
    friend std::ostream& operator<<(std::ostream& ostream,
    Core* core);
    
public:
    /**
     * @brief Standard constructor for a Core object.
     * @param cId integer that represents the index of 
     * the core.
     * @param nSlots represents the total numbr of slots
     * in a core.
     */
    Core(CoreId cId, NumSlots nSlots);
    
    virtual ~Core();
    
    void Initialize();
    /**
     * @brief Get Id of the core.
     * @return Id of the core.
     */
     CoreId GetCoreId();
    /**
     * @brief Get occupation of the slot in the core.
     * @param sPosition represents the position of the slot
     * in the core. 
     * @return Occupation of the slot.
     */
    bool IsSlotOccupied(unsigned int sPosition);
    
    bool IsSlotFree(unsigned int sPosition);
    /**
     * @brief Occupy the slot position.
     * @param Represents the position of the slot
     * in the core. 
     */
    void OccupySlot(unsigned int sPosition);
     /**
     * @brief Release the slot position.
     * @param Represents the position of the slot
     * in the core. 
     */
    void ReleaseSlot(unsigned int sPosition);
private:
    /**
     * @brief Index of the core.
     */
    CoreId coreId;
    /**
     * @brief Vector of occupation of the core.
     */
    bool* vDisp;
     
    std::vector<SlotStatus> slotsStatus;

};

#endif /* CORE_H */

