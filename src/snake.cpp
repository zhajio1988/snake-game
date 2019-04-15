#include "snake.h"

string GetLine() {
    string result;
    //cout << "Please, enter a real number: ";
    getline(cin, result);

    return result;
}

void OpenUserFile(ifstream& input) {
    while(true) {
        cout << "Enter filename: ";
        string filename = GetLine();
        input.open(filename.c_str()); // See Chapter 3 for .c_str().
        if(input.is_open()) return;
        cout << "Sorry, I can't find the file " << filename << endl;
        input.clear();
    }
}
void InitializeGame(gameT& game) {
    srand(static_cast<unsigned int>(time(NULL)));
    ifstream input;
    OpenUserFile(input);
    LoadWorld(game, input);
}

pointT MakePoint(int row, int col) {
    pointT result;
    result.row = row;
    result.col = col;
    return result;
}

void LoadWorld(gameT& game, ifstream& input) {
    input >> game.numRows >> game.numCols;
    game.world.resize(game.numRows);
    input >> game.dx >> game.dy;
    string dummy;
    getline(input, dummy);
    for(int row = 0; row < game.numRows; ++row) {
        getline(input, game.world[row]);
        string::size_type col = game.world[row].find(kSnakeTile);
        if(col != string::npos)
            game.snake.push_back(MakePoint(row, col));
    }
    game.numEaten = 0;
}

void RunSimulation(gameT& game) {
    /* Keep looping while we haven't eaten too much. */
    while(game.numEaten < kMaxFood) {
        PrintWorld(game); // Display the board
        PerformAI(game); // Have the AI choose an action
        if(!MoveSnake(game)) // Move the snake and stop if we crashed.
            break;
        Pause(); // Pause so we can see what's going on.
    }
    DisplayResult(game); // Tell the user what happened
}

const double kWaitTime = 0.3; // Pause 0.1 seconds between frames
void Pause() {
    clock_t startTime = clock(); // clock_t is a type which holds clock ticks.
    /* This loop does nothing except loop and check how much time is left.
* Note that we have to typecast startTime from clock_t to double so
* that the division is correct. The static_cast<double>(...) syntax
* is the preferred C++ way of performing a typecast of this sort;
* see the chapter on
* inheritance for more information.
*/
    while(static_cast<double>(clock() - startTime) / CLOCKS_PER_SEC <
          kWaitTime);
}

const string kClearCommand = "clear";
void PrintWorld(gameT& game) {
    system(kClearCommand.c_str());
    for(int row = 0; row < game.numRows; ++row)
        cout << game.world[row] << endl;
    cout << "Food eaten: " << game.numEaten << endl;
}

void DisplayResult(gameT& game) {
    PrintWorld(game);
    if(game.numEaten == kMaxFood)
        cout << "The snake ate enough food and wins!" << endl;
    else
        cout << "Oh no! The snake crashed!" << endl;
}

pointT GetNextPosition(gameT& game, int dx, int dy) {
    /* Get the head position. */
    pointT result = game.snake.front();
    /* Increment the head position by the specified direction. */
    result.row += dy;
    result.col += dx;
    return result;
}
bool Crashed(pointT headPos, gameT& game) {
    return !InWorld(headPos, game) ||
            game.world[headPos.row][headPos.col] == kSnakeTile ||
            game.world[headPos.row][headPos.col] == kWallTile;
}

bool InWorld(pointT& pt, gameT& game) {
    return pt.col >= 0 &&
            pt.row >= 0 &&
            pt.col < game.numCols &&
            pt.row < game.numRows;
}


bool RandomChance(double probability) {
    return (rand() / (RAND_MAX + 1.0)) < probability;
}
const double kTurnRate = 0.2;
void PerformAI(gameT& game) {
    /* Figure out where we will be after we move this turn. */
    pointT nextHead = GetNextPosition(game, game.dx, game.dy);
    /* If that puts us into a wall or we randomly decide to, turn the snake. */
    if(Crashed(nextHead, game) || RandomChance(kTurnRate)) {
        int leftDx = -game.dy;
        int leftDy = game.dx;
        int rightDx = game.dy;
        int rightDy = -game.dx;
        /* Check if turning left or right will cause us to crash. */
        bool canLeft = !Crashed(GetNextPosition(game, leftDx, leftDy),
                                game);
        bool canRight = !Crashed(GetNextPosition(game, rightDx, rightDy),
                                 game);
        bool willTurnLeft = false;
        if(!canLeft && !canRight)
            return; // If we can't turn, don't turn.
        else if(canLeft && !canRight)
            willTurnLeft = true; // If we must turn left, do so.
        else if(!canLeft && canRight)
            willTurnLeft = false; // If we must turn right, do so.
        else
            willTurnLeft = RandomChance(0.5); // Else pick randomly
        game.dx = willTurnLeft? leftDx : rightDx;
        game.dy = willTurnLeft? leftDy : rightDy;
    }
}

bool MoveSnake(gameT& game) {
    pointT nextHead = GetNextPosition(game, game.dx, game.dy);
    if(Crashed(nextHead, game))
        return false;
    bool isFood = (game.world[nextHead.row][nextHead.col] == kFoodTile);
    game.world[nextHead.row][nextHead.col] = kSnakeTile;
    game.snake.push_front(nextHead);
    if(!isFood) {
        game.world[game.snake.back().row][game.snake.back().col] = kEmptyTile;
        game.snake.pop_back();
    } else {
        ++game.numEaten;
        PlaceFood(game);
    }
    return true;
}

void PlaceFood(gameT& game) {
    while(true) {
        int row = rand() % game.numRows;
        int col = rand() % game.numCols;
        /* If the specified position is empty, place the food there. */
        if(game.world[row][col] == kEmptyTile) {
            game.world[row][col] = kFoodTile;
            return;
        }
    }
}
