#include <iostream>
#include <vector>
#include "puzzle.h"

using namespace std;







int main(){
 
  try
    {
        string file_name = "instancias.txt";
        Puzzle p(file_name);

    }
    catch (const std::exception &e)
    {
        cerr << "Erro: " << e.what() << endl;
    }

    return 0;


    
}