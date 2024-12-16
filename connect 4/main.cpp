#include <iostream>
#include <cstdlib>
#include <ctime>
#include "ConnectFourBoard.h"
#include "BoardGame_Classes.h"

using namespace std;

int main() {
    cout << "Welcome to Connect Four!" << endl;
    cout << "Choose Game Mode:\n";
    cout << "1. Player vs Player\n";
    cout << "2. Player vs Random Computer\n";
    cout << "3. Player vs AI (MinMax)\n";  
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    while (choice != 1 && choice != 2 && choice != 3) {  // Validate input for new option
        cout << "Invalid choice. Please enter 1, 2, or 3: ";
        cin >> choice;
    }

    // Create the board
    ConnectFourBoard<char> board;

    // Create players
    Player<char>* players[2];
    string name1, name2;

    if (choice == 1) {
        // Player vs Player
        cout << "Enter Player 1's name: ";
        cin >> name1;
        cout << "Enter Player 2's name: ";
        cin >> name2;
        players[0] = new ConnectFourPlayer<char>(name1, 'X');
        players[1] = new ConnectFourPlayer<char>(name2, 'O');
    } else if (choice == 2) {
        // Player vs Random Computer
        cout << "Enter Player 1's name: ";
        cin >> name1;
        players[0] = new ConnectFourPlayer<char>(name1, 'X');
        players[1] = new ConnectFourRandomPlayer<char>('O');
    } else {
        // Player vs AI (MinMax)
        cout << "Enter Player 1's name: ";
        cin >> name1;
        players[0] = new ConnectFourPlayer<char>(name1, 'X');
        players[1] = new ConnectFourAiPlayer<char>('O');

    }

    // Set the board for both players
    players[0]->setBoard(&board);
    players[1]->setBoard(&board);

    // Create the game manager
    GameManager<char> gameManager(&board, players);

    // Start the game
    gameManager.run();

    // Clean up dynamic memory
    delete players[0];
    delete players[1];

    return 0;
}
