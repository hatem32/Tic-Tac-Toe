#ifndef _MISERE_XO_H
#define _MISERE_XO_H

#include <string>
#include <vector>


using namespace std;

template <typename T>
class Board1 {
protected:
    int rows, columns;
    T** board;
    int n_moves = 0;

public:


    /// Return true if move is valid and put it on the board
    /// within board boundaries in an empty cell
    /// Return false otherwise
    virtual bool update__board(int x, int y, T symbol) = 0;

    /// Display the board and the pieces on it
    virtual void display__board() = 0;

    /// Returns true if there is any winner
    virtual bool is__win() = 0;

    /// Return true if all moves are done and no winner
    virtual bool is__draw() = 0;

    /// Return true if the game is over
    virtual bool game__is_over() = 0;
};

template <typename T>
class Playerx {
protected:
    string name;
    T symbol;
    Board1<T>* boardPtr;  // Pointer to the board
public:
    /// Two constructors to initiate players
    /// Give the player a symbol to use in playing
    /// It can be X, O, or others
    /// Optionally, you can give them a name
    Playerx(string n, T symbol);
    Playerx(T symbol); // For computer players

    virtual void getmove(int& x, int& y) = 0;
    T getsymbol();
    string getname();
    void setBoardx(Board1<T>* b);
};

/// This class represents a random computer player
/// that generates random positions x, y
/// If invalid, the game manager asks to regenerate
template <typename T>
class RandomPlayer2 : public Playerx<T> {
protected:
    int dimension;
public:
    // Take a symbol and pass it to the parent
    RandomPlayer2(T symbol);
    // Generate a random move
    virtual void getmove(int& x, int& y) = 0;
};

template <typename T>
class GameManger {
private:
    Board1<T>* boardPtr;
    Playerx<T>* players[2];
public:
    GameManger(Board1<T>*, Playerx<T>* playerPtr[2]);

    void run();
};


//--------------------------------------- IMPLEMENTATION

#include <iostream>
using namespace std;

template <typename T>
GameManger<T>::GameManger(Board1<T>* bPtr, Playerx<T>* playerPtr[2]) {
    boardPtr = bPtr;
    players[0] = playerPtr[0];
    players[1] = playerPtr[1];
}

template <typename T>
void GameManger<T>::run() {
    int x, y;

    boardPtr->display__board();

    while (!boardPtr->game__is_over()) {
        for (int i : {0, 1}) {
            players[i]->getmove(x, y);
            while (!boardPtr->update__board(x, y, players[i]->getsymbol())) {
                players[i]->getmove(x, y);
            }
            boardPtr->display__board();
            if (boardPtr->is__win()) {
                cout << players[1-i]->getname() << " wins\n";
                return;
            }
            if (boardPtr->is__draw()) {
                cout << "Draw!\n";
                return;
            }
        }
    }
}


using namespace std;
// Constructor for Player with a name and symbol
template <typename T>
Playerx<T>::Playerx(std::string n, T symbol) {
    this->name = n;
    this->symbol = symbol;
}

// Constructor for Player with only a symbol (e.g., for computer players)
template <typename T>
Playerx<T>::Playerx(T symbol) {
    this->name = "Computer";
    this->symbol = symbol;
}

// Constructor for RandomPlayer, passing the symbol to the parent Player class
template <typename T>
RandomPlayer2<T>::RandomPlayer2(T symbol) : Playerx<T>(symbol) {}

// Getter for player's name
template <typename T>
std::string Playerx<T>::getname() {
    return this->name;
}

// Getter for player's symbol
template <typename T>
T Playerx<T>::getsymbol() {
    return this->symbol;
}

// Method to set the board pointer in the Player class
template <typename T>
void Playerx<T>::setBoardx(Board1<T>* b) {
    this->boardPtr = b;
}
















#endif //_MISERE_XO_H
