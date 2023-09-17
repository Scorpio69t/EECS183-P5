/*
 * Copyright 2022 University of Michigan EECS183
 *
 * main.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Final Project - Elevators
 */

#include <iostream>
#include <fstream>
#include "Utility.h"
#include "Game.h"
using namespace std;

void start_tests();

int main() {
    Game game;

    game.printWelcomeMenu();
    IntroChoice introChoice = game.getIntroChoice();

    string eventSourceFilename = "";

    switch (introChoice) {
        case IntroChoice::Run_Tests: {
            start_tests();
            return 0;
        }
        case IntroChoice::Load: {
            eventSourceFilename = LOAD_FILENAME;
            break;

        }
        case IntroChoice::New: {
            eventSourceFilename = NEW_FILENAME;
            break;
        }
        default:
            throw runtime_error("ERROR: Invalid menu choice detected");
            break;
    }

    ifstream inputFile(eventSourceFilename);
    ofstream gameOutput(GAME_INPUT_FILENAME);
    string line;
    while (getline(inputFile, line)) gameOutput << line << "\n";
    gameOutput.close();
    inputFile.close();

    inputFile.open(GAME_INPUT_FILENAME);

    game.playGame(game.getAIChoice() == AIChoice::AI, inputFile);
    return 0;
}
