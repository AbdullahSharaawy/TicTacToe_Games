
#ifndef _FourXFourTicTacToe_H
#define _FourXFourTicTacToe_H
#pragma once
#include "BoardGame_Classes.h"
#include <algorithm>
bool deleteSymbol = false;// to remove symbol from the board
bool checkOnly = false;// to check if cell empty or not only
template <typename T>
class FourXFourTicTacToe_Board :public Board<T> {
public:
    FourXFourTicTacToe_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    
   
};

template <typename T>
class FourXFourTicTacToe_Player : public Player<T> {
public:
    FourXFourTicTacToe_Player(string name, T symbol);
    void getmove(int& x, int& y);
    bool generatePositionsList(int x, int y, vector <string>&list);// where the player must choose from them
    bool IsValidMove(int x, int y,vector <string>list);
    bool isCellEmpty(int x, int y);
    bool isValidSymbol(int x, int y);
    void setBoard(Board<T>* b);
};

template <typename T>
class FourXFourTicTacToe_Random_Player : public RandomPlayer<T> {
public:
    FourXFourTicTacToe_Random_Player(T symbol);
    void getmove(int& x, int& y);
    bool generatePositionsList(int x, int y, vector <string>& list);// where the player must choose from them
    bool IsValidMove(int x, int y, vector <string>list);
    bool isCellEmpty(int x, int y);
    bool isValidSymbol(int x, int y);
    void setBoard(Board<T>* b);
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
FourXFourTicTacToe_Board<T>::FourXFourTicTacToe_Board() {
    this->rows = 4;
    this->columns = 4;
    this->board = new char* [this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    // this loop to prepare GameStart
    for (int i = 0; i < this->rows; i+=3) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            if (i == 0)
            {
                if(j%2==0)
                    this->board[i][j] = 'X';
                else
                    this->board[i][j] = 'O';
            }
            else
            {
                if (j % 2 == 0)
                    this->board[i][j] = 'O';
                else
                    this->board[i][j] = 'X';
            }
            
        }
    }

    this->n_moves = 0;
}

