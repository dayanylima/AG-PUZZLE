#ifndef PUZZLE_H
#define PUZZLE_H

#include <vector>
#include <string>

using namespace std;

class Puzzle
{
private:
    vector<int> board; // será um vetor, não uma matriz

public:
    Puzzle(vector<int> instance);
    void print_board();
};

#endif // PUZZLE_H
