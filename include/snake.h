#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
using namespace std;
/* Number of food pellets that must be eaten to win. */
const int kMaxFood = 20;
/* Constants for the different tile types. */
const char kEmptyTile = ' ';
const char kWallTile = '#';
const char kFoodTile = '$';
const char kSnakeTile = '*';
/* A struct encoding a point in a two-dimensional grid. */
struct pointT {
    int row, col;
};
/* A struct containing relevant game information. */
struct gameT {
    vector<string> world; // The playing field
    int numRows, numCols; // Size of the playing field
    deque<pointT> snake; // The snake body
    int dx, dy; // The snake direction
    int numEaten; // How much food we've eaten.
};

bool Crashed(pointT headPos,gameT & game);
void DisplayResult(gameT & game);
string GetLine();
pointT GetNextPosition(gameT & game,int dx,int dy);
bool InWorld(pointT & pt,gameT & game);
void InitializeGame(gameT & game);
void LoadWorld(gameT & game,ifstream & input);
pointT MakePoint(int row,int col);
bool MoveSnake(gameT & game);
void OpenUserFile(ifstream & input);
void Pause();
void PerformAI(gameT & game);
void PlaceFood(gameT & game);
void PrintWorld(gameT & game);
bool RandomChance(double probability);
void RunSimulation(gameT & game);

#endif
