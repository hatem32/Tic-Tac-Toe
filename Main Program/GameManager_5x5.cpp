#include <iostream>
#include "5x5.hpp"
using namespace std;

GameManager1::GameManager1(Board5 *bPtr, Playern *playerPtr[2])
{
    boardPtr = bPtr;
    players[0] = playerPtr[0];
    players[1] = playerPtr[1];
}

void GameManager1::run()
{
    int x, y, n = 0;

    boardPtr->display_board1();

    while (!boardPtr->game_is_over1())
    {

        for (int i : {0, 1})
        {
            n++;
            players[i]->get_move(x, y);
            while (!boardPtr->update_board1(x, y, players[i]->get_symbol()))
            {
                players[i]->get_move(x, y);
            }
            boardPtr->display_board1();
            if (n >= 24)
            {
                if (boardPtr->checkGrid1() == 1)
                {
                    cout << players[0]->to_string() << " wins\n";
                    return;
                }
                else if (boardPtr->checkGrid1() == 2)
                {
                    cout << players[1]->to_string() << " wins\n";
                    return;
                }
                else
                    boardPtr->is_draw1();
            }
        }
    }
}
