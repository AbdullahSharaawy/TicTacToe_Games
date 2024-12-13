#ifndef ULTIMATE_H
#define ULTIMATE_H

#include "TicTacToe_of_Ultimate.h"


class Ultimategame {
	char BigBoard[3][3];
    int Big_moves;
public:
	Ultimategame();
    void display_BigBoard();
	void Run_gaMe();
    bool You_win();
    bool You_draw();
};

//====================================================
//implementation

Ultimategame::Ultimategame(){
	for (int i = 0; i < 3; i++) 
		for (int j = 0; j < 3; j++)
		BigBoard[i][j] = 0;
    Big_moves = 0;
}

bool Ultimategame::You_win(){

        for (int i = 0; i < 3; i++) {
            if ((this->BigBoard[i][0] == this->BigBoard[i][1] && this->BigBoard[i][1] == this->BigBoard[i][2] && this->BigBoard[i][0] != 0) ||
                (this->BigBoard[0][i] == this->BigBoard[1][i] && this->BigBoard[1][i] == this->BigBoard[2][i] && this->BigBoard[0][i] != 0)) {
                return true;
            }
        }

        if ((this->BigBoard[0][0] == this->BigBoard[1][1] && this->BigBoard[1][1] == this->BigBoard[2][2] && this->BigBoard[0][0] != 0) ||
            (this->BigBoard[0][2] == this->BigBoard[1][1] && this->BigBoard[1][1] == this->BigBoard[2][0] && this->BigBoard[0][2] != 0)) {
            return true;
        }

        return false;
    
}

bool Ultimategame::You_draw(){
    
        if (Big_moves == 9) return true;
    
    return false;
}

void Ultimategame::display_BigBoard(){
    cout << "\nUltiMate Board:\n";
    cout << "\t\t0\t\t1\t\t2\n\n";
    for (int i = 0; i < 3; ++i) {
        cout << "\t" << i;
        for (int j = 0; j < 3; ++j) {
            cout << "\t" << "(x, y) " << (BigBoard[i][j] == 0 ? '.' : (BigBoard[i][j])) << "  |" << " ";
        }
        cout << "\n\n";
    }
}

void Ultimategame::Run_gaMe() {
	int choice;
	Player<char>* players[2];
	TicTacToeBoard* B = new TicTacToeBoard();
	string playerXName, player2Name;
    cout << "Welcome to FCAI Ultimate TIC TAC TOE Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
    case 1:
        players[0] = new TicTacToePlayer(playerXName, 'X');
        break;
    case 2:
        players[0] = new TicTacToeRandom_Player('X');
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return;
    }

    cout << "Enter Player O name: ";
    cin >> player2Name;
    cout << "Choose Player O type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
    case 1:
        players[1] = new TicTacToePlayer(player2Name, 'O');
        break;
    case 2:
        players[1] = new TicTacToeRandom_Player('O');
        break;
    default:
        cout << "Invalid choice for Player 2. Exiting the game.\n";
        return;
    }

    while (true) {
        int row, column, winersymbol;
  
        for (int i : {0, 1}) {
            display_BigBoard();

            if (players[i]->getname() != "Random Computer Player") {
                cout << "enter your move\n";
                cout << "choose a place in the Ultimate Board to play";
            }
            players[i]->getmove(row, column);
            if (players[i]->getname() == "Random Computer Player") {
                cout << "computer chose spot: " << row << " " << column << endl;
            }

            GameManager<char> game(B, players);
            cout << "player with symbol 'X' playes always first\n";
            game.run();
            Big_moves++;
            winersymbol = B->get_winer_Symbol();
            if (B->is_win()) {
                if (winersymbol == 'X') {
                    cout << "you get this one player " << players[0]->getname() << endl;
                    BigBoard[row][column] = winersymbol;
                }
                else {
                    cout << "you get this one player " << players[1]->getname() << endl;
                    BigBoard[row][column] = winersymbol;
                }
            }
            if (B->is_draw()) {
                cout << "it is a DRAW?!!!\n" << "well, no one gets this now";
                BigBoard[row][column] = 'D';
            }

            if (You_win()) {
                cout << "You win every thing" << winersymbol;
                cout << "\n========================== CongraterS ==========================\n";
                break;
            }
            if (You_draw()) {
                cout << "it is a DRAW?!!!\n" << "in the BIGBoard";
                cout << "looks like we have two losers today";
                cout << "\n===============================================================\n";
                break;
            }

            B->clear_Board();
        }

        if (You_win() || You_draw())
            break;

    } 

}

#endif
