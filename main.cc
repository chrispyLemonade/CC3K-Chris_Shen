#include <iostream>
#include <sstream>
#include "game.h"
#include "enum.h"
using namespace std;

int main(int argc, char *argv[]) {
    Game *game = new Game{};
    cout << "Game Begin!!!" << endl;
    cout << "If you want to quit, please type q." << endl;

    bool hasMap = 0;
    string fileName = "ccekfloor.txt";
    if (argc == 2) {
        hasMap = 1;
        fileName = argv[1];
    }
    game->gameStart(hasMap, fileName);
    cout << endl;

    game->nextFloor();

    cout << "Please choose your Race: " << endl;
    cout << "Human - h;   Dwarf - d;   Elves - e;   Orc - o" << endl;

    char cmd;
    bool pickPotion = 0;
    bool attack = 0;
    bool gameStart = false;
    DirectionType dir;
    string oneLine;
    while (getline(cin, oneLine)) {
        istringstream singleCmd (oneLine);
        string cmdStr;
        while (singleCmd >> cmdStr) {
            if (cmdStr == "q") {
                cout << "Game End!" << endl;
                return 0;
            } else if (cmdStr == "r") {
                gameStart = false;
                // delete game;
                game = new Game{};
                cout << "Game Restart!" << endl;
                game->gameStart(hasMap, fileName);
                cout << endl;
                game->nextFloor();
                cout << "Player character has spawned." << endl;
                cout << "Please choose your Race: " << endl;
                cout << "Human - h;   Dwarf - d;   Elves - e;   Orc - o" << endl;
            } else if (cmdStr == "h") {
                if (!gameStart) {
                    game->setRace(RaceType::HUMAN);
                    cout << "Player character was changed to Human." << endl;
                } else {
                    cout << "U cannot change race during the game." << endl;
                }
            } else if (cmdStr == "d") {
                if (!gameStart) {
                    game->setRace(RaceType::DWARF);
                    cout << "Player character was changed to Dwarf." << endl;
                } else {
                    cout << "U cannot change race during the game." << endl;
                }
            } else if (cmdStr == "o") {
                if (!gameStart) {
                    game->setRace(RaceType::ORC);
                    cout << "Player character was changed to Orc." << endl;
                } else {
                    cout << "U cannot change race during the game." << endl;
                }            
            } else if (cmdStr == "e") {
                if (!gameStart) {
                    game->setRace(RaceType::ELVES);
                    cout << "Player character was changed to Elves." << endl;
                } else {
                    cout << "U cannot change race during the game." << endl;
                }
            } else if (cmdStr == "u") {
                gameStart = true;
                pickPotion = 1;
            } else if (cmdStr == "a") {
                gameStart = true;
                attack = 1;
            } else if (cmdStr == "nnssweweab") {
                game->developerMode();
                cout << "Notice: You are in the Developer Mode." << endl;
            } else {
                gameStart = true;
                if (cmdStr == "no") {
                    dir = DirectionType::NO;
                } else if (cmdStr == "ne") {
                    dir = DirectionType::NE;
                } else if (cmdStr == "nw") {
                    dir = DirectionType::NW;
                } else if (cmdStr == "so") {
                    dir = DirectionType::SO;
                } else if (cmdStr == "se") {
                    dir = DirectionType::SE;
                } else if (cmdStr == "sw") {
                    dir = DirectionType::SW;
                } else if (cmdStr == "ea") {
                    dir = DirectionType::EA;
                } else if (cmdStr == "we") {
                    dir = DirectionType::WE;
                } else {
                    cout << "Sry, I don't understand what u just said." << endl;
                    break;
                }

                if (pickPotion) {
                    if (!game->pickUpPotion(dir)) {
                        cout << endl;
                        cout << endl;
                        cout << "Do you want restart? r - Restart; q - Quit" << endl; 
                    }
                } else if (attack) {
                    if (!game->pcAttack(dir)) {
                        cout << endl;
                        cout << endl;
                        cout << "Do you want restart? r - Restart; q - Quit" << endl; 
                    }
                } else {
                    if (!game->pcMove(dir)) {
                        cout << endl;
                        cout << endl;
                        cout << "Do you want restart? r - Restart; q - Quit" << endl; 
                    }
                }

                pickPotion = 0;
                attack = 0;
            } 
        }
    } 
    return 0;
}
