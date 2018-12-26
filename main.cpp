#include <iostream>
#include <time.h>
#include "ConsoleParameter.h"
#include "SudokuSolution.h"
#include "SudokuPuzzle.h"

using namespace std;

int main(int argc, char *argv[]) {

  clock_t t1, t2;
  t1 = clock();
  ConsoleParameter parameter;  //��ȡ����̨����
  parameter.Init(argc, argv);
  //����ǺϷ���-c������������
  if (parameter.GetCommand() == 'c' && parameter.GetOperationcode_c() != -1) {
    SudokuSolution puzzle(parameter);
    puzzle.Generate();
    printf("generating sudoku success\n");
  //����ǺϷ���-s�����������
  } else if (parameter.GetCommand() == 's' && parameter.GetOperationcode_s() != "") {
    SudokuPuzzle problem(parameter);
    if (problem.SolveAll() != -1)  //���ɹ�
      printf("solving sudoku success\n");
    else                           //û���κ�һ����������Ľ⡣�����ɽ�����������Ϊ0��
      printf("no solution to the sudokus!!\n");
  //�Ƿ�����̨����
  } else {
    printf("illegal input!\n");
  }
  t2 = clock();
  printf("time passed: ");
  cout << (double)(t2 - t1) / CLOCKS_PER_SEC << " seconds\n";
  
  //system("pause");
  return 0;
}
