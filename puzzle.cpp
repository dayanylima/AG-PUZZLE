#include "puzzle.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>  

Puzzle::Puzzle(vector<int> instance)
{
    board = instance;
    empty_position = find(board.begin(), board.end(), 0) - board.begin();
}

void Puzzle::print_board()
{
    cout << "Board: " << endl;
    for (size_t i = 0; i < board.size(); ++i)
    {
        if (i % 3 == 0 && i != 0)
            cout << endl;
        cout << board[i] << " ";
    }
    cout << endl;

    cout << "Empty position: " << empty_position << endl;
}