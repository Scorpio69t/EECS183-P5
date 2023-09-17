/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Person.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */

#include "Person.h"
#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;
/*
     * Requires: inputString is correctly formatted
     * Modifies: turn, currentFloor, targetFloor, angerLevel
     * Effects:  Parses input_string to set member variables
     *           An example of input_string is "7f4t8a3".
    */


    //may need to read inputString before doing this through ifstream or through cin
Person::Person(string inputString) : Person() {
    //TODO: Implement non-default constructor spec suggests using the stringstream system
   /*
    char turnChar = inputString.at(0);
    // Converts turn from char to int using ASCII code
    turn = turnChar - '0';

    //inputString.at(1) = b;
    //inputString.at(2) = c;
    char currFloorChar = inputString.at(2);
    // Converts currentFloor from char to int using ASCII code
    currentFloor = currFloorChar - '0';

    //inputString.at(3) = d;
    //inputString.at(4) = e;
    char targetFloorChar = inputString.at(4);
    // Converts targetFloor from char to int using ASCII code
    targetFloor = targetFloorChar - '0';

    //inputString.at(5) = f;
    //inputString.at(6) = g;
    char angerLevelChar = inputString.at(6);
    // Converts angerLevel from char to int using ASCII code
    angerLevel = angerLevelChar - '0';
    */
    stringstream ss(inputString);

    ss >> turn;
    char a;
    ss >> a;
    ss >> currentFloor;
    char b;
    ss >> b;
    ss >> targetFloor;
    char c;
    ss >> c;
    ss >> angerLevel;


    //This is wrong because it is trying to set a string to an integer so it is taking the character ASCII value 
    //use stoi() function which works on members of a string
}

bool Person::tick(int currentTime) {

    if (currentTime % TICKS_PER_ANGER_INCREASE == 0) {
        angerLevel++;
    }
    if (angerLevel >= MAX_ANGER) {
        return true;
    }
    else if (angerLevel < MAX_ANGER) {
        return false;
    }
}
/**
     * Requires: nothing
     * Modifies: outs
     * Effects:  Prints the infoString of the person NOT including the turn
     *
     * Example:  Person p("7f4t8a3");
     *           cout << "\nThe person you just entered is: ";
     *           p.print(cout);
     *
     *           This will print "f4t8a3"
     */

     //a little unsure about what the rme is asking of me
void Person::print(ostream& outs) {
    //TODO: Implement print
    outs << "f" << currentFloor << "t" << targetFloor << "a" << angerLevel;
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Person::Person() {
    turn = 0;
    currentFloor = 0;
    targetFloor = 0;
    angerLevel = 0;
}

int Person::getTurn() const {
    return turn;
}

int Person::getCurrentFloor() const {
    return currentFloor;
}

int Person::getTargetFloor() const {
    return targetFloor;
}

int Person::getAngerLevel() const {
    return angerLevel;
}

ostream& operator<< (ostream& outs, Person p)
{
    p.print(outs);
    return outs;
}