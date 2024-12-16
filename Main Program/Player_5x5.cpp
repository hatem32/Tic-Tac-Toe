
#include <iostream>
#include <random>
#include <iomanip>
#include <algorithm>
#include "5x5.hpp"
using namespace std;

// Give player a symbol to use in playing
// It can be X or O or others
// This is needed for computer players
// as it does not ask for a name
Playern::Playern(char symbol)
{
    this->symbol = symbol;
}

// Optionally, you can give him ID or order
// Like Player 1 and Player 2
Playern::Playern(int order, char symbol)
{
    cout << "Welcome player " << order << endl;
    cout << "Please enter your name: ";
    cin >> name;
    this->symbol = symbol;
}

// Get desired move: x y (each between 0 and 2)
// Virtual (can change for other player types)
void Playern::get_move(int &x, int &y)
{
    cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
    cin >> x >> y;
}

// Give player info as a string
string Playern::to_string()
{
    return "Player: " + name;
}

// Get symbol used by player
char Playern::get_symbol()
{
    return symbol;
}
