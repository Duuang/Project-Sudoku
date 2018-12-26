#pragma once
#include "ConsoleParameter.h"

//
//����ConsoleParameter���󣬲�����������������ļ�
//
class SudokuSolution {
public:
  //��ConsoleParameter���parameter����ʼ������
  SudokuSolution(ConsoleParameter parameter);
  //����parameter�����������Ķ��󣬲������ļ�
  void Generate();
private:
  //����25����������������ͨ��1��9������ʹ֮��ͬ�ģ��㲻ͬ��������
  //��Generate()����
  void GenerateBasicPuzzle();
  //���ڳ�ʼ������
  ConsoleParameter parameter;
  //���25�������������±��0��ʼ
  int basic_puzzle[25][10][10];
};


