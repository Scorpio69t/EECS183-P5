/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Elevator.h
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Final Project - Elevators
 */

#ifndef _ELEVATOR_H_
#define _ELEVATOR_H_

#include "Utility.h"
#include "Person.h"
#include <string>

//////////////////////////////////////////////////
/////// DO NOT MODIFY ANY CODE IN THIS FILE //////
/////////// ANY CONSTANTS/ETC SHOULD /////////////
////////////// BE ADDED IN THE .CPP //////////////
//////////////////////////////////////////////////

class Elevator {
private:
    bool servicing;
    int currentFloor;
    int targetFloor;

public:
    /**
    * Requires: currentTime is valid
    * Modifies: currentFloor, servicing
    * Effects:  Moves the value of current floor by 1 in the direction of the target
    *           floor if the currentTime is divisible by TICKS_PER_ELEVATOR_MOVE and
    *           the elevator is servicing a request.
    *           If the new current floor is the target floor, servicing is set to false
    */
    void tick(int currentTime);

    /**
     * Requires: 0 <= floorNum <= NUM_FLOORS
     * Modifies: targetFloor, servicing
     * Effects:  Sets the targetFloor and marks the Elevator as 
     *           currently servicing
     */
    void serviceRequest(int floorNum);

    /**
     * Requires: nothing
     * Modifies: outs
     * Effects:  Prints the infoString of the elevator
     */
    void print(ostream &outs);

    /**
     * Requires: nothing
     * Modifies: this Elevator object
     * Effects:  Creates an Elevator object with initial values
     */
    Elevator();

    /**
     * Requires: 0 <= floorNum <= NUM_FLOORS
     * Modifies: currentFloor
     * Effects:  Sets the currentFloor
     */
    void setCurrentFloor(int currentFloorIn);

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects:  Returns whether the elevator is servicing
     *
     */
	bool isServicing() const;

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects:  Returns the currentFloor
     */
    int getCurrentFloor() const;

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects:  Returns the targetFloor
     */
    int getTargetFloor() const;
};

#endif