template <typename T>
bool FourXFourTicTacToe_Board<T>::update_board(int x, int y, T mark) {
    
    // to check if cell empty or not
    if (checkOnly && (x >= 0 && y >= 0 && y < this->columns && x < this->columns) && mark==0)
    {
        return this->board[x][y] == 0;
    }
    else if (checkOnly && (x >= 0 && y >= 0 && y < this->columns && x < this->columns) && mark != 0)
    {
        return this->board[x][y] == mark;
    }
    //  update if move is valid or delete element
    else if (((x >= 0 && y >= 0 && y < this->columns && x<this->columns)  && (this->board[x][y] == 0 || mark == 0 )) || deleteSymbol ) {
        if (mark == 0 || deleteSymbol) {
           /* this->n_moves--;*/
            this->board[x][y] = 0;
        }
        else {
            /*this->n_moves++;*/
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void FourXFourTicTacToe_Board<T>::display_board() {
    //loop to show the header of table
    cout << "x/y|";
    for (short j = 0;j < 4;j++)
    {
        cout << setw(2) << j << "  | ";
    }

    cout << endl;
    cout << "__________________________________________\n";
    //loop to show the table
    for (short i = 0;i < 4;i++)
    {
        cout << i << "  |";
        for (short j = 0;j < 4;j++)
        {
            if (this->board[i][j] != 0)
                cout << setw(2) << this->board[i][j] << "  | ";
            else cout << setw(2) << this->board[i][j] << "   | ";
        }
        cout << endl;

        cout << "__________________________________________\n";
    }
}

// Returns true if there is any winner
template <typename T>
bool FourXFourTicTacToe_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0) ||
            (this->board[1][i] == this->board[2][i] && this->board[2][i] == this->board[3][i] && this->board[1][i] != 0) ||
            (this->board[i][1] == this->board[i][2] && this->board[i][2] == this->board[i][3] && this->board[i][3] != 0)
            )
        
        {
            return true;
        }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        return true;
    }
    if ((this->board[0][1] == this->board[1][2] && this->board[1][2] == this->board[2][3] && this->board[0][1] != 0) ||
        (this->board[0][3] == this->board[1][2] && this->board[1][2] == this->board[2][1] && this->board[0][3] != 0)) {
        return true;
    }
    if ((this->board[3][0] == this->board[2][1] && this->board[2][1] == this->board[1][2] && this->board[3][0] != 0) ||
        (this->board[3][2] == this->board[2][1] && this->board[2][1] == this->board[1][0] && this->board[2][1] != 0)) {
        return true;
    }
    if ((this->board[1][1] == this->board[2][2] && this->board[2][2] == this->board[3][3] && this->board[1][1] != 0) ||
        (this->board[1][3] == this->board[2][2] && this->board[2][2] == this->board[3][1] && this->board[2][2] != 0)) {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool FourXFourTicTacToe_Board<T>::is_draw() {
    return false;
}

template <typename T>
bool FourXFourTicTacToe_Board<T>::game_is_over() {
    return is_win() /*|| is_draw()*/;
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
FourXFourTicTacToe_Player<T>::FourXFourTicTacToe_Player(string name, T symbol) : Player<T>(name, symbol) {}
template<typename T>
bool FourXFourTicTacToe_Player<T>::isCellEmpty(int x, int y)
{
    
        // Assume Board<T> provides `getCell` or equivalent
        if (this->boardPtr) {
            return this->boardPtr->update_board(x, y, '\0'); // check if the cell is empty or not
        }
        return false;
}
template<typename T>
bool FourXFourTicTacToe_Player<T>::isValidSymbol(int x, int y)
{

    // Assume Board<T> provides `getCell` or equivalent
    if (this->boardPtr) {
        return this->boardPtr->update_board(x, y, this->symbol); // Try updating with an empty value
    }
    return false;
}
template <typename T>
void FourXFourTicTacToe_Player<T>::getmove(int& x, int& y) {
    
    cout << "\nTurn Player_" << this->symbol << endl;
    int current_x, current_y;
    checkOnly = true;// turn on 
    vector <string>list;
    do {
        cout << "\nPlease enter a position for your token x and y separated by spaces, where this token you can move it  to an empty place next to it: ";
       
        while (!(cin >> current_x >> current_y)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter two integer values for x and y: ";
        }

    } while (!generatePositionsList(current_x, current_y, list) );
    do
    {
        cout << "\nPlease enter your move x and y from these positions  separated by spaces : ";
        for (string position : list)
            cout << "( " << position << " ), ";
        cout << endl;
        while (!(cin >> x >> y)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter two integer values for x and y: ";
        }
    } while (!IsValidMove(x, y, list));
    checkOnly = false;//turn off
    deleteSymbol = true;//turn on
    this->boardPtr->update_board(current_x, current_y, '\0');
    deleteSymbol = false;// turn off
}
template <typename T>
bool FourXFourTicTacToe_Player<T>::IsValidMove(int x, int y, vector <string>list)
{
    return (find(list.begin(), list.end(),to_string(x)+" "+to_string(y)) != list.end());
}
template <typename T>
bool FourXFourTicTacToe_Player<T>::generatePositionsList(int x, int y, vector <string>&list)
{
   
    
    if (x >= 0 && y >= 0 && y < 4 && x < 4 && isValidSymbol(x,y) )
    {

        if (x - 1 >= 0 && x-1 < 4)
        {
            if (isCellEmpty(x-1,y))
                list.push_back(to_string(x - 1)  +" "+to_string(y));
        }
         if (x + 1 >= 0 && x+1 < 4)
        {
            if (isCellEmpty(x + 1, y))
                list.push_back(to_string(x + 1) + " " + to_string(y));

        }
         if (y + 1 >= 0 && y+1 < 4)
        {
            if (isCellEmpty(x, y+1))
                list.push_back(to_string(x ) + " " + to_string(y+1));

        }
         if (y - 1 >= 0 && y-1 < 4)
        {
            if (isCellEmpty(x, y-1))
                list.push_back(to_string(x) + " " + to_string(y - 1));

        }
    }
    else return false;
   
    if (list.size() != 0)
        return true;
    
        return false;
}
template <typename T>
void FourXFourTicTacToe_Player<T>::setBoard(Board<T>* b)
{
    this->boardPtr = b;  // Store the board pointer
}


// Constructor for X_O_Random_Player
template <typename T>
FourXFourTicTacToe_Random_Player<T>::FourXFourTicTacToe_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 4;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void FourXFourTicTacToe_Random_Player<T>::getmove(int& x, int& y) {
    cout << "\n Computer Move\n\n";
    int current_x, current_y;
    checkOnly = true;// turn on 
    vector <string>list;
    do {
        current_x = rand() % this->dimension;  // Random number between 0 and 3
        current_y = rand() % this->dimension;

    } while (!generatePositionsList(current_x, current_y, list));
    do
    {
        x = rand() % this->dimension;  // Random number between 0 and 3
        y = rand() % this->dimension;
    } while (!IsValidMove(x, y, list));
    checkOnly = false;//turn off
    deleteSymbol = true;//turn on
    this->boardPtr->update_board(current_x, current_y, '\0');
    deleteSymbol = false;// turn off
    
   
}
template <typename T>
void FourXFourTicTacToe_Random_Player<T>::setBoard(Board<T>* b)
{
    this->boardPtr = b;  // Store the board pointer
}
template<typename T>
bool FourXFourTicTacToe_Random_Player<T>::isCellEmpty(int x, int y)
{

    // Assume Board<T> provides `getCell` or equivalent
    if (this->boardPtr) {
        return this->boardPtr->update_board(x, y, '\0'); // Try updating with an empty value
    }
    return false;
}
template<typename T>
bool FourXFourTicTacToe_Random_Player<T>::isValidSymbol(int x, int y)
{

    // Assume Board<T> provides `getCell` or equivalent
    if (this->boardPtr) {
        return this->boardPtr->update_board(x, y, this->symbol); // Try updating with an empty value
    }
    return false;
}
template<typename T>
bool FourXFourTicTacToe_Random_Player<T>::IsValidMove(int x, int y, vector <string>list)
{
    return (find(list.begin(), list.end(), to_string(x) + " " + to_string(y)) != list.end());
}
template <typename T>
bool FourXFourTicTacToe_Random_Player<T>::generatePositionsList(int x, int y, vector <string>& list)
{


    if (x >= 0 && y >= 0 && y < 4 && x < 4 && isValidSymbol(x, y))
    {

        if (x - 1 >= 0 && x < 4)
        {
            if (isCellEmpty(x - 1, y))
                list.push_back(to_string(x - 1) + " " + to_string(y));
        }
        if (x + 1 >= 0 && x < 4)
        {
            if (isCellEmpty(x + 1, y))
                list.push_back(to_string(x + 1) + " " + to_string(y));

        }
        if (y + 1 >= 0 && y < 4)
        {
            if (isCellEmpty(x, y + 1))
                list.push_back(to_string(x) + " " + to_string(y + 1));

        }
        if (y - 1 >= 0 && y < 4)
        {
            if (isCellEmpty(x, y - 1))
                list.push_back(to_string(x) + " " + to_string(y - 1));

        }
    }
    else return false;

    if (list.size() != 0)
        return true;

    return false;
}






#endif //_FourXFourTicTacToe_H

