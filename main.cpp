#include <iostream>
#include <time.h>
#include "ConsoleParameter.h"
#include "SudokuSolution.h"
#include "SudokuPuzzle.h"

using namespace std;

int main(int argc, char *argv[]) {

  clock_t t1, t2;
  t1 = clock();
  ConsoleParameter parameter;
  parameter.Init(argc, argv);

  SudokuSolution puzzle(parameter);
  puzzle.Generate(1000);

  t2 = clock();
  
  cout << ":::::::::::::\n\n\n";
  cout << (double)(t2 - t1) / CLOCKS_PER_SEC << endl;
  
  //system("pause");
  return 0;
}
