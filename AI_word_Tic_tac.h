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

    T getBoardValue(int row, int col) const; // Get board value
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
T Tic_Tac_Toe_Minimax_Player<T>::getBoardValue(int row, int col) const {
    Tic_Tac_Toe_Board<T> board;
    if (!this->boardPtr) {
        cerr << "Error: Board not set!" << endl;
        return 0; // Default value
    }
    return board.getBoardValue(row,col); // Access value indirectly
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

    int bestScore = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (getBoardValue(i, j) == 0) { // Use indirect access
                updateBoard(i, j, this->symbol); // Simulate move
                int score = minimax(board, !isMaximizing);
                updateBoard(i, j, 0); // Undo move
                bestScore = isMaximizing ? std::max(bestScore, score) : std::min(bestScore, score);
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

    set<char> validSymbols = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
                              'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    char bestSymbol = 'A';
    int maxMatches = -1;

    for (char candidate : validSymbols) {
        int matches = 0;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (getBoardValue(i, j) == 0) { // Use indirect access
                    updateBoard(i, j, candidate); // Simulate move

                    // Check all rows for potential matches in the dictionary
                    for (int row = 0; row < 3; row++) {
                        string line;
                        for (int col = 0; col < 3; col++) {
                            T cellValue = getBoardValue(row, col);
                            if (cellValue != 0) {
                                line += cellValue;
                            }
                        }
                        if (find(dictionary.begin(), dictionary.end(), line) != dictionary.end()) {
                            matches++;
                        }
                    }

                    // Undo the move to evaluate the next position
                    updateBoard(i, j, 0);
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
    if (!ticTacToeBoard) {
        cerr << "Error: Board is not a Tic_Tac_Toe_Board!" << endl;
        x = y = -1;
        return;
    }

    int bestMoveScore = std::numeric_limits<int>::min();
    int bestX = -1, bestY = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (getBoardValue(i, j) == 0) { // Check empty positions
                updateBoard(i, j, this->symbol); // Simulate move
                int moveScore = minimax(*ticTacToeBoard, false);
                updateBoard(i, j, 0); // Undo the move

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