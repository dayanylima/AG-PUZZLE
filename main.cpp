#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include "puzzle.h"

using namespace std;
using namespace chrono;

void file_read(const string &file_name, vector<vector<int>> &instances)
{
    string line;
    ifstream inputFile(file_name);
    if (!inputFile)
    {
        cerr << "Erro ao abrir o arquivo." << endl;
        throw runtime_error("Erro ao abrir o arquivo.");
    }
    while (getline(inputFile, line))
    {
        stringstream ss(line);
        int aux;
        vector<int> instances_aux;
        while (ss >> aux)
        {
            instances_aux.push_back(aux);
        }
        instances.push_back(instances_aux);
    }
    inputFile.close();
}

void print_instances(const vector<vector<int>> &instances)
{
    for (const auto &instance : instances)
    {
        for (int value : instance)
        {
            cout << value << " ";
        }
        cout << endl;
    }
}

void print_board(const vector<int> &board)
{
    for (int i = 0; i < 9; i++)
    {
        cout << board[i] << " ";
        if ((i + 1) % 3 == 0)
        {
            cout << endl;
        }
    }
}

void finalSolution(const vector<char> &solution, const vector<int> &initial_board)
{
    cout << "Numero de passos: " << solution.size() << endl;
    for (char s : solution)
    {
        cout << s << " ";
    }
    cout << endl;

    cout << "Tabuleiro inicial:" << endl;
    print_board(initial_board);
    cout << endl;

    cout << "Movimentos:" << endl;
    vector<int> current_board = initial_board;
    int zero_index = find(current_board.begin(), current_board.end(), 0) - current_board.begin();
    int x, y;

    for (char s : solution)
    {
        x = zero_index % 3;
        y = zero_index / 3;

        switch (s)
        {
        case 'U': // UP
            if (y > 0)
            {
                swap(current_board[zero_index], current_board[zero_index - 3]);
                zero_index -= 3;
            }
            break;
        case 'D': // DOWN
            if (y < 2)
            {
                swap(current_board[zero_index], current_board[zero_index + 3]);
                zero_index += 3;
            }
            break;
        case 'L': // LEFT
            if (x > 0)
            {
                swap(current_board[zero_index], current_board[zero_index - 1]);
                zero_index -= 1;
            }
            break;
        case 'R': // RIGHT
            if (x < 2)
            {
                swap(current_board[zero_index], current_board[zero_index + 1]);
                zero_index += 1;
            }
            break;
        }

        cout << "Movimento " << s << ":" << endl;
        print_board(current_board);
        cout << endl;
    }
}

int main()
{
    vector<vector<int>> instances;
    try
    {
        string file_name = "instances.txt";
        file_read(file_name, instances);
        int evaluated_states = 0; // estados avaliados

        // Passe a primeira instância
        Puzzle puzzle(instances[0]);

        auto start_time = high_resolution_clock::now(); // Início da medição do tempo
        vector<char> solution = puzzle.solve(evaluated_states);
        auto end_time = high_resolution_clock::now(); // Fim da medição do tempo

        finalSolution(solution, instances[0]);

        auto duration = duration_cast<milliseconds>(end_time - start_time).count();
        cout << "Tempo de execucao: " << duration << " ms" << endl;
        cout << "Estados avaliados: " << evaluated_states << endl;
    }
    catch (const std::exception &e)
    {
        cerr << "Erro: " << e.what() << endl;
    }

    return 0;
}
