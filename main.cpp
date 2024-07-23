#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "puzzle.h"

using namespace std;

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
int main()
{
    vector<vector<int>> instances;
    try
    {
        string file_name = "instances.txt";
        file_read(file_name, instances);

        print_instances(instances);
        // passar a primeira instance
        Puzzle puzzle(instances[0]);
        puzzle.print_board();
    }
    catch (const std::exception &e)
    {
        cerr << "Erro: " << e.what() << endl;
    }

    return 0;
}
