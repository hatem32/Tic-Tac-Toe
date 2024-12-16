
#ifndef _PYRAMIDX_O_H
#define _PYRAMIDX_O_H

#include "BoardGame_Classes.h"

template <typename T>
class X_O_Board:public Board<T> {
public:
    X_O_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class X_O_Player : public Player<T> {
public:
    X_O_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class X_O_Random_Player : public RandomPlayer<T>{
public:
    X_O_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
X_O_Board<T>::X_O_Board() {
    this->rows = 3; this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool X_O_Board<T>::update_board(int x, int y, T mark) {
    // Check for valid cell
    if ((x < 0 || x >= this->rows || y < 0 || y >= this->columns) ||
        (x == 0 && (y == 0 || y == 1 || y == 3 || y == 4)) || 
        (x == 1 && (y == 0 || y == 4))) {
        return false; // Invalid cell
    }

    // If valid, update
    if (this->board[x][y] == 0 || mark == 0) {
        if (mark == 0) {
            this->n_moves--;
            this->board[x][y] = 0; // Undo move
        } else {
            this->n_moves++;
            this->board[x][y] = toupper(mark); // Place mark
        }
        return true;
    }
    return false;
}
template <typename T>
void X_O_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            if(i==0 && j==0||i==0 && j==1||i==0 && j==3||i==0 && j==4||i==1 && j==0||i==1 && j==4){
                cout<<"   ";
            cout << setw(2) << this->board[i][j] << " |";
            continue;
            }
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

template <typename T>
bool X_O_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        // Skip invalid rows for special cells
        if (this->board[i][2] != 0 &&
            this->board[i][2] == this->board[i][1] &&
            this->board[i][2] == this->board[i][3]) {
            return true; // Row win
        }
    }

    // Diagonals
    if (this->board[0][2] != 0 &&
        ((this->board[0][2] == this->board[1][3] && this->board[0][2] == this->board[2][4]) || 
         (this->board[0][2] == this->board[1][1] && this->board[0][2] == this->board[2][0]))) {
        return true; // Diagonal win
    }
    return false;
}

template <typename T>
bool X_O_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool X_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
X_O_Player<T>::X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void X_O_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    if(x==0&&y==0||x==0&&y==1||x==0 &&y==3||x==1&&y==0||x==1&&y==4||x==0&&y==4){
        cout<<"Invalid move. Please choose a different position."<<endl;
        getmove(x,y);
    }
}

// Constructor for X_O_Random_Player
template <typename T>
X_O_Random_Player<T>::X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void X_O_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % 5;
    if(x==0&&y==0||x==0&&y==1||x==0 &&y==3||x==1&&y==0||x==1&&y==4||x==0&&y==4){
        getmove(x,y);
    }
}







#endif //_3X3X_O_H
