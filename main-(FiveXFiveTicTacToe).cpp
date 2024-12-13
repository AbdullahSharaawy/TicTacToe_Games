#include <iostream>
#include "TicTacToe_5x5.h"
#include "BoardGame_Classes.h"

using namespace std;

string player1_name;
string player2_name;
int main() {
    int choice;

    cout << "Select the game mode:\n";
    cout << "1. Player vs Computer\n";
    cout << "2. Player vs Player\n";
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    Player<char>* player[2];

    switch (choice) {

    case 1: {
        cout << "Enter name for Player 1: ";
        cin >> player1_name;
        
        FiveXFiveTicTacToe_Board<char>* board = new FiveXFiveTicTacToe_Board<char>();
        FiveXFiveTicTacToe_Player<char>* player1 = new FiveXFiveTicTacToe_Player<char>(player1_name, 'X');
        FiveXFiveTicTacToe_Random_Player<char>* player2 = new FiveXFiveTicTacToe_Random_Player<char>('O');

        player[0] = player1;
        player[1] = player2;

        board->set_players(player1, player2);

        GameManager<char> gameManager(board, player);
        gameManager.run();

        

        break;
    }

    case 2: {
        
        cout << "Enter name for Player 1: ";
        cin >> player1_name;
        cout << endl;
        cout << "Enter name for Player 2: ";
        cin >> player2_name;
        FiveXFiveTicTacToe_Board<char>* board = new FiveXFiveTicTacToe_Board<char>();
        FiveXFiveTicTacToe_Player<char>* player1 = new FiveXFiveTicTacToe_Player<char>(player1_name, 'X');
        FiveXFiveTicTacToe_Player<char>* player2 = new FiveXFiveTicTacToe_Player<char>(player2_name, 'O');

        player[0] = player1;
        player[1] = player2;

        board->set_players(player1, player2);

        GameManager<char> gameManager(board, player);
        gameManager.run();

        

        break;
    }

    default: {
        cout << "Invalid choice. Please select a valid option.\n";
        break;
    }
    }

    return 0;
}
