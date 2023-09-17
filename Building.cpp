/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Building.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */

#include "Building.h"

using namespace std;

void Building::spawnPerson(Person newPerson) {
    //TODO: Implement spawnPerson
    if (newPerson.getCurrentFloor() > newPerson.getTargetFloor()) {
        floors[newPerson.getCurrentFloor()].addPerson(newPerson, -1);
    }
    else if (newPerson.getCurrentFloor() < newPerson.getTargetFloor()) {
        floors[newPerson.getCurrentFloor()].addPerson(newPerson, 1);
    }
    //floors[newPerson.getCurrentFloor()].addPerson(newPerson, )
}
/*
   * Requires: move is a valid move
   * Modifies: The building member variables affected by the move
   * Effects: Applies the move to the building:
   *          * If the move is a Pass Move, nothing happens
   *          * If the move is a Pickup Move, copies the list of people to
   *            pickup into an array, and calls removePeople() on the
   *            appropriate floor
   *          * For both Pickup Moves and Service Moves, the appropriate
   *            elevator should be sent to service the targetFloor of the move
   */
void Building::update(Move move) {
    if (move.isPickupMove()) {
        int pickupCopy[MAX_PEOPLE_PER_FLOOR];
        move.copyListOfPeopleToPickup(pickupCopy);
        floors[elevators[move.getElevatorId()].getCurrentFloor()].removePeople(pickupCopy, move.getNumPeopleToPickup());
    }
    if (!move.isPassMove()) {
        elevators[move.getElevatorId()].serviceRequest(move.getTargetFloor());

    }

}
/*
    * Requires: move is a valid move
    * Modifies: The private member variables of building
    * Effects: Increments time and calls update() on the input move
    *          Then, ticks all of the elevators with the new time
    *          Next, ticks all of the buildingfloors, keeping track of new
    *          exploded people
    *          Returns the total number of people that exploded in this tick
    */

int Building::tick(Move move) {
    //TODO: Implement tick
    time++;
    int temp = 0;
    //temp will store the number of exploded people
    update(move);
    //MAY NOT be able to use num_elevators parameter
    for (int i = 0; i < NUM_ELEVATORS; i++) {
        elevators[i].tick(time);
    }
    for (int f = 0; f < NUM_FLOORS; f++) {
        temp += floors[f].tick(time);
    }
    //returning 0 to prevent compilation error
    return temp;
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Building::Building() {
    time = 0;
}

void Building::setElevator(string elevatorInfo, int elevatorId) {
    int i = 0;
    string currPosString = "";
    string destPosString = "";

    while (elevatorInfo[i] != 's' && elevatorInfo[i] != 'w') {
        currPosString += elevatorInfo[i];
        i++;
    }
    elevators[elevatorId] = Elevator();

    elevators[elevatorId].setCurrentFloor(stoi(currPosString));

    if (elevatorInfo[i] == 's') {
        i++;
        while (i < (int)elevatorInfo.size()) {
            destPosString += elevatorInfo[i];
            i++;
        }
        elevators[elevatorId].serviceRequest(stoi(destPosString));
    }
}

int Building::getTime() const {
    return time;
}

void Building::setTime(int timeIn) {
    time = timeIn;
}

void Building::prettyPrintBuilding(ostream& outs) const {
    //-------
    //| | | | 🔼 1 4 2
    //| | |E| 🔽 o o o
    //-------
    //| | | | 🔼   1
    //| |E| |      o
    //-------
    //| | | |
    //|E| | |
    for (int i = NUM_FLOORS - 1; i >= 0; --i) {
        outs << "   ";
        for (int j = 0; j < 2 * NUM_ELEVATORS + 1; ++j) {

            outs << '-';
        }

        outs << endl << "   ";

        for (int j = 0; j < NUM_ELEVATORS; ++j) {
            char floorIndicatorIcon = ' ';

            if (elevators[j].getCurrentFloor() == i &&
                elevators[j].isServicing()) {

                char floorServiceIndicator = ('0' + elevators[j].getTargetFloor());
                floorIndicatorIcon = floorServiceIndicator;
            }

            outs << "|" << floorIndicatorIcon;
        }
        outs << "|";

        floors[i].prettyPrintFloorLine1(outs);
        outs << i << "  ";
        for (int j = 0; j < NUM_ELEVATORS; ++j) {

            outs << "|" << (elevators[j].getCurrentFloor() == i ? 'E' : ' ');
        }
        outs << "|";

        floors[i].prettyPrintFloorLine2(outs);
    }
    outs << "   ";
    for (int j = 0; j < 2 * NUM_ELEVATORS + 1; ++j) {
        outs << '-';
    }
    outs << endl << "   ";
    for (int j = 0; j < NUM_ELEVATORS; ++j) {
        outs << " " << j;
    }
    outs << endl;
}

Elevator Building::getElevatorById(int elevatorId) const {
    return elevators[elevatorId];
}

Floor Building::getFloorByFloorNum(int floorNum) const {
    return floors[floorNum];
}

BuildingState Building::getBuildingState() const {
    BuildingState buildingState;
    buildingState.turn = time;

    for (int i = 0; i < NUM_FLOORS; ++i) {
        buildingState.floors[i].floorNum = i;
        buildingState.floors[i].hasDownRequest = floors[i].getHasDownRequest();
        buildingState.floors[i].hasUpRequest = floors[i].getHasUpRequest();

        int& np = buildingState.floors[i].numPeople;

        for (int j = 0; j < floors[i].getNumPeople(); ++j) {

            Person p = floors[i].getPersonByIndex(j);
            buildingState.floors[i].people[np++].angerLevel = p.getAngerLevel();
        }
    }

    for (int i = 0; i < NUM_ELEVATORS; ++i) {
        Elevator e = elevators[i];

        buildingState.elevators[i].elevatorId = i;
        buildingState.elevators[i].targetFloor = e.getTargetFloor();
        buildingState.elevators[i].currentFloor = e.getCurrentFloor();
        buildingState.elevators[i].isServicing = e.isServicing();
    }

    return buildingState;
}