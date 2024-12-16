#ifndef _wordTic_Tac_H
#define _wordTic_Tac_H

#include "BoardGame_Classes.h"
template <typename T>
class Tic_Tac_Toe_Board:public Board<T> {
public:
    Tic_Tac_Toe_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    T getBoardValue(int row, int col) const; // Get board value

};
template <typename T>
T Tic_Tac_Toe_Board<T>::getBoardValue(int row, int col) const {

    return this->board[row][col]; // Access value indirectly
}

template <typename T>
class Tic_Tac_Toe_Player : public Player<T> {
public:
    Tic_Tac_Toe_Player (string name, T symbol);
    void getmove(int& x, int& y) ;
    T getsymbol();

};

template <typename T>
class Tic_Tac_Toe_Random_Player : public RandomPlayer<T>{
public:
    Tic_Tac_Toe_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
    T getsymbol();
};


#include <fstream>
#include <cctype>
#include <map>
#include <iomanip>
#include <algorithm>
using namespace std;
int indexStart(char c){
    map<const char,int> map1={{ 'A',0} , { 'B',110} , { 'C',214} , { 'D',268} , { 'E',375} , { 'F',498} , { 'G',559} , { 'H',661} ,
    { 'I',734} , { 'J',770} , { 'K',796} , { 'L',840} , { 'M',916} , { 'N',1012} , { 'O',1115} , { 'P',1191} ,
    { 'Q',1311} , { 'R',1314} , { 'S',1401} , { 'T',1533} , { 'U',1674} , { 'V',1706} , { 'W',1735} , { 'X',1812} ,
    { 'Y',1845} , { 'Z',1925}};
    return map1[c];
}

// Constructor for Tic_Tac_Toe_Board
template <typename T>
Tic_Tac_Toe_Board<T>::Tic_Tac_Toe_Board() {
    this->rows = this->columns = 3;
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
bool Tic_Tac_Toe_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

template <typename T>
void Tic_Tac_Toe_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}
template <typename T>
bool Tic_Tac_Toe_Board<T>::is_win() {
    vector<string> dic_vector;
    string str;

    // Open the dictionary file
    ifstream inputFile("text.txt");
    if (!inputFile) {
        cerr << "Error opening dictionary file!" << endl;
        return false; // Cannot determine win without a dictionary
    }

    // Load the dictionary into dic_vector
    while (inputFile >> str) {
        dic_vector.push_back(str);
    }
    inputFile.close(); // Close the file

    // Validate that the dictionary is not empty
    if (dic_vector.empty()) {
        cerr << "Dictionary is empty!" << endl;
        return false;
    }

    // Lambda to validate characters
    auto isValidChar = [](char c) {
        return c >= 'A' && c <= 'Z';
    };

    // Check the two diagonals
    if (isValidChar(this->board[0][0]) && isValidChar(this->board[1][1]) && isValidChar(this->board[2][2])) {
        for (int k = indexStart(this->board[0][0]); k < dic_vector.size(); k++) {
            if (dic_vector[k].size() >= 3 &&
                this->board[0][0] == dic_vector[k][0] &&
                this->board[1][1] == dic_vector[k][1] &&
                this->board[2][2] == dic_vector[k][2]) {
                return true;
            }
        }
    }

    if (isValidChar(this->board[0][2]) && isValidChar(this->board[1][1]) && isValidChar(this->board[2][0])) {
        for (int k = indexStart(this->board[0][2]); k < dic_vector.size(); k++) {
            if (dic_vector[k].size() >= 3 &&
                this->board[0][2] == dic_vector[k][0] &&
                this->board[1][1] == dic_vector[k][1] &&
                this->board[2][0] == dic_vector[k][2]) {
                return true;
            }
        }
    }

    // Check rows
    for (int i = 0; i < this->rows; i++) {
        if (isValidChar(this->board[i][0]) && isValidChar(this->board[i][1]) && isValidChar(this->board[i][2])) {
            for (int j = indexStart(this->board[i][0]); j < dic_vector.size(); j++) {
                if (dic_vector[j].size() >= 3 &&
                    this->board[i][0] == dic_vector[j][0] &&
                    this->board[i][1] == dic_vector[j][1] &&
                    this->board[i][2] == dic_vector[j][2]) {
                    return true;
                }
            }
        }
    }

    // Check columns
    for (int i = 0; i < this->columns; i++) {
        if (isValidChar(this->board[0][i]) && isValidChar(this->board[1][i]) && isValidChar(this->board[2][i])) {
            for (int j = indexStart(this->board[0][i]); j < dic_vector.size(); j++) {
                if (dic_vector[j].size() >= 3 &&
                    this->board[0][i] == dic_vector[j][0] &&
                    this->board[1][i] == dic_vector[j][1] &&
                    this->board[2][i] == dic_vector[j][2]) {
                    return true;
                }
            }
        }
    }

    return false;
}



// Return true if 9 moves are done and no winner
template <typename T>
bool Tic_Tac_Toe_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Tic_Tac_Toe_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//-------------------

// Constructor for Tic_Tac_Toe_Player
template <typename T>
Tic_Tac_Toe_Player<T>::Tic_Tac_Toe_Player(string name, T symbol) : Player<T>(name, symbol) {}


template <typename T>
T Tic_Tac_Toe_Player<T>::getsymbol() {
    char symbol2;
    cout<<"\nPlease enter your character symbol:";
    cin>>symbol2;
    while(!isalpha(symbol2)){
        cout<<"Invalid input. Please enter a letter (A ~ Z): ";
        cin>>symbol2;
    }
    this->symbol=toupper(symbol2);
    return this->symbol;
}
template <typename T>
void Tic_Tac_Toe_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    char symbol2;
    getsymbol();
}


// Constructor for Tic_Tac_Toe_Random_Player
template <typename T>
Tic_Tac_Toe_Random_Player<T>::Tic_Tac_Toe_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Tic_Tac_Toe_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
    string str={"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    this->symbol = str[ rand() % 26];

}

template <typename T>
T Tic_Tac_Toe_Random_Player<T>::getsymbol() {
    string str={"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    this->symbol = str[ rand() % 26];
    return this->symbol;
}






#endif