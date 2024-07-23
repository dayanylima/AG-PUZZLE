#include "puzzle.h"
#include <iostream>
#include <fstream>
#include <sstream>

Puzzle::Puzzle(vector<int> instance)
{
    board = instance;
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
}