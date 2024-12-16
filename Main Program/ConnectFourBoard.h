#ifndef _CONNECTFOURBOARD_H
#define _CONNECTFOURBOARD_H

#include "BoardGame_Classes.h"
#include "MinMaxPlayer.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Board class for Connect Four
template <typename T>
class ConnectFourBoard : public Board<T> {
public:
    ConnectFourBoard();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

// Player class for Connect Four
template <typename T>
class ConnectFourPlayer : public Player<T> {
public:
    ConnectFourPlayer(string name, T symbol);
    void getmove(int& x, int& y) override;
};

// Random player class for Connect Four
template <typename T>
class ConnectFourRandomPlayer : public RandomPlayer<T> {
public:
    ConnectFourRandomPlayer(T symbol);
    void getmove(int& x, int& y) override;
};
// Ai player class for Connect Four
template <typename T>
class ConnectFourAiPlayer : public X_O_MinMax_Player<T> {
public:
    ConnectFourAiPlayer(T symbol);
    void getmove(int& x, int& y) override;
};

// Implementation

// Constructor for ConnectFourBoard
template <typename T>
ConnectFourBoard<T>::ConnectFourBoard() {
    this->rows = 6; // 6 rows for Connect Four
    this->columns = 7; // 7 columns for Connect Four
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new T[this->columns]();
    }
    this->n_moves = 0;
}

// Update the board for a move
template <typename T>
bool ConnectFourBoard<T>::update_board(int x, int y, T mark) {
    if (y < 0 || y >= this->columns) return false; // Invalid column
    for (int i = this->rows - 1; i >= 0; --i) { // Start from the bottom row
        if (this->board[i][y] == 0) {
            this->board[i][y] = mark;
            this->n_moves++;
            return true;
        }
    }
    return false; // Column is full
}

// Display the board
template <typename T>
void ConnectFourBoard<T>::display_board() {
    for (int i = 0; i < this->rows; ++i) {
        cout << "| ";
        for (int j = 0; j < this->columns; ++j) {
            cout << (this->board[i][j] ? this->board[i][j] : '-') << " ";
        }
        cout << "|\n";
    }
    cout << string(this->columns * 2 + 3, '-') << "\n";
}

// Check if there's a winner
template <typename T>
bool ConnectFourBoard<T>::is_win() {
    // Check horizontal
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j <= this->columns - 4; ++j) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i][j + 1] &&
                this->board[i][j] == this->board[i][j + 2] &&
                this->board[i][j] == this->board[i][j + 3]) {
                return true;
            }
        }
    }

    // Check vertical
    for (int i = 0; i <= this->rows - 4; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i + 1][j] &&
                this->board[i][j] == this->board[i + 2][j] &&
                this->board[i][j] == this->board[i + 3][j]) {
                return true;
            }
        }
    }

    // Check diagonals
    for (int i = 0; i <= this->rows - 4; ++i) {
        for (int j = 0; j <= this->columns - 4; ++j) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i + 1][j + 1] &&
                this->board[i][j] == this->board[i + 2][j + 2] &&
                this->board[i][j] == this->board[i + 3][j + 3]) {
                return true;
            }
        }
    }

    for (int i = 3; i < this->rows; ++i) {
        for (int j = 0; j <= this->columns - 4; ++j) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i - 1][j + 1] &&
                this->board[i][j] == this->board[i - 2][j + 2] &&
                this->board[i][j] == this->board[i - 3][j + 3]) {
                return true;
            }
        }
    }

    return false;
}

// Check if the game is a draw
template <typename T>
bool ConnectFourBoard<T>::is_draw() {
    return this->n_moves == this->rows * this->columns && !is_win();
}

// Check if the game is over
template <typename T>
bool ConnectFourBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

// Constructor for ConnectFourPlayer
template <typename T>
ConnectFourPlayer<T>::ConnectFourPlayer(string name, T symbol) : Player<T>(name, symbol) {}

// Get the player's move
template <typename T>
void ConnectFourPlayer<T>::getmove(int& x, int& y) {
    cout << "\nEnter your move (column 0-6): ";
    cin >> y;
    x = -1;
}

// Constructor for ConnectFourRandomPlayer
template <typename T>
ConnectFourRandomPlayer<T>::ConnectFourRandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    srand(static_cast<unsigned int>(time(0)));
}

// Get a random move
template <typename T>
void ConnectFourRandomPlayer<T>::getmove(int& x, int& y) {
    y = rand() % 7;
    x = -1;
}
// Constructor for ConnectFourAiPlayer
template <typename T>
ConnectFourAiPlayer<T>::ConnectFourAiPlayer(T symbol) : X_O_MinMax_Player<T>(symbol) {
    srand(static_cast<unsigned int>(time(0)));
}

// Get a Ai move
template <typename T>
void ConnectFourAiPlayer<T>::getmove(int& x, int& y) {
    y = rand() % 7;
    x = 1;
}


#endif // _CONNECTFOURBOARD_H
