/*
 * Copyright 2022 University of Michigan EECS183
 *
 * AI.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <Kayla Bruner, Wilson Gipson, Andrew Livingston, Mish Jude>
 * <kaylaeb, wgipson, alivin, mishmish>
 *
 * Final Project - Elevators
 */

#include "AI.h"
#include <cassert>

 // This file is used only in the Reach, not the Core.
 // You do not need to make any changes to this file for the Core

string getAIMoveString(const BuildingState& buildingState) {
	string servicingMove = "";
	int floorMaxPeople = 0;
	int indexFloorMaxPeople = 0;
	int indexFloorSecondMax = 0;
	int arr[2][10] = {};
	int sortedAvgAngerArr[10] = {};
	string passMove = "";
	string pickupMove = "";
	bool servFirstPriority = false;
	int firstPriorityEl = 4;
	bool servSecondPriority = false;
	int firstPriorityFloor = 11;
	int secondPriorityFloor = 11;
	int secondPriorityEl = 4;
	int thirdPriorityEl = 4;
	int thirdPriorityFloor = 11;
	int arrAvg[10] = {};


	

	for (int y = 0; y < NUM_FLOORS; y++) {
		int total = 0;
		for (int x = 0; x < buildingState.floors[y].numPeople; x++) {
			total += buildingState.floors[y].people[x].angerLevel;
			
			arrAvg[y] = total;

		}
	}
	int max = arrAvg[0];
	int MaxIndex2 = 0;
	for (int i = 0; i < 10; i++) {
		int targetFloorElevator0 = buildingState.elevators[0].targetFloor;
		int targetFloorElevator1 = buildingState.elevators[1].targetFloor;
		int targetFloorElevator2 = buildingState.elevators[2].targetFloor;
		if ((targetFloorElevator0 != i && targetFloorElevator1 != i && targetFloorElevator2 != i)) {
			if (arrAvg[i] > max) {
				max = arrAvg[i];
				MaxIndex2 = i;
			}
		}
	}

	int floorIndexOfAngriestFloor = 0;
	for (int f = 0; f < 20; f++) {
		for (int i = 0; i < NUM_FLOORS - 1; i++) {
			int targetFloorElevator0 = buildingState.elevators[0].targetFloor;
			int targetFloorElevator1 = buildingState.elevators[1].targetFloor;
			int targetFloorElevator2 = buildingState.elevators[2].targetFloor;
			if (targetFloorElevator0 != i && targetFloorElevator1 != i && targetFloorElevator2 != i) {

				if (arrAvg[i] > arrAvg[i + 1]) {
					floorIndexOfAngriestFloor = i;
				}
				else {
					floorIndexOfAngriestFloor = i + 1;
				}
			}
		}
	}
	for (int y = 0; y < NUM_FLOORS; y++) {
		int angriestPerson = 0;
		
		for (int x = 0; x < buildingState.floors[y].numPeople; x++) {
			int targetFloorElevator0 = buildingState.elevators[0].targetFloor;
			int targetFloorElevator1 = buildingState.elevators[1].targetFloor;
			int targetFloorElevator2 = buildingState.elevators[2].targetFloor;
			if (targetFloorElevator0 != y && targetFloorElevator1 != y && targetFloorElevator2 != y) {
				if (angriestPerson < buildingState.floors[y].people[x].angerLevel) {
					angriestPerson = buildingState.floors[y].people[x].angerLevel;

				}

				arr[1][y] = angriestPerson;
				arr[0][y] = y;
			}
		}
		
	}
	int maxAngriestPerson = 0;
	for (int x = 0; x < NUM_FLOORS - 1; x++) {
		for (int i = 0; i < 20; i++) {
			if (arr[1][x] > arr[1][x + 1]) {
			}
			else {
				for (int y = x; y < NUM_FLOORS - 1; y++) {
					int temp = arr[0][y];
					int temp2 = arr[1][y];
					arr[0][y] = arr[0][y + 1];
					arr[0][y + 1] = temp;
					arr[1][y] = arr[1][y + 1];
					arr[1][y + 1] = temp2;
				}

			}
		}
	}
	
	//create an array that stores the number of people per floor
	int arrNumPeople[10] = {};
	for (int j = 0; j < NUM_FLOORS; j++) {
		int totalPeople = 0;
		totalPeople += buildingState.floors[j].numPeople;
		arrNumPeople[j] = totalPeople;
	}
	//finding the floor with the max number of people on it
	for (int k = 0; k < NUM_FLOORS; k++) {
		int maxPeople = 0;
		if (arrNumPeople[k] > maxPeople) {
			maxPeople = arrNumPeople[k];
			indexFloorMaxPeople = k;
		} 
	}

	for (int i = 0; i < sizeof(arrNumPeople); i++) {
		if (arrNumPeople[i] > indexFloorSecondMax && arrNumPeople[i] < indexFloorMaxPeople) {
			indexFloorSecondMax = arrNumPeople[i];
		}
	}
	


	//check to see if the sum anger level is zero, helps pass peaceful day tests
	int peopleAnger = 0;
	for (int q = 0; q < NUM_FLOORS; q++) {
		for (int w = 0; w < buildingState.floors[q].numPeople; w++) {
			peopleAnger += buildingState.floors[q].people[w].angerLevel;
		}

	}


	//bool inUse = false;
	int numElServicing = 0;
	for (int i = 0; i < NUM_ELEVATORS; i++) {
		if (buildingState.elevators[i].isServicing) {
			numElServicing++;
		}
	}

	int totalPeople = 0;
	for (int fl = 0; fl < NUM_FLOORS; fl++) {
		totalPeople += buildingState.floors[fl].numPeople;
	}
	if (numElServicing == 3 || totalPeople == 0) {
		return passMove;
	}

	int count = 0;

	

	for (int i = 0; i < NUM_ELEVATORS; i++) {
		//elevator is currently servicing a move

		//set a count variable to remember which index to use for the move string if multiple elevators are not servicing

		//elevator is NOT servicing a move
		if (!buildingState.elevators[i].isServicing) {
			string pickupEl = to_string(i);
			if ((buildingState.elevators[i].currentFloor == MaxIndex2 && buildingState.floors[MaxIndex2].numPeople != 0) || (buildingState.elevators[i].currentFloor == indexFloorMaxPeople)) {
				pickupMove = 'e' + pickupEl + 'p';
				return pickupMove;
			}
			//send to floor with second largest number of people
			for (int i = 0; i < NUM_ELEVATORS - 1; i++) {
				if (!buildingState.elevators[i].isServicing && buildingState.elevators[i].targetFloor == buildingState.elevators[i + 1].targetFloor && buildingState.elevators[i].targetFloor != buildingState.elevators[i].currentFloor) {
					string el = to_string(i);
					string targetFloor = to_string(indexFloorSecondMax);
					servicingMove = 'e' + el + 'f' + targetFloor;
					return servicingMove;
				}
			}

			if (peopleAnger == 0) {
				string el = to_string(i);
				string maxpplFloor = to_string(indexFloorMaxPeople);
				servicingMove = 'e' + el + 'f' + maxpplFloor;
				return servicingMove;

				
			}
			else {

				pickupMove = 'e' + pickupEl + 'f' + to_string(MaxIndex2);

				return pickupMove;
			}
		}
	}
	
}

