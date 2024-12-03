#include <iostream>
#include "BoardGame.hpp"
#include "BoardGame_Classes.h"
#include "Tic_Board.cpp"
#include "Player.cpp"
#include "RandomPlayer.cpp"
#include "GameManager.cpp"

using namespace std;

int main()
{
    int choice;
    Playern *players[2];
    players[0] = new Playern(1, 'x');
    Board1 *bord = new Tic_Board();
    cout << "Welcome to 5x5 X-O Game. :)\n";
    cout << "Choose Who Do You Want To Play Against\n1-Human\n2-Computer\n3-Ai Player \n";
    cin >> choice;
    if (choice == 1)
        players[1] = new Playern(2, 'o');
    else if (choice == 2)
        // Player pointer points to child
        players[1] = new RandomPlayer1('o', 5);
    else
    {
        players[1] = new AI(bord, 'o');
    }
    GameManager1 x_o_game(bord, players);
    x_o_game.run();
    // system("pause");
}
