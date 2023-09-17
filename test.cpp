/*
 * Copyright 2022 University of Michigan EECS183
 *
 * test.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Final Project - Elevators
 */
 
////////////////////////////////////////////////
// You will submit test.cpp to the autograder //
// FOR LAB 8, but NOT the final project Core  //
////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include "AI.h"
#include "Building.h"
#include "BuildingState.h"
#include "Elevator.h"
#include "Floor.h"
#include "Game.h"
#include "Move.h"
#include "Person.h"
#include "SatisfactionIndex.h"
#include "Utility.h"

using namespace std;

void test_game();



void start_tests() {
    test_game();
    
    
    
    return;
}



void test_game()  {
    cout << "Testing isValidPickupList" << endl;

    Game validOrNot;
    int pickupFloorNum = 3;
    string invalidCopy = "1134";
    string invalidNegative = "-1235";
   
    
    cout << "Expected: 0, actual: " << validOrNot.isValidPickupList(invalidCopy, pickupFloorNum) << endl;
    cout << "Expected: 0, actual: " << validOrNot.isValidPickupList(invalidNegative, pickupFloorNum) << endl;
   


}
