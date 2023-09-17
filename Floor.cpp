/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Floor.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */


#include "Floor.h"
#include <algorithm>
using namespace std;


/*
	* Requires: nothing
	* Modifies: people
	* Effects:  Ticks each person on this floor
	*           Also removes any Person who explodes
	*           Returns the number of exploded people
	*/
int Floor::tick(int currentTime) {
	int removeExplodedPeople[MAX_PEOPLE_PER_FLOOR];
	int explodedPeople = 0;
	//int temp = 0;
	int indexToRemove = 0;
	//int time = 1;
	//while (numPeople != 0) {
	for (int i = 0; i < numPeople; i++) {
		if (people[i].tick(currentTime)) {
			//int temp = i;
			removeExplodedPeople[indexToRemove] = i;
			indexToRemove++;
			//removePeople(removeExplodedPeople, explodedPeople);
			explodedPeople++;
			//time++;


		}
		//else if (!people[i].tick(currentTime)) {
			//time++;
		//}

	}
	//}
	removePeople(removeExplodedPeople, explodedPeople);

	return explodedPeople;

}


/*
	 * Requires: request != 0
	 * Modifies: hasUpRequest, hasDownRequest, numPeople, people
	 * Effects:  If there is still room, add newPerson to people.
	 *           Updates hasUpRequest or hasDownRequest based on value of request
	 */

void Floor::addPerson(Person newPerson, int request) {
	//TODO: Implement addPerson
	if (numPeople < MAX_PEOPLE_PER_FLOOR) {
		people[numPeople] = newPerson;
		if (request > 0) {
			hasUpRequest = true;
		}
		else if (request < 0) {
			hasDownRequest = true;
		}
		numPeople++;
	}

	return;
	/*if (numPeople < MAX_PEOPLE_PER_FLOOR) {
		people[numPeople] = newPerson;
		if (request > 0) {
			hasUpRequest = true;
		}
		else if (request < 0) {
			hasDownRequest = true;
		}
		numPeople++;
	}*/
	//how do I add newPerson to people, is people an array? Yes people is an array with MAX_PEOPLE_PER_FLOOR as the max point


}

/*
	 * Requires: numPeopleToRemove >= 0, numPeopleToRemove <= MAX_PEOPLE_PER_FLOOR,
	 *           numPeopleToRemove >= 0, numPeopleToRemove <= numPeople,
	 *           for all values of i such that 0 <= i < numPeopleToRemove, indicesToRemove[i] < numPeople
	 * Modifies: people[], numPeople, hasUpRequest, hasDownRequest
	 * Effects:  Removes objects from people[] at indices specified in indicesToRemove[].
	 *           The size of indicesToRemove[] is given by numPeopleToRemove.
	 *           After removals, calls resetRequests() to update hasUpRequest and hasDownRequest.
	 * //TODO: Implement removePeople interate over total people array and inside that iterate over people to remove
	//set a alternate array and store people to keep in it and then set the indices for people equal to that array
	/*Person temp[MAX_PEOPLE_PER_FLOOR];
	int countPeopleRemaining = 0;
	for (int i = 0; i < numPeople; i++) {
		for (int f = 0; f < numPeopleToRemove; f++) {
			if (i != indicesToRemove[f]) {
				temp[i] = people[i];
				countPeopleRemaining++;

			}

		}
	}
	for (int g = 0; g < countPeopleRemaining; g++) {
		people[g] = temp[g];
	}
	resetRequests();
	return;
	*/

	/*for (int i = 0; i < numPeople; i++) {
		for (int f = 0; f < numPeopleToRemove; f++)

		{
			if (i == (indicesToRemove[f])) {
				for (int j = i; j < (numPeople - 1); j++) {
					people[j] = people[j + 1];

					numPeople--;
					numPeopleToRemove--;

				}
				while (indicesToRemove[f] > i)
				for (int g = 0; g < numPeopleToRemove; g++) {
					indicesToRemove[f] = (indicesToRemove[f] - 1);

				}

			}
		}

}
	*/
	/*
	for (int i = 0; i < numPeople; i++) {
		for (int f = 0; f < numPeopleToRemove; f++) {
			if (i == (indicesToRemove[f])) {
				for (int j = i; j < (numPeople - 1); j++) {
					people[j] = people[j + 1];
					// indicesToRemove[j + 1] = (indicesToRemove[j] - 1);
				}
				// for (int g = i; g < numPeopleToRemove; g++) {
				//   indicesToRemove[f] = (indicesToRemove[f] - 1);
				// }
				for (int g = 0; g < numPeopleToRemove; g++)
				{
					if (indicesToRemove[g] > i)
					{
						indicesToRemove[g]--;
					}
				}
				numPeople -= numPeopleToRemove;
			}
		}
	}
	resetRequests();
	*/


	/*sort(indicesToRemove, indicesToRemove + numPeopleToRemove);

	for (int i = numPeopleToRemove - 1; i >= 0; i--) {
		int x = indicesToRemove[i];
		for (int j = 0; j < numPeople - 1; j++) {
			if (j == x) {
				for (int g = j; g < numPeople; g++) {
					people[g] = people[g + 1];
				}
				numPeople--;
			}
		}
		resetRequests();
	}
	*/

	//maybe I can set non-occupied array spots to NULL

