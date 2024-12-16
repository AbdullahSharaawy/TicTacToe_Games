#ifndef _TICTACTOE_ULTIMATE_H
#define _TICTACTOE_ULTIMATE_H

#include "BoardGame_Classes.h"

int where_are_we(int x);

template <typename T>
class tictactoe_ultimateBoard:public Board<T> {
    char track_BigBoard[3][3];
public:
    tictactoe_ultimateBoard ();
    bool update_board (int x , int y , T symbol);
    void draw_X();
    void draw_O();
    void display_board ();
    void is_win_small();
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    
    
};

template <typename T>
class tictactoe_ultimatePlayer : public Player<T> {
public:
    tictactoe_ultimatePlayer (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class tictactoe_ultimateRandom_Player : public RandomPlayer<T>{
public:
    tictactoe_ultimateRandom_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  

using namespace std;

// Constructor for tictactoe_ultimateBoard
template <typename T>
tictactoe_ultimateBoard<T>::tictactoe_ultimateBoard() {
    this->rows = this->columns = 9;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            track_BigBoard[i][j] = 0;
        }
    }
}

template <typename T>
bool tictactoe_ultimateBoard<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            //for clarity
            cout << "\nposition chosen is: " << x << " " << y;
            cout << "\nfilled with mark: " << mark << endl;
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

template<typename T>
inline void tictactoe_ultimateBoard<T>::draw_X(){

}

template<typename T>
inline void tictactoe_ultimateBoard<T>::draw_O(){

}

// Display the board and the pieces on it
template <typename T>
void tictactoe_ultimateBoard<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2);
            (this->board[i][j] == 0) ? cout << " " : cout << this->board[i][j];
            cout << "|";
        }
        cout << "\n--------------------------------------------------------------------------";
    }
    cout << endl;
}

int where_are_we(int x) {// to get the correct position in the big board
    if (x < 3)
        return 0;
    else if (x < 6)
        return 1;
    else if (x < 9)
        return 2;
}

template<typename T>
void tictactoe_ultimateBoard<T>::is_win_small(){
    //finds out with board is win and assigns a corret mark
    for (int i = 0; i < this->rows; i+=3) {// for the rows
        for (int c = 0; c < this->rows; c+=3) {// for the columns
            if ((this->board[c][i] == this->board[c][i + 1] && this->board[c][i + 1] == this->board[c][i + 2] && this->board[c][i] != 0) ||
                (this->board[i][c] == this->board[i + 1][c] && this->board[i + 1][c] == this->board[i + 2][c] && this->board[i][c] != 0)) {
                track_BigBoard[where_are_we(i)][where_are_we(c)] = ((this->board[c][i] == this->board[c][i + 1] && this->board[c][i + 1] == this->board[c][i + 2]))
                                        ? this->board[c][i]
                                        : this->board[i][c];
            }
            if ((this->board[i][c] == this->board[i + 1][c + 1] && this->board[i + 1][c + 1] == this->board[i + 2][c + 2] && this->board[i][c] != 0) ||
                 (this->board[i][c + 2] == this->board[i + 1][c + 1] && this->board[i + 1][c + 1] == this->board[i + 2][c] && this->board[i][c + 2] != 0)) {
                 track_BigBoard[where_are_we(i)][where_are_we(c)] = ((this->board[i][c] == this->board[i + 1][c + 1] && this->board[i + 1][c + 1] == this->board[i + 2][c + 2] && this->board[i][c] != 0))
                                        ? this->board[i][c]
                                        : this->board[i][c + 2];
            }
        }
    }
}

// Returns true if there is any winner
template <typename T>
bool tictactoe_ultimateBoard<T>::is_win() {
    //run is_win_small first to track the game
    is_win_small();
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((track_BigBoard[i][0] == track_BigBoard[i][1] && track_BigBoard[i][1] == track_BigBoard[i][2] && track_BigBoard[i][0] != 0) ||
            (track_BigBoard[0][i] == track_BigBoard[1][i] && track_BigBoard[1][i] == track_BigBoard[2][i] && track_BigBoard[0][i] != 0)) {
            return true;
        }
    }

    // Check diagonals
    if ((track_BigBoard[0][0] == track_BigBoard[1][1] && track_BigBoard[1][1] == track_BigBoard[2][2] && track_BigBoard[0][0] != 0) ||
        (track_BigBoard[0][2] == track_BigBoard[1][1] && track_BigBoard[1][1] == track_BigBoard[2][0] && track_BigBoard[0][2] != 0)) {
        return true;
    }

    return false;
}

// Return true if 81 moves are done and no winner
template <typename T>
bool tictactoe_ultimateBoard<T>::is_draw() {
    return (this->n_moves == 81 && !is_win());
}

template <typename T>
bool tictactoe_ultimateBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for tictactoe_ultimatePlayer
template <typename T>
tictactoe_ultimatePlayer<T>::tictactoe_ultimatePlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void tictactoe_ultimatePlayer<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 8) separated by spaces: ";
    while (true) {
        cin >> x >> y;

        // Check if input is valid
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a valid integer.\n";
        }
        else {
            break; // Exit the loop if input is valid
        }
    }

}

// Constructor for tictactoe_ultimateRandom_Player
template <typename T>
tictactoe_ultimateRandom_Player<T>::tictactoe_ultimateRandom_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 9;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void tictactoe_ultimateRandom_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 8
    y = rand() % this->dimension;
}







#endif //_tictactoe_ultimate_O_H

