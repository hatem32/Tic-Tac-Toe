#ifndef _AI_PYRAMIDXO_H
#define _AI_PYRAMIDXO_H

#include "BoardGame_Classes.h"
#include <limits>
#include <algorithm> // For std::max and std::min

template <typename T>
class X_O_MinMax_Player : public Player<T> {
public:
    X_O_MinMax_Player(T symbol);

    void getmove(int& x, int& y) override;

private:
    int calculateMinMax(T s, bool isMaximizing);
    std::pair<int, int> getBestMove();
    bool isValidPosition(int x, int y);
};

// Constructor
template <typename T>
X_O_MinMax_Player<T>::X_O_MinMax_Player(T symbol) : Player<T>(symbol) {
    this->name = "AI Player";
}

// Helper: Check if position is valid
template <typename T>
bool X_O_MinMax_Player<T>::isValidPosition(int x, int y) {
    return !(x == 0 && y == 0 || x == 0 && y == 1 || x == 0 && y == 3 ||
             x == 1 && y == 0 || x == 1 && y == 4 || x == 0 && y == 4);
}

// Minimax Algorithm
template <typename T>
int X_O_MinMax_Player<T>::calculateMinMax(T s, bool isMaximizing) {
    if (!this->boardPtr->is_win()) {
        return isMaximizing ? -1 : 1;
    } else if (this->boardPtr->is_draw()) {
        return 0;
    }

    int bestValue = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    T opponentSymbol = (s == 'X') ? 'O' : 'X';

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (!isValidPosition(i, j)) continue;

            if (this->boardPtr->update_board(i, j, s)) {
                int value = calculateMinMax(opponentSymbol, !isMaximizing);
                this->boardPtr->update_board(i, j, 0); // Undo move

                bestValue = isMaximizing ? std::max(bestValue, value) : std::min(bestValue, value);
            }
        }
    }
    return bestValue;
}

// Find the best move
template <typename T>
std::pair<int, int> X_O_MinMax_Player<T>::getBestMove() {
    int bestValue = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (!isValidPosition(i, j)) continue;

            if (this->boardPtr->update_board(i, j, this->symbol)) {
                int moveValue = calculateMinMax(this->symbol, false);
                this->boardPtr->update_board(i, j, 0); // Undo move

                if (moveValue > bestValue) {
                    bestMove = {i, j};
                    bestValue = moveValue;
                }
            }
        }
    }
    return bestMove;
}

// Get move using Minimax
template <typename T>
void X_O_MinMax_Player<T>::getmove(int& x, int& y) {
    std::pair<int, int> bestMove = getBestMove();
    x = bestMove.first;
    y = bestMove.second;
}

#endif // _AI_PYRAMIDXO_H
