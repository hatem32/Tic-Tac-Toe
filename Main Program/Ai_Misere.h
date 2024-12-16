#ifndef _MINMAXPLAYER_H
#define _MINMAXPLAYER_H

#include "Misere_X_O.h"


template <typename T>
class X_O_MinMaxPlayer : public Playerx<T> {
public:
    X_O_MinMaxPlayer(T symbol);

    void getmove(int& x, int& y) override;

private:
    int calculateMinMax(T s, bool isMaximizing);
    std::pair<int, int> getBestMove();
};







//--------------------------------------- IMPLEMENTATION

#include <limits>
#include <algorithm> // For std::max and std::min
using namespace std;
// Constructor for the templated class
template <typename T>
X_O_MinMaxPlayer<T>::X_O_MinMaxPlayer(T symbol) : Playerx<T>(symbol) {
    this->name = "AI Player";
}

// Method to get the best move for the player
template <typename T>
void X_O_MinMaxPlayer<T>::getmove(int& x, int& y) {
    std::pair<int, int> bestMove = getBestMove();
    x = bestMove.first;
    y = bestMove.second;
}

// Minimax algorithm to evaluate the board
template <typename T>
int X_O_MinMaxPlayer<T>::calculateMinMax(T s, bool isMaximizing) {
    if (this->boardPtr->is__win()) {
        return isMaximizing ? -1 : 1;
    } else if (this->boardPtr->is__draw()) {
        return 0;
    }

    int bestValue = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    T opponentSymbol = (s == 'X') ? 'O' : 'X';

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (this->boardPtr->update__board(i, j, s)) {
                int value = calculateMinMax(opponentSymbol, !isMaximizing);
                this->boardPtr->update__board(i, j, 0); // Undo move

                if (isMaximizing) {
                    bestValue = std::max(bestValue, value);
                } else {
                    bestValue = std::min(bestValue, value);
                }
            }
        }
    }

    return bestValue;
}

// Find the best move using the minimax algorithm
template <typename T>
std::pair<int, int> X_O_MinMaxPlayer<T>::getBestMove() {
    int bestValue = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = {-1, -1};
    T opponentSymbol = (this->symbol == 'X') ? 'O' : 'X';

   for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
        if (this->boardPtr->update__board(i, j, this->symbol)) {
            if (!this->boardPtr->is__win()) {
                this->boardPtr->update__board(i, j, 0); // Undo move
                return {i, j}; // Valid move (not a winning move)
            }
            this->boardPtr->update__board(i, j, 0); // Undo move
        }
    }
}


    // If no immediate win or block, use MinMax to find the best move
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (this->boardPtr->update__board(i, j, this->symbol)) {
                int moveValue = calculateMinMax(this->symbol, false);
                this->boardPtr->update__board(i, j, 0); // Undo move

                if (moveValue > bestValue) {
                    bestMove = {i, j};
                    bestValue = moveValue;
                }
            }
        }
    }

    return bestMove;
}
















#endif //_MINMAXPLAYER_H