#include <iostream>
#include <time.h>
#include "ConsoleParameter.h"
#include "SudokuSolution.h"
#include "SudokuPuzzle.h"

using namespace std;

int main(int argc, char *argv[]) {
  printf("\n");
  clock_t t1, t2;
  t1 = clock();
  ConsoleParameter parameter;  //获取控制台参数
  parameter.Init(argc, argv);
  //如果控制台输入是合法的-c，则生成数独
  if (parameter.GetCommand() == 'c' && parameter.GetOperationcode_c() != -1) {
    SudokuSolution puzzle(parameter);
    puzzle.Generate();
    printf("成功生成数独，在当前目录的 sudoku.txt 中\n");
  //如果控制台输入是合法的-s，则求解数独
  } else if (parameter.GetCommand() == 's' && parameter.GetOperationcode_s() != "") {
    SudokuPuzzle problem(parameter);
    int solved_count = problem.SolveAll();
    //文件打开没有出错
    if (solved_count != -2) {  
      printf("数独已全部解完，有解的数独已经依次写入当前目录的 solution_of_puzzles.txt 中\n");
      printf("有解的数独个数：%d\n", solved_count);
      printf("无解的数独个数：%d\n", problem.count - solved_count);
    //如果文件打开出错
    } else {  
      ;  //错误信息在SudokuPuzzle类的构造函数中已经输出到控制台
    }
  //非法控制台输入
  } else {
    printf("非法的输入！\n");
  }
  t2 = clock();
  printf("-----------------------------------------------\n");
  printf("time passed: ");
  cout << (double)(t2 - t1) / CLOCKS_PER_SEC << " seconds\n";
  
  //system("pause");
  return 0;
}
