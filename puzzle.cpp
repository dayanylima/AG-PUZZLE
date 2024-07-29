#include "puzzle.h"
#include <iostream>
#include <unordered_set>

PuzzleState::PuzzleState(const vector<int> &board, const vector<char> &path, int accumulated_cost)
    : board(board), path(path), accumulated_cost(accumulated_cost)
{
    heuristic = calculateHeuristic();
    total_cust = accumulated_cost + heuristic;
}

int PuzzleState::manhattanDistance(int x1, int y1, int x2, int y2) const
{
    return abs(x1 - x2) + abs(y1 - y2);
}

int PuzzleState::calculateHeuristic() const
{
    int heuristic = 0;
    for (int i = 0; i < 9; i++)
    {
        if (board[i] != i)
        {
            int targetX = i % 3;
            int targetY = i / 3;
            int currentX = board[i] % 3;
            int currentY = board[i] / 3;
            heuristic += manhattanDistance(currentX, currentY, targetX, targetY);
        }
    }
    return heuristic;
}

bool PuzzleState::stateObjective() const
{
    return board == vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8};
}

vector<PuzzleState> PuzzleState::generateMovements() const
{
    vector<PuzzleState> movements;
    int x, y;
    for (int i = 0; i < 9; i++)
    {
        if (board[i] == 0)
        {
            x = i % 3;
            y = i / 3;
            break;
        }
    }

    auto addMovement = [&](int newX, int newY, char direction)
    {
        if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3)
        {
            vector<int> newBoard = board;
            swap(newBoard[x + y * 3], newBoard[newX + newY * 3]);
            vector<char> newPath = path;
            newPath.push_back(direction);
            movements.emplace_back(newBoard, newPath, accumulated_cost + 1);
        }
    };

    addMovement(x, y - 1, 'U'); // UP
    addMovement(x, y + 1, 'D'); // DOWN
    addMovement(x - 1, y, 'L'); // LEFT
    addMovement(x + 1, y, 'R'); // RIGHT

    return movements;
}

int PuzzleState::getTotalCost() const
{
    return total_cust;
}

int PuzzleState::getAccumulatedCost() const
{
    return accumulated_cost;
}

vector<char> PuzzleState::getPath() const
{
    return path;
}

int PuzzleState::getHeuristic() const
{
    return heuristic;
}

const vector<int> &PuzzleState::getBoard() const
{
    return board;
}

size_t PuzzleState::generateHash() const
{
    size_t hash = 0;
    for (int tile : board)
    {
        hash = hash * 31 + tile;
    }
    return hash;
}

Puzzle::Puzzle(vector<int> instance)
    : initial_board(instance),
      priority([](const PuzzleState &state1, const PuzzleState &state2)
               { return state1.getTotalCost() > state2.getTotalCost(); })
{
}

void Puzzle::print_board()
{
    cout << "Board: " << endl;
    for (size_t i = 0; i < initial_board.size(); ++i)
    {
        if (i % 3 == 0 && i != 0)
            cout << endl;
        cout << initial_board[i] << " ";
    }
    cout << endl;
}

vector<char> Puzzle::solve(int &evaluated_states)
{
    PuzzleState initialState(initial_board, {}, 0);
    priority.push(initialState);

    while (!priority.empty())
    {
        PuzzleState current = priority.top();
        priority.pop();

        if (current.stateObjective())
        {
            evaluated_states = visited.size() + priority.size();
            return current.getPath();
        }

        size_t hash = current.generateHash();
        visited.insert(hash);

        vector<PuzzleState> movements = current.generateMovements();
        for (const auto &movement : movements)
        {
            size_t movementHash = movement.generateHash();
            if (visited.find(movementHash) == visited.end())
            {
                priority.push(movement);
            }
        }
    }
    evaluated_states = visited.size() + priority.size();
    return {};
}
