#ifndef _BoardGame_CLASSES_H
#define _BoardGame_CLASSES_H
using namespace std;
#include <string>
#include "BoardGame_Classes.h"


class Board5
{
protected:
    int n_rows, n_cols;
    char **board;
    int n_moves = 0;

public:
    // Return true  if move is valid and put it on board
    // within board boundaries in empty cell
    // Return false otherwise
    virtual bool update_board1(int x, int y, char symbol) = 0;
    // Returns true if there is any winner
    // either X or O
    // Written in a complex way. DO NOT DO LIKE THIS.
    virtual int is_winner1(int a, int b, char symb) = 0;
    // Return true if all moves are done and no winner
    virtual bool is_draw1() = 0;
    // Display the board and the pieces on it
    virtual void display_board1() = 0;
    // Return true if game is over
    virtual bool game_is_over1() = 0;
    virtual int checkGrid1() = 0;
    virtual int minimax1(int &x, int &y, bool isMaximizing, bool first_time, int depth) = 0;
    virtual int check_status1() = 0;
    virtual int is_moves_left1() = 0;
};

class Tic_Board : public Board5
{
public:
    Tic_Board();
    ~Tic_Board();
    bool update_board1(int x, int y, char mark);
    int is_winner1(int a, int b, char symb);
    bool is_draw1();
    bool game_is_over1();
    int checkGrid1();
    void display_board1();
    int minimax1(int &x, int &y, bool isMaximizing, bool first_time, int depth);
    int check_status1();
    bool is_valid(int x, int y);
    int is_moves_left1();
};

///////////////////////////////////////////
// This class represents a player who has
// a name and a symbol to put on board
class Playern
{
protected:
    string name;
    char symbol;

public:
    // Two constructors to initiate player
    // Give player a symbol to use in playing
    // It can be X or O or others
    // Optionally, you can give him ID or order
    // Like Player 1 and Player 2
    Playern(char symbol); // Needed for computer players
    Playern(int order, char symbol);
    // Get desired move: x y (each between 0 and 2)
    // Virtual (can change for other player types)
    virtual void get_move(int &x, int &y);
    // Give player info as a string
    string to_string();
    // Get symbol used by player
    char get_symbol();
};

///////////////////////////////////////////
// This class represents a random computer player
// that generates random positions x y (0 to 2)
// If invalid, game manager asks to regenerate
class RandomPlayer1 : public Playern
{
protected:
    int dimension;

public:
    // Take a symbol and pass it to parent
    RandomPlayer1(char symbol, int dimension);
    // Generate a random move
    void get_move(int &x, int &y);
};

///////////////////////////////////////////
class GameManager1
{
private:
    Board5 *boardPtr;
    Playern *players[2];

public:
    GameManager1(Board5 *, Playern *playerPtr[2]);
    void run();
    // This method creates board and players
    // It displays board
    // While True
    //   For each player
    //      It takes a valid move as x, y pair (between 0 - 2)
    //      It updates board and displays otit
    //      If winner, declare so and end
    //      If draw, declare so and end
};
class AI : public Playern
{
private:
    Board5 *board;

public:
    AI(Board5 *board, char symb) : Playern(symb)
    {
        this->board = board;
        this->name = "AI Player";
        cout << "My Name Is " << this->name << endl;
    }
    void get_move(int &x, int &y)
    {
        board->minimax1(x, y, false, true, 5);
    }
};
#endif
