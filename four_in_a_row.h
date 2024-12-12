
#ifndef _for_in_a_row_H
#define _four_in_a_row_H
#pragma once
#include "BoardGame_Classes.h"
//#include"Controller.h"

template <typename T>
class four_in_a_row_Board :public Board<T> {
public:
    four_in_a_row_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    bool selectMove_X(int& x, int y, T symbol);

};

template <typename T>
class four_in_a_row_Player : public Player<T> {
public:
    four_in_a_row_Player(string name, T symbol);
    void getmove(int&x, int& y);

};

template <typename T>
class four_in_a_row_Random_Player : public RandomPlayer<T> {
public:
    four_in_a_row_Random_Player(T symbol);
    void getmove(int& x, int& y);
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
//char** copy_board;
template <typename T>
four_in_a_row_Board<T>::four_in_a_row_Board() {
    this->rows = 6;
    this->columns = 7;
   this->board = new char* [this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
  //  copy_board = this->board;
}

template <typename T>
bool four_in_a_row_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    
    if (selectMove_X(x, y, mark))
    {
        if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
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
    else return false;

}
template <typename T>
bool four_in_a_row_Board<T>::selectMove_X( int& x, int y, T symbol)
{

    for (short i = 5; i >=0; i--)
    {
        
        if (this->board[i][y] == 0 )
        {
            x = i;
            return true;
        }

        else if (i == 0)
        {
            if (this->board[i][y - 1] == 'X' || this->board[i][y - 1] == 'O')
            {

                return false;
            }
        }
    }
    return true;
}


// Display the board and the pieces on it
template <typename T>
void four_in_a_row_Board<T>::display_board() {
    //loop to show the header of table
    for (short j = 0;j < 7;j++)
    {
        cout <<setw(2)<< j << "  | ";
    }
   
    cout << endl;
    cout << "__________________________________________\n";
    //loop to show the table
    for (short i = 0;i < 6;i++)
    {
        for (short j = 0;j < 7;j++)
        { 
            if(this->board[i][j]!=0)
            cout << setw(2)<<this->board[i][j] << "  | ";
            else cout << setw(2) << this->board[i][j] << "   | ";
        }
        cout << endl;
        
        cout << "__________________________________________";
    }
}

// Returns true if there is any winner
template <typename T>
bool four_in_a_row_Board<T>::is_win() {
    //we can know who won from this loop if we found four elements are similar in specefic row
    for (short i = 0; i < 6; i++)
    {
        //if board[i][3]!='X' or board[i][3]!='O' exsit from the loop 
        if (this->board[i][3] == 'X' || this->board[i][3] == 'O')
        {
            if ((this->board[i][3] == this->board[i][2] && this->board[i][3] == this->board[i][1] && this->board[i][3] == this->board[i][0]) ||
                (this->board[i][3] == this->board[i][4] && this->board[i][3] == this->board[i][5] && this->board[i][3] == this->board[i][6]) ||
                (this->board[i][3] == this->board[i][4] && this->board[i][3] == this->board[i][5] && this->board[i][3] == this->board[i][2]) ||
                (this->board[i][3] == this->board[i][4] && this->board[i][3] == this->board[i][1] && this->board[i][3] == this->board[i][2]))
            {
                return true;
            }
        }
    }
    //we can know who won from this loop if we found four elements are similar in specefic cloumn
    for (short i = 0; i < 6; i++)
    {
        //if board[i][3]!='X' or board[i][3]!='O' exsit from the loop
        if (this->board[3][i] == 'X' || this->board[3][i] == 'O')
        {
            if ((this->board[3][i] == this->board[2][i] && this->board[3][i] == this->board[1][i] && this->board[3][i] == this->board[0][i]) ||
                (this->board[3][i] == this->board[2][i] && this->board[3][i] == this->board[4][i] && this->board[3][i] == this->board[5][i]) ||
                (this->board[3][i] == this->board[2][i] && this->board[3][i] == this->board[1][i] && this->board[3][i] == this->board[4][i]) ||
                (this->board[3][i] == this->board[2][i] && this->board[3][i] == this->board[1][i] && this->board[3][i] == this->board[4][i]))
            {
                return true;
            }
        }
    }
    //we can know who won from this loop if we found four elements are similar in specefic  diagonal
    for (short i = 0; i < 7; i++)
    {
        //if board[i][3]!='X' or board[i][3]!='O' exsit from the loop
        if (this->board[3][i] == 'X' || this->board[3][i] == 'O')
        {
            if ((this->board[3][i] == this->board[2][i - 1] && this->board[3][i] == this->board[1][i - 2] && this->board[3][i] == this->board[0][i - 3]) ||
                (this->board[3][i] == this->board[4][i - 1] && this->board[3][i] == this->board[1][i + 2] && this->board[3][i] == this->board[2][i + 1]) ||
                (this->board[3][i] == this->board[4][i - 1] && this->board[3][i] == this->board[5][i - 2] && this->board[3][i] == this->board[2][i + 1]) ||
                (this->board[3][i] == this->board[4][i + 1] && this->board[3][i] == this->board[1][i - 2] && this->board[3][i] == this->board[2][i - 1]) ||
                (this->board[3][i] == this->board[4][i + 1] && this->board[3][i] == this->board[5][i + 2] && this->board[3][i] == this->board[2][i - 1]) ||
                (this->board[3][i] == this->board[2][i + 1] && this->board[3][i] == this->board[1][i + 2] && this->board[3][i] == this->board[0][i + 3]))
            {                                                                       
                return true;
            }
        }
    }
    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool four_in_a_row_Board<T>::is_draw() {
    return (this->n_moves == 42 && !is_win());
}

template <typename T>
bool four_in_a_row_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
four_in_a_row_Player<T>::four_in_a_row_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void four_in_a_row_Player<T>::getmove(int& x, int& y) {
    while (true) {
        cout << "\nEnter number of column (0 -> 6): ";
        cin >> y;

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
four_in_a_row_Random_Player<T>::four_in_a_row_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void four_in_a_row_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}







#endif //_3X3X_O_H

