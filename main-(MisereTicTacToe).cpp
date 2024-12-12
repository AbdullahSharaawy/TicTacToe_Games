#include <iostream>
#include <string>
#include "MisereTicTacToe.h"
#include "BoardGame_Classes.h"

using namespace std;

Player<char>* name[2];

int main() {
    int choice;

    cout << "Select the game mode:\n";
    cout << "1. Player vs Computer\n";
    cout << "2. Player vs Player\n";
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    if (choice == 1) {
        string player1_name;
        cout << "Enter name for Player 1: ";
        cin >> player1_name;

        MisereTicTacToe_Board<char>* board = new MisereTicTacToe_Board<char>();
        MisereTicTacToe_Player<char>* player1 = new MisereTicTacToe_Player<char>(player1_name, 'X');
        MisereTicTacToe_Random_Player<char>* player2 = new MisereTicTacToe_Random_Player<char>('O');

        board->set_players(player1, player2);
        name[0] = player1;
        name[1] = player2;

        GameManager<char> gameManager(board, name);
        gameManager.run();
    } 
    else if (choice == 2) {
        string player1_name, player2_name;
        cout << "Enter name for Player 1: ";
        cin >> player1_name;
        cout << "Enter name for Player 2: ";
        cin >> player2_name;

        MisereTicTacToe_Board<char>* board = new MisereTicTacToe_Board<char>();
        MisereTicTacToe_Player<char>* player1 = new MisereTicTacToe_Player<char>(player1_name, 'X');
        MisereTicTacToe_Player<char>* player2 = new MisereTicTacToe_Player<char>(player2_name, 'O');

        board->set_players(player1, player2);
        name[0] = player1;
        name[1] = player2;

        GameManager<char> gameManager(board, name);
        gameManager.run();
    } else {
        cout << "Invalid choice. Please select a valid option.\n";
    }

    return 0;
}
