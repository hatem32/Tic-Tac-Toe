#ifndef _NUMERICAL_TICTACTOE_H
#define _NUMERICAL_TICTACTOE_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "BoardGame_Classes.h"
 

template <typename T>
class Playerr {
protected:
    std::string name;
    T symbol;
    int sum; // Track the sum of the numbers chosen by the Playerr

public:
    Playerr(std::string name, T symbol) : name(name), symbol(symbol), sum(0) {}
    virtual ~Playerr() {}

    std::string get_name() const { return name; }
    T get_symbol() const { return symbol; }
    int get_sum() const { return sum; }

    void add_to_sum(T number) {
        sum += number;
    }

    virtual void getmove(int& x, int& y) = 0;

    virtual bool has_won() const {
        return sum == 15; // Playerr wins if their sum of numbers equals 15
    }
};

// Numerical TicTacToe Board
template <typename T>
class NumericalTicTacToeBoard {
private:
    T board[3][3];

public:
    NumericalTicTacToeBoard() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                board[i][j] = 0;  // Initialize all cells to 0 (empty)
            }
        }
    }

    void display_board() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == 0) {
                    std::cout << " . ";
                } else {
                    std::cout << " " << board[i][j] << " ";
                }
                if (j < 2) std::cout << "|";
            }
            std::cout << std::endl;
            if (i < 2) std::cout << "-------------" << std::endl;
        }
    }

    bool is_valid_move(int x, int y) {
        return x >= 0 && x < 3 && y >= 0 && y < 3 && board[x][y] == 0;
    }

    bool update_board(int x, int y, T number) {
        if (is_valid_move(x, y)) {
            board[x][y] = number;
            return true;
        }
        return false;
    }

    bool is_full() const {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == 0) {
                    return false;
                }
            }
        }
        return true;
    }
};

// NumericalPlayer Class (Human Playerr)
template <typename T>
class NumericalPlayer : public Playerr<T> {
private:
    NumericalTicTacToeBoard<T>* boardPtr;  // Pointer to the board
    std::vector<T> available_numbers;

public:
    NumericalPlayer(std::string name, T symbol) : Playerr<T>(name, symbol), boardPtr(nullptr) {
        // Initialize available numbers based on the Playerr's symbol
        available_numbers = (symbol % 2 == 1)
                            ? std::vector<T>{1, 3, 5, 7, 9}
                            : std::vector<T>{2, 4, 6, 8};
    }

    void set_board(NumericalTicTacToeBoard<T>* board) {
        boardPtr = board;
    }

    void getmove(int& x, int& y) override {
        bool valid_move = false;
        T chosen_number;

        while (!valid_move) {
            std::cout << this->name << ", choose a number from the available ones: ";
            for (T num : available_numbers) {
                std::cout << num << " ";
            }
            std::cout << std::endl;

            std::cin >> chosen_number;

            if (std::find(available_numbers.begin(), available_numbers.end(), chosen_number) != available_numbers.end()) {
                std::cout << "Enter your move (row and column): ";
                std::cin >> x >> y;

                if (boardPtr && boardPtr->is_valid_move(x, y)) {
                    // Update board and remove the number from available_numbers
                    boardPtr->update_board(x, y, chosen_number);
                    available_numbers.erase(std::remove(available_numbers.begin(), available_numbers.end(), chosen_number), available_numbers.end());
                    this->add_to_sum(chosen_number); // Add the number to the Playerr's total sum
                    valid_move = true;
                }
                else {
                    std::cout << "Invalid move. Please try again." << std::endl;
                }
            }
            else {
                std::cout << "Invalid number. Please choose a valid one." << std::endl;
            }
        }
    }

    T get_symbol() { return this->symbol; }
};

// NumericalRandomPlayer Class (Computer Playerr)
template <typename T>
class NumericalRandomPlayer : public Playerr<T> {
private:
    NumericalTicTacToeBoard<T>* boardPtr;  // Pointer to the board
    std::vector<T> available_numbers;

public:
    NumericalRandomPlayer(T symbol) : Playerr<T>("Random Playerr", symbol), boardPtr(nullptr) {
        // Initialize available numbers based on the Playerr's symbol
        available_numbers = (symbol % 2 == 1)
                            ? std::vector<T>{1, 3, 5, 7, 9}
                            : std::vector<T>{2, 4, 6, 8};
        srand(static_cast<unsigned int>(time(0))); // Seed RNG
    }

    void set_board(NumericalTicTacToeBoard<T>* board) {
        boardPtr = board;
    }

    void getmove(int& x, int& y) override {
        std::vector<std::pair<int, int>> valid_moves;

        // Collect all valid moves (empty spots on the board)
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (boardPtr->is_valid_move(i, j)) {
                    valid_moves.push_back({i, j});
                }
            }
        }

        if (!valid_moves.empty() && !available_numbers.empty()) {
            // Randomly select a valid move
            int random_index = rand() % valid_moves.size();
            x = valid_moves[random_index].first;
            y = valid_moves[random_index].second;

            // Randomly select a number from the available ones
            int random_num_index = rand() % available_numbers.size();
            T chosen_number = available_numbers[random_num_index];

            // Apply the selected move to the board
            if (boardPtr->update_board(x, y, chosen_number)) {
                // Remove the chosen number from available numbers
                available_numbers.erase(available_numbers.begin() + random_num_index);
                this->add_to_sum(chosen_number); // Add the number to the Playerr's total sum
                std::cout << this->name << " chooses number " << chosen_number << " at (" << x << ", " << y << ")" << std::endl;
            }
        } else {
            std::cout << "No valid moves left!" << std::endl;
        }
    }
};

// NumericalAIPlayer Class (AI Playerr)
template <typename T>
class NumericalAIPlayer : public Playerr<T> {
private:
    NumericalTicTacToeBoard<T>* boardPtr;  // Pointer to the board
    std::vector<T> available_numbers;

public:
    NumericalAIPlayer(T symbol) : Playerr<T>("AI Playerr", symbol), boardPtr(nullptr) {
        // Initialize available numbers based on the Playerr's symbol
        available_numbers = (symbol % 2 == 1)
                            ? std::vector<T>{1, 3, 5, 7, 9}
                            : std::vector<T>{2, 4, 6, 8};
        srand(static_cast<unsigned int>(time(0))); // Seed RNG
    }

    void set_board(NumericalTicTacToeBoard<T>* board) {
        boardPtr = board;
    }

    void getmove(int& x, int& y) override {
        std::vector<std::pair<int, int>> valid_moves;

        // Collect all valid moves (empty spots on the board)
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (boardPtr->is_valid_move(i, j)) {
                    valid_moves.push_back({i, j});
                }
            }
        }

        if (!valid_moves.empty() && !available_numbers.empty()) {
            // Randomly select a valid move
            int random_index = rand() % valid_moves.size();
            x = valid_moves[random_index].first;
            y = valid_moves[random_index].second;

            // Randomly select a number from the available ones
            int random_num_index = rand() % available_numbers.size();
            T chosen_number = available_numbers[random_num_index];

            // Apply the selected move to the board
            if (boardPtr->update_board(x, y, chosen_number)) {
                // Remove the chosen number from available numbers
                available_numbers.erase(available_numbers.begin() + random_num_index);
                this->add_to_sum(chosen_number); // Add the number to the Playerr's total sum
                std::cout << this->name << " chooses number " << chosen_number << " at (" << x << ", " << y << ")" << std::endl;
            }
        } else {
            std::cout << "No valid moves left!" << std::endl;
        }
    }
};

#endif // _NUMERICAL_TICTACTOE_H
