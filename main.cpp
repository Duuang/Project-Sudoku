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
  ConsoleParameter parameter;  //��ȡ����̨����
  parameter.Init(argc, argv);
  //�������̨�����ǺϷ���-c������������
  if (parameter.GetCommand() == 'c' && parameter.GetOperationcode_c() != -1) {
    SudokuSolution puzzle(parameter);
    puzzle.Generate();
    printf("�ɹ������������ڵ�ǰĿ¼�� sudoku.txt ��\n");
  //�������̨�����ǺϷ���-s�����������
  } else if (parameter.GetCommand() == 's' && parameter.GetOperationcode_s() != "") {
    SudokuPuzzle problem(parameter);
    int solved_count = problem.SolveAll();
    //�ļ���û�г���
    if (solved_count != -2) {  
      printf("������ȫ�����꣬�н�������Ѿ�����д�뵱ǰĿ¼�� solution_of_puzzles.txt ��\n");
      printf("�н������������%d\n", solved_count);
      printf("�޽������������%d\n", problem.count - solved_count);
    //����ļ��򿪳���
    } else {  
      ;  //������Ϣ��SudokuPuzzle��Ĺ��캯�����Ѿ����������̨
    }
  //�Ƿ�����̨����
  } else {
    printf("�Ƿ������룡\n");
  }
  t2 = clock();
  printf("-----------------------------------------------\n");
  printf("time passed: ");
  cout << (double)(t2 - t1) / CLOCKS_PER_SEC << " seconds\n";
  
  //system("pause");
  return 0;
}
