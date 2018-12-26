#include <iostream>
#include <time.h>
#include "ConsoleParameter.h"
#include "SudokuSolution.h"
#include "SudokuPuzzle.h"

using namespace std;

int main(int argc, char *argv[]) {

  clock_t t1, t2, t3;
  t1 = clock();
  ConsoleParameter parameter;
  parameter.Init(argc, argv);

  SudokuSolution puzzle(parameter);
  puzzle.Generate();
  t2 = clock();
  SudokuPuzzle problem(parameter);
  problem.SolveAll();

  t3 = clock();
  
  cout << ":::::::::::::\n\n\n";
  cout << (double)(t2 - t1) / CLOCKS_PER_SEC << endl;
  cout << (double)(t3 - t2) / CLOCKS_PER_SEC << endl;
  
  
  //system("pause");
  return 0;
}
