
#ifndef _WORD_TICTACTOE_H
#define _WORD_TICTACTOE_H

#include "BoardGame_Classes.h"

template <typename T>
class WORD_TICTACTOE_Board :public Board<T> {
private:
   
public:
    WORD_TICTACTOE_Board(vector<string>Words);
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    string ReserveWord(string word) ;
    bool is_draw();
    bool game_is_over();
    bool IsValidWord(vector<string> Words,string word);
    static  vector <string>_Words;
};

template <typename T>
vector<string> WORD_TICTACTOE_Board<T>::_Words;


template <typename T>
class WORD_TICTACTOE_Player : public Player<T> {
public:
    WORD_TICTACTOE_Player(string name, T symbol);
    void getmove(int& x, int& y);

};

template <typename T>
class WORD_TICTACTOE_Random_Player : public RandomPlayer<T> {
public:
    WORD_TICTACTOE_Random_Player(T symbol);
    void getmove(int& x, int& y);
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
WORD_TICTACTOE_Board<T>::WORD_TICTACTOE_Board(vector<string>Words) {
    WORD_TICTACTOE_Board::_Words = Words;
    this->rows = this->columns = 3;
    this->board = new char* [this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}
template<typename T>
string WORD_TICTACTOE_Board<T>::ReserveWord(string word)
{
    string reversed = word;  // Create a copy of the input string
    reverse(reversed.begin(), reversed.end());  // Reverse the string
    return reversed;

}
template <typename T>
bool WORD_TICTACTOE_Board<T>::IsValidWord(vector<string>Words,string word)
{
    return (find(Words.begin(), Words.end(), word) != Words.end());
}
template <typename T>
bool WORD_TICTACTOE_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
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

// Display the board and the pieces on it
template <typename T>
void WORD_TICTACTOE_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
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
bool WORD_TICTACTOE_Board<T>::is_win() {
    // Check rows and columns
    string word[2];

    word[0] += this->board[0][0];
    word[0] += this->board[1][1];
    word[0] += this->board[2][2];

    word[1] += this->board[0][2];
    word[1] += this->board[1][1];
    word[1] += this->board[2][0];
    // Check diagonals
    if (IsValidWord(WORD_TICTACTOE_Board::_Words, word[0]) || IsValidWord(WORD_TICTACTOE_Board::_Words, word[1]) ||
        IsValidWord(WORD_TICTACTOE_Board::_Words,ReserveWord( word[0])) || IsValidWord(WORD_TICTACTOE_Board::_Words, ReserveWord(word[1]))) {
        return true;
    }
    for (int i = 0; i < this->rows; i++) {
        word[0] = "";
        word[1] = "";
        
        word[0] += this->board[i][0];
        word[0] += this->board[i][1];
        word[0] += this->board[i][2];
        
        word[1] += this->board[0][i];
        word[1] += this->board[1][i];
        word[1] += this->board[2][i];

       


        if (IsValidWord(WORD_TICTACTOE_Board::_Words,word[0]) || IsValidWord(WORD_TICTACTOE_Board::_Words, word[1]) ||
            IsValidWord(WORD_TICTACTOE_Board::_Words,ReserveWord( word[0])) || IsValidWord(WORD_TICTACTOE_Board::_Words, ReserveWord(word[1])))
        {
            return true;
        }
       
    }
   

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool WORD_TICTACTOE_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool WORD_TICTACTOE_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
WORD_TICTACTOE_Player<T>::WORD_TICTACTOE_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void WORD_TICTACTOE_Player<T>::getmove(int& x, int& y) {
    char letter;
    cout << "Please enter your letter: ";
    cin >> letter;  // 'letter' is local to this function, not 'symbol'

    // Optionally assign the letter to the player's symbol
    this->symbol = static_cast<T>(letter);  // Explicit cast to T if needed

    cout << "Please enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
WORD_TICTACTOE_Random_Player<T>::WORD_TICTACTOE_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void WORD_TICTACTOE_Random_Player<T>::getmove(int& x, int& y) {
    string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    this->symbol = letters[rand()%26];// random character
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}







#endif //_3X3X_O_H

