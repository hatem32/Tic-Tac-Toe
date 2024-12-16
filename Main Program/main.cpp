#include <iostream>
#include "NumericalTicTacToe.h"
#include "Ultimate_Tic_Tac_Toe.h"
#include "PyramidX_O.h"
#include "AI_PyramidXO.h"
#include "5x5.hpp"
#include "Tic_Board_5x5.cpp"
#include "Player_5x5.cpp"
#include "RandomPlayer_5x5.cpp"
#include "GameManager_5x5.cpp"
#include "Misere_X_O.h"
#include "Misere.h"
#include "Ai_Misere.h"
#include "SUS.h"
#include "wordTic_Tac.h"
#include "Ai_word_Tic_Tac.h"
#include "ConnectFourBoard.h"
#include "MinMaxPlayer.h"
#include "BoardGame_Classes.h"

using namespace std;

int main()
{
    int choice;

    do
    {
        cout << "Welcome to Tic Tac Toe Games:\n\n";
        cout << "1. Pyramid X_O\n";
        cout << "2. Four in a row\n";
        cout << "3. 5x5 X_O\n";
        cout << "4. Word\n";
        cout << "5. Numerical\n";
        cout << "6. Misere X_O\n";
        cout << "7. Ultimate\n";
        cout << "8. SUS\n";
        cout << "9. Exit\n";
        cout << "Enter your choice : ";
        cin >> choice;

        if (choice == 1) // Pyramid X_O
        {
            int choice;
            Player<char> *players[2];
            X_O_Board<char> *B = new X_O_Board<char>();
            string playerXName, player2Name;

            cout << "Welcome to FCAI X-O Game. :)\n";

            // Set up player 1
            cout << "Enter Player X name: ";
            cin >> playerXName;
            cout << "Choose Player X type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "3. Smart Computer (AI)\n";
            cin >> choice;

            switch (choice)
            {
            case 1:
                players[0] = new X_O_Player<char>(playerXName, 'X');
                break;
            case 2:
                players[0] = new X_O_Random_Player<char>('X');
                break;
            case 3:
                players[0] = new X_O_MinMax_Player<char>('X');
                players[0]->setBoard(B);
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
            cout << "3. Smart Computer (AI)\n";
            cin >> choice;

            switch (choice)
            {
            case 1:
                players[1] = new X_O_Player<char>(player2Name, 'O');
                break;
            case 2:
                players[1] = new X_O_Random_Player<char>('O');
                break;
            case 3:
                players[1] = new X_O_MinMax_Player<char>('O');
                players[1]->setBoard(B);
                break;
            default:
                cout << "Invalid choice for Player 2. Exiting the game.\n";
                return 1;
            }

            // Create the game manager and run the game
            GameManager<char> x_o_game(B, players);
            x_o_game.run();

            // Clean up
            delete B;
            for (int i = 0; i < 2; ++i)
            {
                delete players[i];
            }
        }
        else if (choice == 2) // Four in a row
        {
            cout << "Welcome to Connect Four!" << endl;
            cout << "Choose Game Mode:\n";
            cout << "1. Player vs Player\n";
            cout << "2. Player vs Random Computer\n";
            cout << "3. Player vs AI (MinMax)\n";
            cout << "Enter your choice: ";

            int choice;
            cin >> choice;

            while (choice != 1 && choice != 2 && choice != 3)
            { // Validate input for new option
                cout << "Invalid choice. Please enter 1, 2, or 3: ";
                cin >> choice;
            }

            // Create the board
            ConnectFourBoard<char> board;

            // Create players
            Player<char> *players[2];
            string name1, name2;

            if (choice == 1)
            {
                // Player vs Player
                cout << "Enter Player 1's name: ";
                cin >> name1;
                cout << "Enter Player 2's name: ";
                cin >> name2;
                players[0] = new ConnectFourPlayer<char>(name1, 'X');
                players[1] = new ConnectFourPlayer<char>(name2, 'O');
            }
            else if (choice == 2)
            {
                // Player vs Random Computer
                cout << "Enter Player 1's name: ";
                cin >> name1;
                players[0] = new ConnectFourPlayer<char>(name1, 'X');
                players[1] = new ConnectFourRandomPlayer<char>('O');
            }
            else
            {
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
        }
        else if (choice == 3) // 5x5 X_O Game
        {
            int choice;
            Playern *players[2];
            players[0] = new Playern(1, 'x');
            Board5 *bord = new Tic_Board();
            cout << "Welcome to 5x5 X-O Game :\n";
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "3. Smart Computer (AI)\n";
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
        else if (choice == 4) // Word
        {
            int choice;
            Player<char> *players[2];
            Tic_Tac_Toe_Board<char> *B = new Tic_Tac_Toe_Board<char>();
            string playerXName, player2Name;

            cout << "Welcome to FCAI X-O Game. :)\n";

            // Set up player 1
            cout << "Enter Player X name: ";
            cin >> playerXName;
            cout << "Choose Player X type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "3. Smart Computer (AI)\n";
            cin >> choice;

            switch (choice)
            {
            case 1:
                players[0] = new Tic_Tac_Toe_Player<char>(playerXName, 'X');
                break;
            case 2:
                players[0] = new Tic_Tac_Toe_Random_Player<char>('X');
                break;
            case 3:
                players[0] = new Tic_Tac_Toe_Minimax_Player<char>("AI",'X');
                players[0]->setBoard(B);
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
            cout << "3. Smart Computer (AI)\n";
            cin >> choice;

            switch (choice)
            {
            case 1:
                players[1] = new Tic_Tac_Toe_Player<char>(player2Name, 'O');
                break;
            case 2:
                players[1] = new Tic_Tac_Toe_Random_Player<char>('O');
                break;
            case 3:
                players[1] = new Tic_Tac_Toe_Minimax_Player<char>("AI",'O');
                players[1]->setBoard(B);
                break;
            default:
                cout << "Invalid choice for Player 2. Exiting the game.\n";
                return 1;
            }

            // Create the game manager and run the game
            GameManager<char> Tic_Tac_Toe_game(B, players);
            Tic_Tac_Toe_game.run();

            // Clean up
            delete B;
            for (int i = 0; i < 2; ++i)
            {
                delete players[i];
            }
        }
        else if (choice == 5) // Numerical
        {
            string playerXName, playerOName;
            int choice;

            // Set up player 1 (X)
            cout << "Enter Player 1 name: ";
            cin >> playerXName;
            cout << "Choose Player 1 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "3. Smart Computer (AI)\n";
            cin >> choice;

            NumericalPlayer<int> *player1;
            if (choice == 1)
            {
                player1 = new NumericalPlayer<int>(playerXName, 1);
            }
            else if (choice == 2)
            {
                player1 = reinterpret_cast<NumericalPlayer<int> *>(new NumericalRandomPlayer<int>(1));
            }
            else if (choice == 3)
            {
                player1 = reinterpret_cast<NumericalPlayer<int> *>(new NumericalAIPlayer<int>(1));
            }
            else
            {
                cout << "Invalid choice. Defaulting to Random Computer." << endl;
                player1 = reinterpret_cast<NumericalPlayer<int> *>(new NumericalRandomPlayer<int>(1));
            }

            // Set up player 2 (O)
            cout << "Enter Player 2 name: ";
            cin >> playerOName;
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "3. Smart Computer (AI)\n";
            cin >> choice;

            NumericalPlayer<int> *player2;
            if (choice == 1)
            {
                player2 = new NumericalPlayer<int>(playerOName, 2);
            }
            else if (choice == 2)
            {
                player2 = reinterpret_cast<NumericalPlayer<int> *>(new NumericalRandomPlayer<int>(2));
            }
            else if (choice == 3)
            {
                player2 = reinterpret_cast<NumericalPlayer<int> *>(new NumericalAIPlayer<int>(2));
            }
            else
            {
                cout << "Invalid choice. Defaulting to Random Computer." << endl;
                player2 = reinterpret_cast<NumericalPlayer<int> *>(new NumericalRandomPlayer<int>(2));
            }

            NumericalTicTacToeBoard<int> board;
            player1->set_board(&board);
            player2->set_board(&board);

            int x, y;
            while (true)
            {
                board.display_board();
                player1->getmove(x, y);
                if (player1->has_won())
                {
                    cout << player1->get_name() << " wins with a sum of " << player1->get_sum() << "!" << endl;
                    break;
                }
                if (board.is_full())
                {
                    cout << "The game is a draw!" << endl;
                    break;
                }

                board.display_board();
                player2->getmove(x, y);
                if (player2->has_won())
                {
                    cout << player2->get_name() << " wins with a sum of " << player2->get_sum() << "!" << endl;
                    break;
                }
                if (board.is_full())
                {
                    cout << "The game is a draw!" << endl;
                    break;
                }
            }
        }
        else if (choice == 6) // Misere X-O Game
        {
            int choice;
            Playerx<char> *players[2];
            Misere_Board<char> *B = new Misere_Board<char>();
            string playerXName, player2Name;

            cout << "Welcome to Misere X-O Game:\n";

            // Set up player 1
            cout << "Enter Player X name: ";
            cin >> playerXName;
            cout << "Choose Player X type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "3. Ai Player\n";
            cin >> choice;

            switch (choice)
            {
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

            switch (choice)
            {
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
            for (int i = 0; i < 2; ++i)
            {
                delete players[i];
            }
        }
        else if (choice == 7) // Ultimate
        {
            int choice;
            Player<char> *players[2];
            Ultimate_Tic_Tac_Toe_Board<char> *B = new Ultimate_Tic_Tac_Toe_Board<char>();
            string playerXName, player2Name;

            cout << "Welcome to FCAI X-O Game. :)\n";

            // Set up player 1
            cout << "Enter Player X name: ";
            cin >> playerXName;
            cout << "Choose Player X type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch (choice)
            {
            case 1:
                players[0] = new Ultimate_Tic_Tac_Toe_Player<char>(playerXName, 'X');
                break;
            case 2:
                players[0] = new Ultimate_Tic_Tac_Toe_Random_Player<char>('X');
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
            cin >> choice;

            switch (choice)
            {
            case 1:
                players[1] = new Ultimate_Tic_Tac_Toe_Player<char>(player2Name, 'O');
                break;
            case 2:
                players[1] = new Ultimate_Tic_Tac_Toe_Random_Player<char>('O');
                break;
            default:
                cout << "Invalid choice for Player 2. Exiting the game.\n";
                return 1;
            }

            // Create the game manager and run the game
            GameManager<char> Ultimate_Tic_Tac_Toe_game(B, players);
            Ultimate_Tic_Tac_Toe_game.run();

            // Clean up
            delete B;
            for (int i = 0; i < 2; ++i)
            {
                delete players[i];
            }
        }
        else if (choice == 8) // SUS Game
        {
            int choice;
            Player<char> *players[2];
            SUS_Board<char> *B = new SUS_Board<char>();
            string player1Name, player2Name;

            cout << "Welcome to SUS Game!\n";

            // Set up player 1
            cout << "Enter Player 1 name: ";
            cin >> player1Name;
            cout << "Choose Player 1 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch (choice)
            {
            case 1:
                players[0] = new SUS_Player<char>(player1Name, 'S');
                break;
            case 2:
                players[0] = new SUS_Random_Player<char>('S');
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
            cin >> choice;

            switch (choice)
            {
            case 1:
                players[1] = new SUS_Player<char>(player2Name, 'U');
                break;
            case 2:
                players[1] = new SUS_Random_Player<char>('U');
                break;
            default:
                cout << "Invalid choice for Player 2. Exiting the game.\n";
                return 1;
            }

            // Create the game manager and run the game
            GameManager<char> sus_game(B, players);
            sus_game.run();

            // Determine winner
            if (B->getScore(1) > B->getScore(2))
            {
                cout << player1Name << " wins with " << B->getScore(1) << " points!\n";
            }
            else if (B->getScore(1) < B->getScore(2))
            {
                cout << player2Name << " wins with " << B->getScore(2) << " points!\n";
            }
            else
            {
                cout << "It's a draw!\n";
            }

            // Clean up
            delete B;
            for (int i = 0; i < 2; ++i)
            {
                delete players[i];
            }
        }
        else if (choice == 9) // Exit
        {
            cout << "Exiting, Thank you" << endl;
        }
        else
        {
            cout << "Invalid choice! Please select a number between 1 and 9" << endl;
        }

    } while (choice != 9);

    return 0;
}
