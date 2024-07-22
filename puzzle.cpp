#include "puzzle.h"
#include <iostream>
#include <fstream>
#include <sstream>

Puzzle::Puzzle(string &file_name)
{
   string line;

    ifstream inputFile(file_name);
    if (!inputFile)
    {
        cerr << "Erro ao abrir o arquivo." << endl;
        throw runtime_error("Erro ao abrir o arquivo.");
    }

   
}