/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Game.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */

#include <random>
#include <sstream>
#include "Game.h"
#include "AI.h"
#include "Utility.h"
using namespace std;
/**
     * Requires: nothing
     * Modifies: cout, isAIMode, building, satisfactionIndex
     * Effects:  if game input file is not open, exits with status 1
     *           sets isAIMode
     *           prints game start prompt
     *           else reads events from game input file
     *           if event is happening on current turn, updates building
     *           with event else prints building and checks if game has
     *           ended, if it hasn't yet, gets user (player or AI) move,
     *           and updates building with move.
     */

     // Stub for playGame for Core, which plays random games
     // You *must* revise this function according to the RME and spec
void Game::playGame(bool isAIModeIn, ifstream& gameFile) {

    std::mt19937 gen(1);
    std::uniform_int_distribution<> floorDist(0, 9);
    std::uniform_int_distribution<> angerDist(0, 3);

    if (!gameFile.is_open()) {
        exit(EXIT_FAILURE);
    }
    isAIMode = isAIModeIn;
    printGameStartPrompt();
    initGame(gameFile);



    string str;
    while (gameFile >> str) {
        Person p(str);
        //look at the condition for this
        //get to part where you are spawning the person at the number or not
        // when they are spawned it is before the turn starts\//turn is when they are added to the board then the player has to respond to them
        //cant do turn first then the person
        while (building.getTime() < p.getTurn()) {
            building.prettyPrintBuilding(cout);
            satisfactionIndex.printSatisfaction(cout, false);
            checkForGameEnd();
            Move nextMove = getMove();
            update(nextMove);
        }
        building.spawnPerson(p);
    }

    while (true) {
        building.prettyPrintBuilding(cout);
        satisfactionIndex.printSatisfaction(cout, false);
        checkForGameEnd();
        Move nextMove = getMove();
        update(nextMove);
    }

    /*
    stringstream input;
    while (input >> str) {
        Floor newPerson;
        Floor floors[NUM_FLOORS];
        for (int i = 0; i < NUM_FLOORS; i++) {
            int numPeople = floors[i].getNumPeople();
            for (int j = 0; j < floors[i].getNumPeople(); ++j) {
                Person p = floors[i].getPersonByIndex(j);
                int x = p.getTargetFloor(); //?
                //create a person
                newPerson.addPerson(p, x);
                //determine which tick the person will spawn with
                int y = p.getAngerLevel(); //?
                p.tick(y);
                //play the game
                building.prettyPrintBuilding(cout);
                satisfactionIndex.printSatisfaction(cout, false);
                checkForGameEnd();
                Move m = getMove();
                update(m);
                //create a person
                building.spawnPerson(p);
            }
        }
    }
}
*/
}





/*
std::mt19937 gen(1);
std::uniform_int_distribution<> floorDist(0, 9);
std::uniform_int_distribution<> angerDist(0, 3);
// if event is happening on current turn = if reading in from gameFile is valid
if (!gameFile.is_open()) {
    exit(1);
    isAIMode = isAIModeIn;
    printGameStartPrompt();
}
else {
    //given to us
    isAIMode = isAIModeIn;
    printGameStartPrompt();
    initGame(gameFile);
    while (true) {
        int src = floorDist(gen);
        int dst = floorDist(gen);
        if (src != dst) {
            std::stringstream ss;
            ss << "0f" << src << "t" << dst << "a" << angerDist(gen);
            Person p(ss.str());
            building.spawnPerson(p);
        }
        //added by me
        if (gameFile.good()) {
            building.prettyPrintBuilding(cout);
            satisfactionIndex.printSatisfaction(cout, false);
            checkForGameEnd();
            Move nextMove = getMove();
            update(nextMove);
        }
        else {
            building.prettyPrintBuilding(cout);
            checkForGameEnd();
        }
        /*while (gameFile.is_open()) {
            if (gameFile.good()) {
                building.prettyPrintBuilding(cout);
                satisfactionIndex.printSatisfaction(cout, false);
                checkForGameEnd();
                Move nextMove = getMove();
                update(nextMove);
            }
            else {
                building.prettyPrintBuilding(cout);
                checkForGameEnd();
            }
        }
    }
}

Floor floors[NUM_FLOORS];
for (int i = 0; i < NUM_FLOORS; i++) {
    int numPeople = floors[i].getNumPeople();
}
*/


