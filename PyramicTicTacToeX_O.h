
#ifndef _TicTacToeX_O_H
#define _TicTacToeX_O_H
#pragma once
#include "BoardGame_Classes.h"

template <typename T>
class PyramicTicTacToe_Board :public Board<T> {
public:
    PyramicTicTacToe_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class PyramicTicTacToe_Player : public Player<T> {
public:
    PyramicTicTacToe_Player(string name, T symbol);
    void getmove(int& x, int& y);

};

template <typename T>
class PyramicTicTacToe_Random_Player : public RandomPlayer<T> {
public:
    PyramicTicTacToe_Random_Player(T symbol);
    void getmove(int& x, int& y);
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
PyramicTicTacToe_Board<T>::PyramicTicTacToe_Board() {
    this->rows = 3;
    this->columns = 5;
    this->board = new char* [this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool PyramicTicTacToe_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (((x == 0 && (y >= 0 && y < this->columns)) || (x == 1 && (y >= 1 && y < this->columns - 1)) || (x == 2 && y == 2)) && (this->board[x][y] == 0 || mark == 0)) {
        if (mark == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void PyramicTicTacToe_Board<T>::display_board() {
    for (int i = this->rows - 1; i >= 0; i--) {

        cout << "\n";

        if (i == 1) cout << "\t ";
        else if (i == 2) cout << "\t\t  ";
        else  cout << "";

        cout << "| ";
        for (int j = i; j < this->columns - i; j++) {


            cout << setw(2) << this->board[i][j];

            if (this->board[i][j] == 0)
                cout << "(" << i << "," << j << ")";
            else cout << "\t";

            cout << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool PyramicTicTacToe_Board<T>::is_win() {
    // Check rows and columns

    if ((this->board[0][0] == this->board[0][1] && this->board[0][1] == this->board[0][2] && this->board[0][0] != 0) ||//check row 0
        (this->board[0][2] == this->board[1][2] && this->board[1][2] == this->board[2][2] && this->board[0][2] != 0) ||// chek column 2
        (this->board[0][1] == this->board[0][2] && this->board[0][2] == this->board[0][3] && this->board[0][1] != 0) ||//check row 0
        (this->board[0][2] == this->board[0][3] && this->board[0][2] == this->board[0][4] && this->board[0][2] != 0) ||
        (this->board[1][1] == this->board[1][2] && this->board[1][2] == this->board[1][3] && this->board[1][1] != 0)) //check row 1
    {
        return true;
    }


    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[2][2] == this->board[1][3] && this->board[1][3] == this->board[0][4] && this->board[2][2] != 0)) {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool PyramicTicTacToe_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool PyramicTicTacToe_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
PyramicTicTacToe_Player<T>::PyramicTicTacToe_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void PyramicTicTacToe_Player<T>::getmove(int& x, int& y) {
   
    
    while (true) {
        cout << "\nEnter your move x and y  separated by spaces: ";
        cin >> x >> y;

        // Check if input is valid
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a valid integer.\n";
        }
        else {
            break; // Exit the loop if input is valid
        }
    }

}

// Constructor for X_O_Random_Player
template <typename T>
PyramicTicTacToe_Random_Player<T>::PyramicTicTacToe_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void PyramicTicTacToe_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}







#endif //_3X3X_O_H

