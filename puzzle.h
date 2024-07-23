#ifndef PUZZLE_H
#define PUZZLE_H

#include <vector>
#include <string>

using namespace std;

class Puzzle
{
private:
    vector<int> board; // será um vetor, não uma matriz
    int empty_position; // posição do zero(vazio) no tabuleiro
    vector<int> board_goal = {0, 1, 2, 3, 4, 5, 6, 7, 8}; // estado objetivo do tabuleiro

public:
    Puzzle(vector<int> instance);
    void print_board();
};

#endif // PUZZLE_H
