#include <iostream>
#include <random>
#include <iomanip>
#include <algorithm>
#include <climits>
#include "BoardGame.hpp"
using namespace std;
int Tic_Board::is_moves_left1()
{
    return n_moves - 24;
}
Tic_Board::Tic_Board()
{
    n_rows = n_cols = 5;
    board = new char *[n_rows];
    for (int i = 0; i < n_rows; i++)
    {
        board[i] = new char[n_cols];
        for (int j = 0; j < n_cols; j++)
            board[i][j] = 0;
    }
}

bool Tic_Board::update_board1(int x, int y, char mark)
{
    // Only update if move is valid
    if (!(x < 0 || x > 4 || y < 0 || y > 4) && (board[x][y] == 0))
    {
        board[x][y] = toupper(mark);
        n_moves++;
        return true;
    }
    else
        return false;
}

void Tic_Board::display_board1()
{
    for (int i : {0, 1, 2, 3, 4})
    {
        cout << "\n|";
        for (int j : {0, 1, 2, 3, 4})
        {
            if (board[i][j] == 0)
                cout << setw(2) << "(" << i << "," << j << ")" << setw(2)
                     << " |";
            else
                cout << setw(2) << "   " << board[i][j] << "   "
                     << "|";
        }
        cout << "\n------------------------------------------";
    }
    cout << endl;
}

int Tic_Board::is_winner1(int a, int b, char symb)
{

    int row_win[3] = {0, 0, 0}, col_win[3] = {0, 0, 0}, diag_win[2] = {0, 0};
    for (int i : {0, 1, 2})
    {
        if ((board[i + a][0 + b] == board[i + a][1 + b]) && (board[i + a][1 + b] == board[i + a][2 + b]) && (board[i + a][2 + b] == symb))
            row_win[i]++;

        if ((board[0 + a][i + b] == board[1 + a][i + b]) && (board[1 + a][i + b] == board[2 + a][i + b]) && (board[2 + a][i + b] == symb))

            col_win[i]++;
    }
    if (((board[0 + a][0 + b] == board[1 + a][1 + b]) && (board[1 + a][1 + b] == board[2 + a][2 + b]) && (board[2 + a][2 + b] == symb)))
        diag_win[0]++;
    if (((board[2 + a][0 + b] == board[1 + a][1 + b]) && (board[1 + a][1 + b] == board[0 + a][2 + b]) && (board[0 + a][2 + b] == symb)))
        diag_win[1]++;
    int sum = 0;
    for (int k : {0, 1, 2})
        sum += row_win[k] + col_win[k];
    sum += diag_win[0] + diag_win[1];
    return sum;
}
int Tic_Board::checkGrid1()
{
    int p1_wins = 0;
    int p2_wins = 0;
    // Check each 3x3 section
    for (int i = 0; i <= 2; ++i)
    {
        for (int j = 0; j <= 2; ++j)
        {
            p1_wins += is_winner1(i, j, 'X');
            p2_wins += is_winner1(i, j, 'O');
        }
    }
    if (p1_wins > p2_wins)
        return 1;
    else if (p1_wins < p2_wins)
        return 2;
    else
    {
        return 3;
    }
}
bool Tic_Board::is_draw1()
{
    cout << "----\nDraw\n----";
    return true;
}
bool Tic_Board::game_is_over1()
{
    return n_moves >= 24;
}
int Tic_Board::check_status1()
{
    int p1_win = 0;
    int p2_win = 0;
    // Check each 3x3 section
    for (int i = 0; i <= 2; ++i)
    {
        for (int j = 0; j <= 2; ++j)
        {
            if (board[i][j] == 0)
                return 1;
            p1_win += is_winner1(i, j, 'X');
            p2_win += is_winner1(i, j, 'O');
        }
    }
    if (p1_win > p2_win)
    {
        return (p1_win - p2_win) * 10;
    }
    else if (p2_win > p1_win)
        return -10 * (p2_win - p1_win);
    else
        return 1;
}
int Tic_Board::minimax1(int &x, int &y, bool isMaximizing, bool first_time, int depth)
{
    int result = check_status1();
    int final_i, final_j;
    if (depth == 0)
    {

        return result;
    }

    int max_score = INT_MIN, min_score = INT_MAX;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (board[i][j] == 0)
            {
                if (isMaximizing)
                {
                    board[i][j] = 'X';
                    int score = minimax1(x, y, false, false, depth - 1);
                    if (score >= max_score)
                    {
                        max_score = score;
                        final_i = i;
                        final_j = j;
                    }
                    board[i][j] = 0;
                }

                else
                {
                    board[i][j] = 'O';
                    int score = minimax1(x, y, true, false, depth - 1);

                    if (score <= min_score)
                    {
                        min_score = score;
                        final_i = i;
                        final_j = j;
                    }
                    board[i][j] = 0;
                }
            }
        }
    }
    if (first_time)
    {
        x = final_i, y = final_j;
    }
    if (isMaximizing)
        return max_score;
    else
        return min_score;
}