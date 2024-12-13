#include <iostream>
#include <string>
#include "MisereTicTacToe.h"
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

    if (choice == 1) {
        cout << "Enter name for Player 1: ";
        cin >> player1_name;
        player2_name = "Computer";
        MisereTicTacToe_Board<char>* board = new MisereTicTacToe_Board<char>();
        MisereTicTacToe_Player<char>* player1 = new MisereTicTacToe_Player<char>(player1_name, 'X');
        MisereTicTacToe_Random_Player<char>* player2 = new MisereTicTacToe_Random_Player<char>('O');

        Player<char>* players[2] = { player1, player2 };

        GameManager<char> gameManager(board, players);
        gameManager.run();
    }
    else if (choice == 2) {
        cout << "Enter name for Player 1: ";
        cin >> player1_name;
        cout << "Enter name for Player 2: ";
        cin >> player2_name;

        MisereTicTacToe_Board<char>* board = new MisereTicTacToe_Board<char>();
        MisereTicTacToe_Player<char>* player1 = new MisereTicTacToe_Player<char>(player1_name, 'X');
        MisereTicTacToe_Player<char>* player2 = new MisereTicTacToe_Player<char>(player2_name, 'O');

        Player<char>* players[2] = { player1, player2 };

        GameManager<char> gameManager(board, players);
        gameManager.run();
    }
    else {
        cout << "Invalid choice. Please select a valid option.\n";
    }

    return 0;
}


