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

typedef int CoreId;
typedef int NumSlots;

/**
 * @brief Core Class represents a core inside a Fiber. 
 */
class Core {
public:
     /**
     * @brief Standard constructor for a Core object.
     * @param cId integer that represents the index of 
     * the core.
     * @param nSlots represents the total numbr of slots
     * in a core.
     */
     Core(CoreId cId,NumSlots nSlots);
     /**
     * @brief Get Id of the core.
     * @return Id of the core.
     */
     CoreId getCoreId();
     /**
     * @brief Get occupation of the slot in the core.
     * @param sPosition represents the position of the slot
     * in the core. 
     * @return Occupation of the slot.
     */
     bool getSlotOccupation(int sPosition);
     /**
     * @brief Occupy the slot position.
     * @param Represents the position of the slot
     * in the core. 
     */
     void occupySlot(int);
     /**
     * @brief Release the slot position.
     * @param Represents the position of the slot
     * in the core. 
     */
     void releaseSlot(int);
private:
     /**
     * @brief Index of the core.
     */
     CoreId coreId;
     /**
     * @brief Vector of occupation of the core.
     */
     bool* vDisp;

};

#endif /* CORE_H */

