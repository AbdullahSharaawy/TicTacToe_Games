#include <iostream>
#include "TicTacToe_5x5.h"
#include "BoardGame_Classes.h"

using namespace std;

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
        string player1_name;
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

        delete player1;
        delete player2;
        delete board;

        break;
    }

    case 2: {
        string player1_name, player2_name;
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

        delete player1;
        delete player2;
        delete board;

        break;
    }

    default: {
        cout << "Invalid choice. Please select a valid option.\n";
        break;
    }
    }

    return 0;
}