/*event is happening on current turn, updates building
* with event else prints buildingand checks if game has
* ended, if it hasn't yet, gets user (player or AI) move,
* andupdates building with move.)
* */



// Stub for isValidPickupList for Core
// You *must* revise this function according to the RME and spec
bool Game::isValidPickupList(const string& pickupList, const int pickupFloorNum) const {
    //REQUIREMENTS FOR VALIDITY
        /* There are no duplicate indices present in pickupList
        Each element of pickupList is a non-negative digit
        The length of the pickupList is less than or equal to the capacity of an elevator
        The maximum value pointed to by an index of pickupList must be strictly less than the number of people on the floor pointed to by pickupFloorNum
        Each person represented by an index in pickupList must be going in the same direction relative to pickupFloorNum
        */


        /*
            Floor peopleInElevator;
            Floor targetFloor;
            building.getFloorByFloorNum(pickupFloorNum).getNumPeople();



           // need to define this
            int count = 0;
            int count2 = 0;
            //no duplicates
            for (int i = 0; i < pickupList.length() - 1; i++) {
                for (int j = i + 1; j < pickupList.length(); j++) {
                    if (pickupList[i] == pickupList[j]) {
                        return false;;
                    }
                }
            }
            //no negatives
            for (int g = 0; g < pickupList.length(); g++) {
                if ((pickupList.at(g) - '0') < 0) {
                    return false;
                }
            }
            //length of the pickupList is less than or equal to capacity of elevator
            if (pickupList.length() > ELEVATOR_CAPACITY) {
                return false;
            }
            //if value in pickuplist at any point is greater than or equal to pickupFloorNum return false
            for (int z = 0; z < pickupList.length(); z++) {

                //How do I get the number of people for the floor specified
               int localNumPeople = building.getFloorByFloorNum(pickupFloorNum).getNumPeople();
               //issue on the line below this
                if ((pickupList.at(z) - '0') >= localNumPeople) {
                    return false;
                }
            }
            for (int x = 0; x < pickupList.length(); x++){
                int targetFloorPerson = building.getFloorByFloorNum(pickupFloorNum).getPersonByIndex(x).getTargetFloor();
                 if (targetFloorPerson < pickupFloorNum) {
                     count++;
                 }

                 else if (targetFloorPerson > pickupFloorNum) {
                     count2++;
                 }
            }
            if (count == pickupList.length()) {
                return true;
            }
            else if (count2 == pickupList.length()) {
                return true;
            }
            return true;
            */

            /* /length of list is less than overall capacity of elevator (assuming it is empty)
            if (pickupList.length() > MAX_PEOPLE_PER_FLOOR) {
                return false;
            }
            //attempt to read the number of people in an elevator and adding it to the pickuplist length to make sure that is less than 10
            else if (peopleInElevator.getNumPeople() + pickupList.length() > 10) {
                return false;
            }
            // CONFUSION RN -> pickupList.at(i) is a character not an int, so i'mnot sure of an effective way to compare the inputted character to a number
            //use person function to turn string into ints
            else {
                for (int i = 0; i < pickupList.length() - 1; i++) {
                    //no duplicate indices
                    if (pickupList.at(i) == pickupList.at(i + 1)) {
                        return false;
                    }
                    //index is non-negative digit (originally wrote as 'else if (pickupList.at(i) < 0)')
                    else if (pickupList.at(i) == '-') {
                        return false;
                    }
                    //max index value is less than number of people currently on floor
                   //line right below this has an error
                    else if ((pickupList.at(i) - '0') < (peopleInElevator.getNumPeople() - 1)) {
                        //not sure if this is right -- used the code in building.cpp as a guide
                        //trying to read the pickup list index and getting that as a person, then trying to get the target floor of that person?
                        p = targetFloor.getPersonByIndex(i);
                        if (p.getTargetFloor() < pickupFloorNum || p.getTargetFloor() > pickupFloorNum) {
                            return true;
                        }
                        else {
                            return false;
                        }
                    }
                }
            }
        }*/
        /*int Index = pickupList.at(0) - '0';
        bool direction = false;
        int countUps = 0;
        int countDowns = 0;
        for (int k = 0; k < pickupList.length(); k++) {
            if (building.getFloorByFloorNum(pickupFloorNum).getPersonByIndex(pickupList.at(k) - '0').getTargetFloor() > pickupFloorNum) {
                countUps++;
            }
            else if (building.getFloorByFloorNum(pickupFloorNum).getPersonByIndex(pickupList.at(k) - '0').getTargetFloor() < pickupFloorNum) {
                countDowns++;
            }
        }
        if (!(countDowns == pickupList.length()) && !(countUps == pickupList.length())) {
            return false;
        }
        if (pickupList.length() > ELEVATOR_CAPACITY) {
            return false;
        }
        //could make an iteration that all could make a loop that counts numbers of people being picked up and people who have uprequests
        for (int i = 0; i < pickupList.length(); i++) {
            bool isDirectionValid = false;
            if (((pickupList.at(i) - '0') < 0) || (pickupList.at(i) - '0' > building.getFloorByFloorNum(pickupFloorNum).getNumPeople())) {
                return false;
                //took i out of building.getFloorByFloorNum(i).getNumPeople()))
            }
           // if (building.getFloorByFloorNum(pickupFloorNum).getPersonByIndex(pickupList.at(i)).getTargetFloor() > pickupFloorNum) {
           //     isDirectionValid = true;
           // }
           // if (direction != isDirectionValid) {
           //     return false;
            //}
            for (int f = i + 1; f < pickupList.length(); f++) {
                if ((pickupList.at(i) - '0') == (pickupList.at(f) - '0')) {
                    return false;
                }
            }
        }
        return true;
        */
    for (int i = 0; i < pickupList.length(); i++) {
        for (int j = i + 1; j < pickupList.length(); j++) {
            if (pickupList.at(i) - '0' == pickupList.at(j) - '0') {
                return false;
            }
        }
    }

    //non-negative integers
    for (int i = 0; i < pickupList.size(); i++) {
        if (pickupList.at(i) - '0' < 0) {
            return false;
        }
    }

    //number of indices is less than tha capacity of the elevator
    if (pickupList.length() > ELEVATOR_CAPACITY || pickupList.length() < 1) {
        return false;
    }

    //calculating which index in the pickuplist is the greatest
    int maxIndex = pickupList.at(0) - '0';
    for (int i = 0; i < pickupList.length(); i++) {
        if ((pickupList.at(i) - '0') > maxIndex) {
            maxIndex = pickupList.at(i) - '0';
        }
    }

    //if the max value in the pickuplist is greater than the number of people on the floor 
    //if the list is "0135" and the max index is 5, that means youre trying to acess the 6th person, so it cant be equal to the number of people on a floor either
    if (maxIndex >= building.getFloorByFloorNum(pickupFloorNum).getNumPeople() || maxIndex < 0) {
        return false;
    }

    //if the first value of the list is going down, check to see if the others are going down 
    if (building.getFloorByFloorNum(pickupFloorNum).getPersonByIndex(pickupList.at(0) - '0').getTargetFloor() < pickupFloorNum) {
        for (int i = 1; i < pickupList.length(); i++) {
            if (building.getFloorByFloorNum(pickupFloorNum).getPersonByIndex(pickupList.at(i) - '0').getTargetFloor() > pickupFloorNum) {
                return false;
            }
        }
    }
    //if the first value of the list is going up, check to see if the rest are going up
    else {
        for (int i = 1; i < pickupList.length(); i++) {
            if (building.getFloorByFloorNum(pickupFloorNum).getPersonByIndex(pickupList.at(i) - '0').getTargetFloor() < pickupFloorNum) {
                return false;
            }
        }
    }

    return true;
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

bool Game::performMove(Move& move) const
{
    Elevator elevators[NUM_ELEVATORS];

    for (int i = 0; i < NUM_ELEVATORS; ++i)
    {
        elevators[i] = building.getElevatorById(i);
    }

    if (move.isValidMove(elevators) && move.isPickupMove())
    {

        Elevator taggedElevator = building.getElevatorById(move.getElevatorId());
        Floor taggedFloor = building.getFloorByFloorNum(taggedElevator.getCurrentFloor());

        if (taggedFloor.getNumPeople() > 0)
        {
            getPeopleToPickup(move);
            return true;
        }

        return false;
    }
    else if (move.isSaveMove())
    {
        performSave();
    }
    else if (move.isQuitMove())
    {
        performQuit();
    }
    else if (!move.isValidMove(elevators))
    {
        return false;
    }

    return true;
}

void Game::printWelcomeMenu() const
{
    cout << "########################################" << endl;
    cout << "# Welcome to EECS 183 Elevator Escape! #" << endl;
    cout << "########################################" << endl
        << endl;
}

void Game::printIntroMenu() const
{
    cout << "[0] Run Tests" << endl;
    cout << "[1] Load saved game" << endl;
    cout << "[2] Start new game" << endl;
    cout << "Choice: ";
}

void Game::printAIMenu() const {
    cout << "[1] Play as human" << endl;
    cout << "[2] Watch AI play" << endl;
    cout << "Choice: ";
}

void Game::printOptions() const
{
    cout << "########################################" << endl;
    cout << "#         Enter service move:          #" << endl;
    cout << "#     'e' elevatorId 'f' floorNum      #" << endl;
    cout << "#            Or pickup move:           #" << endl;
    cout << "#          'e' elevatorId 'p'          #" << endl;
    cout << "########################################" << endl;
}

void Game::printGameStartPrompt() const
{
    cout << endl;
    cout << "########################################" << endl;
    cout << "#                 Enter:               #" << endl;
    cout << "#               Q to Quit              #" << endl;
    cout << "#               S to Save              #" << endl;
    cout << "#      At any time after this prompt   #" << endl;
    cout << "########################################" << endl;
    cout << endl;
    cout << "Press enter to continue....";

    string trash;
    getline(cin, trash);
    cout << endl;
}

IntroChoice Game::getIntroChoice() const {

    if (IS_AI_OVERRIDE) {
        return IntroChoice::New;
    }

    int choice = -1;

    while ((choice < 0) || (choice > 2))
    {
        printIntroMenu();
        string s_choice;
        getline(cin, s_choice);
        choice = stoi(s_choice);

        if ((choice < 0) || (choice > 2))
        {
            cout << endl
                << "Invalid menu choice!" << endl
                << endl;
        }
    }

    cout << endl;

    return static_cast<IntroChoice>(choice);
}

AIChoice Game::getAIChoice() const {
    if (IS_AI_OVERRIDE) {
        return AIChoice::AI;
    }

    int choice = 0;
    printAIMenu();
    string s_choice;
    getline(cin, s_choice);
    choice = stoi(s_choice);
    while (choice != 1 && choice != 2) {
        cout << endl << "Invalid menu choice!" << endl << endl;
        getline(cin, s_choice);
        choice = stoi(s_choice);
    }

    cout << endl;

    return static_cast<AIChoice>(choice);
}

void Game::printSatisfactionIndex() const
{
    cout << endl
        << endl;
    cout << "Your hotel's current satisfaction index is: " << satisfactionIndex;
    cout << endl
        << endl;
}

void Game::getPeopleToPickup(Move& move) const
{
    int currentFloorNum = building.getElevatorById(move.getElevatorId()).getCurrentFloor();
    Floor currentFloor = building.getFloorByFloorNum(currentFloorNum);

    if (currentFloor.getNumPeople() == 1)
    {
        move.setPeopleToPickup("0", currentFloorNum, currentFloor);
        return;
    }

    string peopleIndices = "";
    bool isValidPickup = false;

    while (!isValidPickup)
    {

        currentFloor.printFloorPickupMenu(cout);
        cout << endl;
        cout << "Choices: ";
        getline(cin, peopleIndices);
        cout << "\n";

        if (isAIMode) {
            Elevator e = building.getElevatorById(move.getElevatorId());
            Floor f = building.getFloorByFloorNum(e.getCurrentFloor());
            peopleIndices = getAIPickupList(move, building.getBuildingState(), f);
            cout << "AI OVERRIDE: " << peopleIndices << endl;
        }

        isValidPickup = isValidPickupList(peopleIndices, currentFloorNum);

        if (!isValidPickup)
        {
            cout << "Invalid list of people chosen!" << endl;
            checkForGameEnd();
        }
    }

    move.setPeopleToPickup(peopleIndices, currentFloorNum, currentFloor);
}

Move Game::getMove() const
{
    Move moveObj;
    string moveString = "";
    bool isValid = false;
    GameChoice choiceCapture = GameChoice::Invalid;

    do
    {
        cout << "Enter move: ";

        getline(cin, moveString);
        cout << "\n";

        if (isAIMode) {
            moveString = getAIMoveString(building.getBuildingState());
            cout << "AI OVERRIDE: " << moveString << endl;
        }
        moveObj = Move(moveString);
        choiceCapture = static_cast<GameChoice>(moveString[0]);

        switch (choiceCapture)
        {
        case GameChoice::Quit:
            performQuit();
            break;
        case GameChoice::Save:
            isValid = performSave();
            break;
        case GameChoice::Pass:
        case GameChoice::Move:
            isValid = performMove(moveObj);
            break;
        default:
            isValid = false;
            break;
        }

        if (!isValid)
        {
            cout << endl
                << "Invalid move!" << endl
                << endl;
            checkForGameEnd();
        }

    } while (!isValid);

    return moveObj;
}

void Game::performQuit() const
{
    QuitChoice quitChoice = static_cast<QuitChoice>(getExitChoice());
    switch (quitChoice)
    {
    case QuitChoice::Quit:
        endGame();
        break;
    case QuitChoice::Stay:
        return;
        break;
    }
}

bool Game::performSave() const
{
    ofstream saveFile(LOAD_FILENAME);
    if (!saveFile.is_open())
    {
        cout << "Could not open " << LOAD_FILENAME << endl;
        return false;
    }
    return saveGame(saveFile);
}

void Game::initGame(ifstream& loadFile)
{
    cout << endl
        << "Loading game..." << endl;

    loadFile >> satisfactionIndex;

    int tempTime;
    loadFile >> tempTime;

    building.setTime(tempTime);

    string elvState;
    for (int i = 0; i < NUM_ELEVATORS; i++)
    {
        loadFile >> elvState;
        building.setElevator(elvState, i);
    }

    cout << "Loaded!" << endl
        << endl;
}

void Game::printExitMenu() const
{
    cout << endl;
    cout << "Are you sure you want to quit?" << endl;
    cout << "[1] Yes, I'm sure!" << endl;
    cout << "[2] No, keep playing!" << endl;
    cout << "Choice: ";
}

int Game::getExitChoice() const
{
    int exitChoice = 0;

    while ((exitChoice < 1) || (exitChoice > 2))
    {
        printExitMenu();

        string choice = "";
        getline(cin, choice);
        exitChoice = stoi(choice);

        if ((exitChoice < 1) || (exitChoice > 2))
        {
            cout << endl
                << "Invalid menu choice!" << endl
                << endl;
        }
    }
    cout << endl;

    return exitChoice;
}

void Game::endGame() const
{
    cout << endl
        << "Goodbye!" << endl;
    satisfactionIndex.save();
    exit(0);
}

void Game::printSuccessEnding() const
{
    cout << endl
        << endl;
    cout << "Time is up! Your final score is: " << endl;
    satisfactionIndex.printSatisfaction(cout);
}

void Game::printFailureEnding() const
{
    cout << endl
        << endl;
    cout << "Uh oh! Your hotel has gone out of business!" << endl;
    cout << "Better luck next time!" << endl
        << endl;
    cout << "Your final achievement:" << endl
        << endl;
    satisfactionIndex.printSatisfaction(cout);
}

void Game::checkForGameEnd() const
{
    if (building.getTime() >= MAX_TURNS)
    {
        printSuccessEnding();
        endGame();
    }
    else if (satisfactionIndex.getSatisfaction() < 0)
    {
        printFailureEnding();
        endGame();
    }
}

void Game::update(const Move& m)
{
    if (m.isPickupMove())
    {
        satisfactionIndex.updateSumDirectionRequest(m, building);
    }
    satisfactionIndex.updateSumExploded(building.tick(m));
    satisfactionIndex.updateTimeReached(building);
    if (building.getTime() % 2)
    {
        satisfactionIndex.updateSumIdle(building);
    }
}

// Stub for saveGame for project
// You will *not* implement this function for the project
bool Game::saveGame(ofstream& saveFile) const {
    return true;
}