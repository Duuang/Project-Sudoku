#include <iostream>
#include "ConsoleParameter.h"
#include "SudokuPuzzle.h"
using namespace std;

int main(int argc, char *argv[]) {
  ConsoleParameter parameter;
  SudokuPuzzle puzzle_generate(parameter);
  puzzle_generate.Generate();

  
  system("pause");
  return 0;
}

// path:
//C:\Users\cky\source\repos\Project6\Debug