void Floor::removePeople(int indicesToRemove[MAX_PEOPLE_PER_FLOOR], int numPeopleToRemove) {
	//use of person constructor can set every value for a person to zero
	//this could solve the issue I have been having with iterating and getting duplicates 
	Person empty;
	for (int i = 0; i < numPeopleToRemove; i++) {
		people[indicesToRemove[i]] = empty;
	}
	for (int j = 0; j < numPeopleToRemove; j++) {
		for (int k = 0; k < numPeople; k++) {
			if (people[k].getAngerLevel() == 0 && people[k].getCurrentFloor() == 0 && people[k].getTurn() == 0 && people[k].getTargetFloor() == 0) {
				for (int g = k; g < numPeople; g++) {
					people[g] = people[g + 1];
				}

			}
		}
	}
	numPeople -= numPeopleToRemove;
	resetRequests();
}


//I think there are several ways to do this function but this is sort of along the lines that I am thinking NEED to fix error
// when i is an indice to remove it will be removed and then all the indices to be removed must go down by one
/*
	* Requires: nothing
	* Modifies: hasUpRequest, hasDownRequest
	* Effects: Search through people to find if there are any
	*          pending up requests or down requests. Set the
	*          values of hasUpRequest and hasDownRequest appropriately.
	*          This function is used to recalculate requests whenever
	*          the people on this floor are added or removed.
	*/

void Floor::resetRequests() {
	//TODO: Implement resetRequests
	//first we need to iterate through the array to count the number of hasUp and hasDown requests easy loop solution but what do I need to call to see if a person has such a request
	//then simply set the request value to the count
	/*int noUpCounter = 0;
	int noDownCounter = 0;
	for (int i = 0; i < numPeople; i++) {
		int tf = people[i].getTargetFloor();
		int cf = people[i].getCurrentFloor();
		if (tf > cf) {
			hasUpRequest = true;
			noDownCounter++;
		}
		else if (cf > tf) {
			hasDownRequest = true;
			noUpCounter++;
		}

	}
	if (noDownCounter == numPeople - 1) {
		hasDownRequest = false;
	}
	if (noUpCounter == numPeople - 1) {
		hasUpRequest = false;
	}*/


	hasUpRequest = false;
	hasDownRequest = false;
	for (int i = 0; i < numPeople; i++) {
		//int tf = people[i].getTargetFloor();
		//int cf = people[i].getCurrentFloor();
		if (people[i].getTargetFloor() > people[i].getCurrentFloor()) {
			hasUpRequest = true;
			//noDownCounter++;
		}
		else if (people[i].getTargetFloor() < people[i].getCurrentFloor()) {
			hasDownRequest = true;
			//noUpCounter++;
		}
	}

}



//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Floor::Floor() {
	hasDownRequest = false;
	hasUpRequest = false;
	numPeople = 0;
}

void Floor::prettyPrintFloorLine1(ostream& outs) const {
	string up = "U";
	outs << (hasUpRequest ? up : " ") << " ";
	for (int i = 0; i < numPeople; ++i) {
		outs << people[i].getAngerLevel();
		outs << ((people[i].getAngerLevel() < MAX_ANGER) ? "   " : "  ");
	}
	outs << endl;
}

void Floor::prettyPrintFloorLine2(ostream& outs) const {
	string down = "D";
	outs << (hasDownRequest ? down : " ") << " ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "o   ";
	}
	outs << endl;
}

void Floor::printFloorPickupMenu(ostream& outs) const {
	cout << endl;
	outs << "Select People to Load by Index" << endl;
	outs << "All people must be going in same direction!";
	/*  O   O
	// -|- -|-
	//  |   |
	// / \ / \  */
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " O   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "-|-  ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " |   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "/ \\  ";
	}
	outs << endl << "INDEX:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << i << "   ";
	}
	outs << endl << "ANGER:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getAngerLevel() << "   ";
	}
	outs << endl << "TARGET FLOOR: ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getTargetFloor() << "   ";
	}
}

void Floor::setHasUpRequest(bool hasRequest) {
	hasUpRequest = hasRequest;
}

bool Floor::getHasUpRequest() const {
	return hasUpRequest;
}

void Floor::setHasDownRequest(bool hasRequest) {
	hasDownRequest = hasRequest;
}

bool Floor::getHasDownRequest() const {
	return hasDownRequest;
}

int Floor::getNumPeople() const {
	return numPeople;
}

Person Floor::getPersonByIndex(int index) const {
	return people[index];
}