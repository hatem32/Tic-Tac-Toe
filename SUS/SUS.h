#ifndef _3X3X_SUS_H
#define _3X3X_SUS_H

#include "BoardGame_Classes.h"

template <typename T>
class SUS_Board : public Board<T>
{
private:
    int player1Score;
    int player2Score;

public:
    SUS_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    int getScore(int player) const;
};

template <typename T>
class SUS_Player : public Player<T>
{
public:
    SUS_Player(string name, T symbol);
    void getmove(int &x, int &y);
};

template <typename T>
class SUS_Random_Player : public RandomPlayer<T>{
public:
    SUS_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};
 
 ////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <cctype> // for toupper()

using namespace std;

template <typename T>
SUS_Board<T>::SUS_Board()
{
    this->rows = this->columns = 3;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++)
        {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
    player1Score = 0;
    player2Score = 0;
}

template <typename T>
bool SUS_Board<T>::update_board(int x, int y, T symbol)
{
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == 0)
    {
        this->board[x][y] = toupper(symbol);
        this->n_moves++;

        int susCount = 0; // Count the "S-U-S" sequences created in this turn.

        // Check the row of the move
        if (this->board[x][0] == 'S' && this->board[x][1] == 'U' && this->board[x][2] == 'S')
        {
            susCount++;
        }

        // Check the column of the move
        if (this->board[0][y] == 'S' && this->board[1][y] == 'U' && this->board[2][y] == 'S')
        {
            susCount++;
        }

        // Check the main diagonal if the move is on it
        if (x == y)
        {
            if (this->board[0][0] == 'S' && this->board[1][1] == 'U' && this->board[2][2] == 'S')
            {
                susCount++;
            }
        }

        // Check the anti-diagonal if the move is on it
        if (x + y == 2)
        {
            if (this->board[0][2] == 'S' && this->board[1][1] == 'U' && this->board[2][0] == 'S')
            {
                susCount++;
            }
        }

        // Update player's score
        if (symbol == 'S')
        {
            player1Score += susCount; // Assuming player 1 uses 'S'
        }
        else if (symbol == 'U')
        {
            player2Score += susCount; // Assuming player 2 uses 'U'
        }

        return true;
    }
    return false;
}

template <typename T>
void SUS_Board<T>::display_board()
{
    for (int i = 0; i < this->rows; i++)
    {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++)
        {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << "\nPlayer 1 (S): " << player1Score << " | Player 2 (U): " << player2Score << endl;
}

template <typename T>
bool SUS_Board<T>::is_win()
{
    // The game is won by the player who has more points
    return (this->n_moves == 9 && (player1Score > player2Score || player2Score > player1Score));
}

template <typename T>
bool SUS_Board<T>::is_draw()
{
    // A draw occurs if the board is full and both players have the same score
    return (this->n_moves == 9 && player1Score == player2Score);
}

template <typename T>
bool SUS_Board<T>::game_is_over()
{
    // The game ends when there's a win or a draw
    return is_win() || is_draw();
}


template <typename T>
int SUS_Board<T>::getScore(int player) const
{
    return player == 1 ? player1Score : player2Score;
}

template <typename T>
SUS_Player<T>::SUS_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void SUS_Player<T>::getmove(int &x, int &y)
{
    cout << "\n"
         << this->name << " (" << this->symbol << "), enter your move (x y): ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
SUS_Random_Player<T>::SUS_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void SUS_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}

#endif //_3X3X_SUS_H
