#ifndef _ULTIMATE_TIC_TAC_TOE_H
#define _ULTIMATE_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <vector>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

template <typename T>
class Ultimate_Tic_Tac_Toe_Board : public Board<T> {
public:
    Ultimate_Tic_Tac_Toe_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();

private:
    bool sub_board_check(int subBoardIndex);
    bool check_rows(int subBoardIndex);
    bool check_columns(int subBoardIndex);
    bool check_diagonals(int subBoardIndex);

    
};

template <typename T>
class Ultimate_Tic_Tac_Toe_Player : public Player<T> {
public:
    Ultimate_Tic_Tac_Toe_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class Ultimate_Tic_Tac_Toe_Random_Player : public RandomPlayer<T> {
public:
    Ultimate_Tic_Tac_Toe_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

vector<char> checker(9, ' ');
vector<int> remove_index(9,11);

//----------------------Implementations--------------------

template <typename T>
Ultimate_Tic_Tac_Toe_Board<T>::Ultimate_Tic_Tac_Toe_Board() {
    this->rows = this->columns = 9;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool Ultimate_Tic_Tac_Toe_Board<T>::update_board(int x, int y, T symbol) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && this->board[x][y] == ' ') {
        this->board[x][y] = toupper(symbol);
        this->n_moves++;
        return true;
    }
    return false;
}

template <typename T>
void Ultimate_Tic_Tac_Toe_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
            if(j==2||j==5){
                cout<<"| ";
            }
        }
        cout << "\n---------------------------------------------------------------------------------------";
        if(i==2||i==5){

            cout << "\n---------------------------------------------------------------------------------------";
        }
    }
    cout << endl;
}

template <typename T>
bool Ultimate_Tic_Tac_Toe_Board<T>::is_win() {
    for(int k = 0; k < 9 &&remove_index[k]!=k ; k++){

        
        int startRow = (k / 3) * 3;
        int startCol = (k % 3) * 3;

        for (int i = startRow; i < startRow + 3; i++) {
            if (this->board[i][startCol] != ' ' &&
                this->board[i][startCol] == this->board[i][startCol + 1] &&
                this->board[i][startCol] == this->board[i][startCol + 2]) {
                checker[k]=this->board[i][startCol];
                remove_index[k]+=k;
                break;
            }
        }
        for (int j = startCol; j < startCol + 3; j++) {
            if (this->board[startRow][j] != ' ' &&
                this->board[startRow][j] == this->board[startRow + 1][j] &&
                this->board[startRow][j] == this->board[startRow + 2][j]) {
                checker[k]=this->board[startRow][j];
                remove_index[k]+=k;
                break;
            }
        }
            if (this->board[startRow][startCol] != ' ' &&
                this->board[startRow][startCol] == this->board[startRow + 1][startCol + 1] &&
                this->board[startRow][startCol] == this->board[startRow + 2][startCol + 2]) {
                checker[k]=this->board[startRow][startCol];
                remove_index[k]+=k;
                break;
            }

            // Check anti-diagonal
            if (this->board[startRow][startCol + 2] != ' ' &&
                this->board[startRow][startCol + 2] == this->board[startRow + 1][startCol + 1] &&
                this->board[startRow][startCol + 2] == this->board[startRow + 2][startCol]) {
                checker[k]=this->board[startRow][startCol+2];
                remove_index[k]+=k;
                break;
            }        

    
    }




    // Check rows and columns
    for (int i = 0; i < 7; i+=3) {
        if (checker[i]==checker[i+1]&& checker[i+1]==checker[i+2] && checker[i]!=' ') {
            

            return true;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (checker[i]==checker[i+3]&&checker[i+3]==checker[i+6]&&checker[i]!=' ') {

            return true;
        }
    }

    // Check diagonals
    if ((checker[0]==checker[4] && checker [4] ==checker[8] &&checker[0]!= ' ') ||
        (checker[2]==checker[4]&& checker[4] ==checker[7] && checker[2] != ' ')) {
        return true;
    }

    return false;
}

template <typename T>
bool Ultimate_Tic_Tac_Toe_Board<T>::is_draw() {
    return (this->n_moves == 81 && !is_win());
}

template <typename T>
bool Ultimate_Tic_Tac_Toe_Board<T>::game_is_over() {
    return is_win() || is_draw();
}




// Player constructor
template <typename T>
Ultimate_Tic_Tac_Toe_Player<T>::Ultimate_Tic_Tac_Toe_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Ultimate_Tic_Tac_Toe_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 8) separated by spaces: ";
    cin >> x >> y;
}

// Random player constructor
template <typename T>
Ultimate_Tic_Tac_Toe_Random_Player<T>::Ultimate_Tic_Tac_Toe_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 9;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed random number generator
}

template <typename T>
void Ultimate_Tic_Tac_Toe_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

#endif // _ULTIMATE_TIC_TAC_TOE_H
