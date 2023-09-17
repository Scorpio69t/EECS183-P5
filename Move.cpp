/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Move.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */

#include <cmath>
#include <sstream>
#include <stdio.h>      
#include <stdlib.h>
#include "Move.h"

using namespace std;

Move::Move(string commandString) : Move() {

    // Non-default constructor
    //cin >> commandString;

    /*
    // Sets eId to the second character in "e1f4"
    char eIdChar = commandString[1];
    // Converts elevatorId from char to int using ASCII code
    elevatorId = eIdChar - '0';
    // Sets targetFloor to fourth character in "e1f4"
    char tarFloorChar = commandString[3];
    // Converts targetFloor from char to int using ASCII code
    targetFloor = tarFloorChar - '0';
    */

    /*
    // Sets move as a pass
    if (commandString == "") {
        isPass = true;
        elevatorId = -1;
        targetFloor = -1;
    }
    // Sets move as an elevator pickup
    else if (commandString[2] == 'p') {
        isPickup = true;
        targetFloor = -1;
    }
    // Sets move as a game save
    else if (commandString == "s" || commandString == "S") {
        isSave = true;
        elevatorId = -1;
        targetFloor = -1;
    }
    // Sets move as a game quit
    else if (commandString == "q" || commandString == "Q") {
        isQuit = true;
        elevatorId = -1;
        targetFloor = -1;
    }
    */
    string command = commandString;
    stringstream ss(command);
    char firstLetter;
    char floorOrPickup;

    ss >> firstLetter;
    if (firstLetter == 'q' || firstLetter == 'Q') {
        isQuit = true;
    }
    else if (firstLetter == 's' || firstLetter == 'S') {
        isSave = true;
    }
    else if (firstLetter == 'e' || firstLetter == 'E') {
        ss >> elevatorId;
        ss >> floorOrPickup;
        if (floorOrPickup == 'f' || firstLetter == 'F') {
            ss >> targetFloor;
        }
        else if (floorOrPickup == 'p' || firstLetter == 'P') {
            isPickup = true;
        }
    }
    else {
        isPass = true;
    }
}

bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {

    if (isPassMove() == true || isQuitMove() == true || isSaveMove() == true) {
        return true;
    }
    //move has an invalid elevator id
    else if ((elevatorId < 0) || elevatorId > NUM_ELEVATORS - 1) {
        return false;
    }
    //move attempts to change an elevator that is already in service
    else if (elevators[elevatorId].isServicing() == true) {
        return false;
    }
    //move has an invalid floor number
    else if ((targetFloor < 0 || targetFloor > NUM_FLOORS - 1) && !isPickupMove()) {
        return false;
    }
    //move tries to set the target floor equal to the current floor
    else if ((targetFloor == elevators[elevatorId].getCurrentFloor()) && !isPickupMove()) {
        return false;
    }
    else {
        return true;
    }

    // For pass, game quit, & game save moves
    /*if ((isPass == true) || (isQuit == true) || (isSave == true)) {
        return true;
    }
    // For pickup moves & servicing moves
    //the commented code below is Kayla's code mine is right below that
    else if ((elevatorId >= 0) && (elevatorId < NUM_ELEVATORS) &&
        (elevators[elevatorId].isServicing() == false)) {
        // For servicing moves
        if ((targetFloor >= 0) && (targetFloor < NUM_FLOORS) &&
            (targetFloor != elevators[elevatorId].getCurrentFloor())) {
            return true;
        }
        else {
            return false;
        }
        return true;
    }
    // Returns all other moves as invalid
    else {
        return false;
    }
*/

/*
if ((isPass == true) || (isQuit == true) || (isSave == true)) {
    return true;
}
else if (elevatorId >= 0 && elevatorId < NUM_ELEVATORS) {
    if (elevators[elevatorId].isServicing() == false) {
        return true;
    }
    else {
        return false;
    }
}
else if (targetFloor >= 0 && targetFloor < NUM_FLOORS && targetFloor != elevators[elevatorId].getCurrentFloor()) {
return true;
}
else {
    return false;
}
*/

/*
if ((isPass) || (isQuit) || (isSave)) {
    return true;
}
// For pickup moves
//for (int i = 0; i < NUM_ELEVATORS; i++) {
else if ((elevatorId >= 0) && (elevatorId < NUM_ELEVATORS) &&
    (!elevators[elevatorId].isServicing())) {
    return true;
}
// For servicing moves
//for (int j = 0; j < NUM_ELEVATORS; j++) {
else if ((targetFloor >= 0) && (targetFloor < NUM_FLOORS) &&
    (elevatorId >= 0) && (elevatorId < NUM_ELEVATORS) &&
    (targetFloor != elevators[elevatorId].getCurrentFloor()) &&
    (!elevators[elevatorId].isServicing()) && (isPickupMove() == false)) {
    return true;
}
// Returns all other moves as invalid
else {
    return false;
}
*/

/*
if ((isPass == true) || (isQuit == true) || (isSave == true)) {
    return true;
}
// For pickup moves & servicing moves
/*else if ((elevatorId >= 0) && (elevatorId < NUM_ELEVATORS && elevators[elevatorId].isServicing() == false)) {
        return true;
    }
    // For servicing moves
else if ((targetFloor >= 0) && (targetFloor < NUM_FLOORS) &&
        (targetFloor != elevators[elevatorId].getCurrentFloor()) && isPickupMove() == false) {
        return true;
    }
// Returns all other moves as invalid
else {
    return false;
}
*/
/*else if (isPickup && !elevators[elevatorId].isServicing() &&
      elevatorId < NUM_ELEVATORS && 0 <= elevatorId){
      return true}
      else if (!isQuit && !isPass && !isPickup &&
    !elevators[elevatorId].isServicing() &&
    elevatorId < NUM_ELEVATORS && 0 <= elevatorId &&
    targetFloor != elevators[elevatorId].getCurrentFloor() &&
    targetFloor < NUM_FLOORS && 0 <= targetFloor) {
    return true}
    }
    return false
    }
    */
}


