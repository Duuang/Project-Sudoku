#include <iostream>
#include <time.h>
#include "ConsoleParameter.h"
#include "SudokuSolution.h"
#include "SudokuPuzzle.h"

using namespace std;

int main(int argc, char *argv[]) {

  clock_t t1, t2;
  t1 = clock();
  ConsoleParameter parameter;  //获取控制台参数
  parameter.Init(argc, argv);
  //如果是合法的-c，则生成数独
  if (parameter.GetCommand() == 'c' && parameter.GetOperationcode_c() != -1) {
    SudokuSolution puzzle(parameter);
    puzzle.Generate();
    printf("generating sudoku success\n");
  //如果是合法的-s，则求解数独
  } else if (parameter.GetCommand() == 's' && parameter.GetOperationcode_s() != "") {
    SudokuPuzzle problem(parameter);
    if (problem.SolveAll() != -1)  //求解成功
      printf("solving sudoku success\n");
    else                           //没有任何一个可以输出的解。。（可解的数独题个数为0）
      printf("no solution to the sudokus!!\n");
  //非法控制台输入
  } else {
    printf("illegal input!\n");
  }
  t2 = clock();
  printf("time passed: ");
  cout << (double)(t2 - t1) / CLOCKS_PER_SEC << " seconds\n";
  
  //system("pause");
  return 0;
}
