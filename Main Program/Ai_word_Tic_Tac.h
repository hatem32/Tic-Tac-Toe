#ifndef _AI_TIC_TAC_H
#define _AI_TIC_TAC_H

#include "BoardGame_Classes.h"
#include "wordTic_Tac.h"



//----------------------------------------------------------------
//Implementation

#include <algorithm>
#include <limits>
#include <set>
// Minimax algorithm constants
const int AI_WIN = 10;
const int PLAYER_WIN = -10;
const int DRAW = 0;

template <typename T>
class Tic_Tac_Toe_Minimax_Player : public Player<T> {
public:
    Tic_Tac_Toe_Minimax_Player(string name, T symbol);

    void getmove(int &x, int &y) override;
    T getsymbol();
    void setBoard(Board<T>* b);

    T getBoardValue2(int row, int col) const; // Get board value
    void updateBoard(int row, int col, T value); // Update board value

private:
    int minimax(Tic_Tac_Toe_Board<T>& board, bool isMaximizing);
    bool is_moves_left(Tic_Tac_Toe_Board<T>& board);
};

template <typename T>
void Tic_Tac_Toe_Minimax_Player<T>::setBoard(Board<T>* b) {
    this->boardPtr = b;
}

template <typename T>
T Tic_Tac_Toe_Minimax_Player<T>::getBoardValue2(int row, int col) const {
    Tic_Tac_Toe_Board<T> board;  // This creates a NEW board, not the game board
    if (!this->boardPtr) {
        cerr << "Error: Board not set!" << endl;
        return 0;
    }
    return board.getBoardValue(row,col); // This will NOT work as expected
}

template <typename T>
void Tic_Tac_Toe_Minimax_Player<T>::updateBoard(int row, int col, T value) {
    if (!this->boardPtr) {
        cerr << "Error: Board not set!" << endl;
        return;
    }
    this->boardPtr->update_board(row, col, value); // Update value indirectly
}


template <typename T>
Tic_Tac_Toe_Minimax_Player<T>::Tic_Tac_Toe_Minimax_Player(string name, T symbol)
    : Player<T>(name, symbol) {}

// Minimax Logic
template <typename T>
int Tic_Tac_Toe_Minimax_Player<T>::minimax(Tic_Tac_Toe_Board<T>& board, bool isMaximizing) {
        if (board.is_win()) {
            return isMaximizing ? PLAYER_WIN : AI_WIN;
        }

        if (board.is_draw()) {
            return DRAW;
        }

        int bestScore = isMaximizing ? numeric_limits<int>::min() : numeric_limits<int>::max();

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board.getBoardValue(i, j) == 0) {
                    board.update_board(i, j, this->symbol);
                    int score = minimax(board, !isMaximizing);
                    board.update_board(i, j, 0); // Undo move

                    bestScore = isMaximizing
                        ? max(bestScore, score)
                        : min(bestScore, score);
                }
            }
        }

        return bestScore;
}

// Find the best move for the AI

template <typename T>
T Tic_Tac_Toe_Minimax_Player<T>::getsymbol() {
    vector<string> dictionary;
    ifstream inputFile("text.txt");
    if (!inputFile) {
        cerr << "Error opening dictionary file!" << endl;
        return 'A'; // Default fallback
    }

    // Load dictionary into a vector
    string word;
    while (inputFile >> word) {
        dictionary.push_back(word);
    }


    set<char> validSymbols={'A','B','C', 'D','E','F', 'G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};



    char bestSymbol = 'A';
    int maxMatches = -1;


    for (char candidate : validSymbols) {
        int matches = 0;


        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (getBoardValue2(i,j) == 0) {
                    this->boardPtr->update_board(i, j, candidate);


                    string line;
                    for (int row = 0; row < 3; row++) {
                        for (int col = 0; col < 3; col++) {
                            if (getBoardValue2(row,col)!= 0) {
                                line += getBoardValue2(row,col);
                            }
                        }
                        // If line exists in the dictionary, count it
                        if (find(dictionary.begin(), dictionary.end(), line) != dictionary.end()) {
                            matches++;
                        }
                    }

                    // Undo the move to evaluate the next position
                    this->boardPtr->update_board(i, j, 0);
                }
            }
        }

        // Update the best symbol if this candidate results in more matches
        if (matches > maxMatches) {
            maxMatches = matches;
            bestSymbol = candidate;
        }
    }

    this->symbol = bestSymbol;
    return bestSymbol;
}
template <typename T>
void Tic_Tac_Toe_Minimax_Player<T>::getmove(int& x, int& y) {
    getsymbol(); // Choose the best letter based on the dictionary

    Tic_Tac_Toe_Board<char>* ticTacToeBoard = dynamic_cast<Tic_Tac_Toe_Board<char>*>(this->boardPtr);
       // Ensure board is set
        if (!this->boardPtr) {
            cerr << "Error: Board not set!" << endl;
            x = y = -1;
            return;
        }

        // Cast to the specific board type
        Tic_Tac_Toe_Board<T>* board = dynamic_cast<Tic_Tac_Toe_Board<T>*>(this->boardPtr);
        if (!board) {
            cerr << "Error: Invalid board type!" << endl;
            x = y = -1;
            return;
        }

        int bestMoveScore = numeric_limits<int>::min();
        int bestX = -1, bestY = -1;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // Use board directly instead of getBoardValue2
                if (board->getBoardValue(i, j) == 0) {
                    board->update_board(i, j, this->symbol);
                    int moveScore = minimax(*board, false);
                    board->update_board(i, j, 0); // Undo move

                    if (moveScore > bestMoveScore) {
                        bestMoveScore = moveScore;
                        bestX = i;
                        bestY = j;
                    }
                }
            }
        }

        x = bestX;
        y = bestY;
}




#endif