void Move::setPeopleToPickup(const string& pickupList, const int currentFloor, const Floor& pickupFloor) {

    //TODO: Implement setPeopleToPickup
   /* numPeopleToPickup = 0;
    totalSatisfaction = 0;
    Floor floor;
    int maxDistanceIndex = 0;
    // Takes in a string of indices
    stringstream input(pickupList);
    //other version not using stringstream could just use pickupList.get(i) - '0'
    // Reads character from pickupList into peopleToPickup int array
    for (int i = 0; i < MAX_PEOPLE_PER_FLOOR; i++) {
        input >> peopleToPickup[i];
        numPeopleToPickup++;

        int tempAngerLevel = P.getPersonByIndex(peopleToPickup[i]).getAngerLevel();
        totalSatisfaction += MAX_ANGER - tempAngerLevel;
        //need function from floor that allows you to access a particular person at an index in the people array
        // getPersonByIndex
        //then get anger level from that person function from person class
        //getAngerLevel()
        // need to find satisfaction from this person and add to to totalSatisfaction peopleToPickup[i]
    }
    for (int f = 0; f < numPeopleToPickup - 1; f++) {
        int tempTargetFloor = P.getPersonByIndex(peopleToPickup[f]).getTargetFloor();
        int tempTargetFloor2 = P.getPersonByIndex(peopleToPickup[f + 1]).getTargetFloor();
        int distance = abs(currentFloor - tempTargetFloor);
        int distance2 = abs(currentFloor - tempTargetFloor2);
        if (distance2 >= distance) {
            distance = distance2;
            maxDistanceIndex = f + 1;
        }
        else {
            maxDistanceIndex = f;
        }
    }

    // if distance > distance 2 distance = distance 2
    // Sets targetFloor to most extreme floor
    // of those being picked up (up or down)

   targetFloor = P.getPersonByIndex(peopleToPickup[maxDistanceIndex]).getTargetFloor();
   */
    numPeopleToPickup = 0;
    totalSatisfaction = 0;

    int maxDistanceIndex = 0;
    int tempAngerLevel = 0;
    int maxDistance = 0;

    for (int i = 0; i < pickupList.size(); i++) {
        peopleToPickup[i] = pickupList.at(i) - '0';
        numPeopleToPickup++;
    }

    for (int j = 0; j < numPeopleToPickup; j++) {
        tempAngerLevel = pickupFloor.getPersonByIndex(peopleToPickup[j]).getAngerLevel();
        totalSatisfaction += MAX_ANGER - tempAngerLevel;
    }

    for (int f = 0; f < numPeopleToPickup; f++) {
        int distance = pickupFloor.getPersonByIndex(peopleToPickup[f]).getTargetFloor() - pickupFloor.getPersonByIndex(peopleToPickup[f]).getCurrentFloor();
        if (abs(distance) > maxDistance) {
            maxDistance = abs(distance);
            targetFloor = pickupFloor.getPersonByIndex(peopleToPickup[f]).getTargetFloor();
        }
    }
    /* for (int f = 0; f < numPeopleToPickup - 1; f++) {
         int tempTargetFloor = pickupFloor.getPersonByIndex(peopleToPickup[f]).getTargetFloor();
         int tempTargetFloor2 = pickupFloor.getPersonByIndex(peopleToPickup[f + 1]).getTargetFloor();
         int distance = abs(currentFloor - tempTargetFloor);
         int distance2 = abs(currentFloor - tempTargetFloor2);
         if (distance2 >= distance) {
             distance = distance2;
             maxDistanceIndex = f + 1;
         }
         else {
             maxDistanceIndex = f;
         }

     }
     targetFloor = pickupFloor.getPersonByIndex(peopleToPickup[maxDistanceIndex]).getTargetFloor();
     */
     /*
     // Takes in a string of indices
     stringstream input(pickupList);
     // Reads character from pickupList into peopleToPickup int array
     for (int i = 0; i < MAX_PEOPLE_PER_FLOOR; i++) {
         input >> peopleToPickup[i];
         numPeopleToPickup++;
         int tempAngerLevel = floor.getPersonByIndex(peopleToPickup[i]).getAngerLevel();
         totalSatisfaction += MAX_ANGER - tempAngerLevel;
     }
     for (int f = 0; f < numPeopleToPickup - 1; f++) {
         int tempTargetFloor = floor.getPersonByIndex(peopleToPickup[f]).getTargetFloor();
         int tempTargetFloor2 = floor.getPersonByIndex(peopleToPickup[f + 1]).getTargetFloor();
         int distance = abs(currentFloor - tempTargetFloor);
         int distance2 = abs(currentFloor - tempTargetFloor2);
         if (distance2 >= distance) {
             distance = distance2;
             maxDistanceIndex = f + 1;
         }
         else {
             maxDistanceIndex = f;
         }
     }
     targetFloor = floor.getPersonByIndex(peopleToPickup[maxDistanceIndex]).getTargetFloor();
     */
    return;
}







//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Move::Move() {
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;
}

bool Move::isPickupMove() const {
    return isPickup;
}

bool Move::isPassMove() const {
    return isPass;
}

bool Move::isSaveMove() const {
    return isSave;
}

bool Move::isQuitMove() const {
    return isQuit;
}

int Move::getElevatorId() const {
    return elevatorId;
}

int Move::getTargetFloor() const {
    return targetFloor;
}

int Move::getNumPeopleToPickup() const {
    return numPeopleToPickup;
}

int Move::getTotalSatisfaction() const {
    return totalSatisfaction;
}

void Move::setTargetFloor(int inTargetFloor) {
    targetFloor = inTargetFloor;
}

void Move::copyListOfPeopleToPickup(int newList[MAX_PEOPLE_PER_FLOOR]) const {
    for (int i = 0; i < numPeopleToPickup; ++i) {
        newList[i] = peopleToPickup[i];
    }
}