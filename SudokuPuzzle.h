#pragma once
#include "ConsoleParameter.h"

//
//����ConsoleParameter���󣬲�����ļ��������������sudoku_answers�ļ�
//
class SudokuPuzzle {
public:
  //��ConsoleParameter��Ĳ�����ʼ��������Ĭ�Ϲ��캯����������ʼ���������ݳ�Ա
  SudokuPuzzle(ConsoleParameter parameter);
  //���ڹر������ļ�
  ~SudokuPuzzle();
  //���ļ��ж�ȡ��һ�������⣬�ɹ�����0��ʧ��-1
  int GetNextPuzzle();
  //����dfs_solve()���⵱ǰpuzzle�д�ŵ�����
  int SolveCurrentPuzzle();
  //��������GetNextPuzzle();��SolveCurrentPuzzle();
  //���ļ��е����������⣬�������sudoku_answers�ļ�
  int SolveAll();
private:
  //���ڸ���puzzle[10][10]��һ���������ѽ����solution[90]
  void dfs_solve(int depth);
  //���ڹ������
  ConsoleParameter parameter;
  //�������⣬0����ո�1~9�к�1~9��Ϊ��Ч����
  int puzzle[10][10];
  //�������Ƿ���ϸ�ʽҪ��
  bool islegal;
  //�������е�0����
  int number_of_blanks;
  //��������ÿ��0��λ�ã���0�±꿪ʼ
  int position_of_blanks[90][2];
  //�������Ľ⣬��0�±꿪ʼ
  int solution[90];
  //�����Ƿ��н�
  bool solvable;
  //�����ļ���ָ��
  FILE *finput;
  //����ļ���ָ��
  FILE *foutput;
  //��ʾ���˼����������������Ϊ��������ļ���ʱ�����ֵ�һ��
  int count;
};
