#include <iostream>
#include "BoardGame_Classes.h"
#include "Misere_X_O.h"
#include "Misere.h"
#include "Ai_Misere.h"


using namespace std;

int main() {
    int choice;
    Playerx<char>* players[2];
    Misere_Board<char>* B = new Misere_Board<char>();
    string playerXName, player2Name;

    cout << "Welcome to Misere X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Ai Player\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new Misere_Player<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new X_O_RandomPlayer<char>('X');
            break;
        case 3:
            players[0] = new X_O_MinMaxPlayer<char>('X');
            players[0]->setBoardx(B);
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Ai Player\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new Misere_Player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new X_O_RandomPlayer<char>('O');
            break;
        case 3:
            players[1] = new X_O_MinMaxPlayer<char>('O');
            players[1]->setBoardx(B);
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return 1;
    }

    // Create the game manager and run the game
    GameManger<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}


