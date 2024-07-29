#ifndef PUZZLE_H
#define PUZZLE_H

#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <functional>

using namespace std;

struct PuzzleState
{
private:
    vector<int> board;  // será um vetor, não uma matriz
    int empty_position; // posição do zero(vazio) no tabuleiro
    vector<char> path;
    int total_cust, accumulated_cost, heuristic;

public:
    PuzzleState(const vector<int> &board, const vector<char> &path, int accumulated_cost);
    int manhattanDistance(int x1, int y1, int x2, int y2) const;
    int calculateHeuristic() const;
    bool stateObjective() const;
    vector<PuzzleState> generateMovements() const;
    int getTotalCost() const;
    int getAccumulatedCost() const;
    int getHeuristic() const;
    vector<char> getPath() const;
    const vector<int>& getBoard() const;
    size_t generateHash() const; // Nova função para gerar hash
};

struct CompareStates
{
    bool operator()(const PuzzleState &state1, const PuzzleState &state2) const
    {
        return state1.getTotalCost() > state2.getTotalCost();
    }
};

class Puzzle
{
private:
    vector<int> initial_board;
    priority_queue<PuzzleState, vector<PuzzleState>, CompareStates> priority; // fila de prioridade
    unordered_set<size_t> visited;                                             // armazena hash dos estados já visitados

public:
    Puzzle(vector<int> instance);
    void print_board();
    vector<char> solve(int &evaluated_states);
};

#endif // PUZZLE_H
