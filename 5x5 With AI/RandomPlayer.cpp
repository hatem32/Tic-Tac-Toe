#include <iostream>
#include <random>
#include <iomanip>
#include <algorithm>
#include "BoardGame.hpp"
using namespace std;

// Set player symbol and name as Random Computer Player
RandomPlayer1::RandomPlayer1(char symbol, int dimension) : Playern(symbol)
{
    this->dimension = dimension;
    this->name = "Random Computer Player";
    cout << "My names is " << name << endl;
}

// Generate a random move
void RandomPlayer1::get_move(int &x, int &y)
{
    x = (int)(rand() / (RAND_MAX + 1.0) * dimension);
    y = (int)(rand() / (RAND_MAX + 1.0) * dimension);
}