string getAIPickupList(const Move& move, const BuildingState& buildingState,
	const Floor& floorToPickup) {


	BuildingState state;
	int upRequest = 0;
	int downRequest = 0;
	string pickupList = "";
	int totalAngerLevelUp = 0;
	int totalAngerLevelDown = 0;
	int numUpRequests = 0;
	int numDownRequests = 0;
	int numPeopleOnFloor = floorToPickup.getNumPeople();
	int maxAnger = 0;
	int maxAngerIndex = 0;
	bool upperRequest = false;
	int maxPeopleOnFloor = 0;

	for (int j = 0; j < floorToPickup.getNumPeople(); j++) {
		if (floorToPickup.getPersonByIndex(j).getAngerLevel() > maxAnger) {
			maxAnger = floorToPickup.getPersonByIndex(j).getAngerLevel();
			maxAngerIndex = j;
		}

	}

	if (maxAnger < 7) {
		for (int person = 0; person < floorToPickup.getNumPeople(); person++) {
			if (floorToPickup.getPersonByIndex(person).getTargetFloor() > floorToPickup.getPersonByIndex(person).getCurrentFloor()) {
				upRequest++;
			}
			else if (floorToPickup.getPersonByIndex(person).getTargetFloor() < floorToPickup.getPersonByIndex(person).getCurrentFloor()) {
				downRequest++;
			}
		}
		//checking if there are majority up requests or down requests
		if (upRequest > downRequest) {
			for (int k = 0; k < floorToPickup.getNumPeople(); k++) {
				if (floorToPickup.getPersonByIndex(k).getTargetFloor()
			> floorToPickup.getPersonByIndex(k).getCurrentFloor()) {
					//make list of all people by index with up request
					pickupList += to_string(k);
				}
			}
			return pickupList;
		}
		else if (upRequest < downRequest) {
			for (int k = 0; k < floorToPickup.getNumPeople(); k++) {
				if (floorToPickup.getPersonByIndex(k).getTargetFloor()
					< floorToPickup.getPersonByIndex(k).getCurrentFloor()) {
					//make list of all people by index with down request
					pickupList += to_string(k);
				}
			}
			return pickupList;
		}
	}

	if (floorToPickup.getPersonByIndex(maxAngerIndex).getCurrentFloor() < floorToPickup.getPersonByIndex(maxAngerIndex).getTargetFloor()) {
		upperRequest = true;
	}

	if (upperRequest) {
		for (int u = 0; u < floorToPickup.getNumPeople(); u++) {
			if (floorToPickup.getPersonByIndex(u).getCurrentFloor() < floorToPickup.getPersonByIndex(u).getTargetFloor()) {
				pickupList += to_string(u);

			}
		}
		return pickupList;
	}
	else if (!upperRequest) {
		for (int m = 0; m < floorToPickup.getNumPeople(); m++) {
			if (floorToPickup.getPersonByIndex(m).getCurrentFloor() > floorToPickup.getPersonByIndex(m).getTargetFloor()) {
				pickupList += to_string(m);

			}
		}
		return pickupList;
	}
	
	string list = "0";
	return list;

}
