#pragma once
#include "ConsoleParameter.h"

//
//接收ConsoleParameter对象，并生成数独，输出到文件
//
class SudokuSolution {
public:
  //用ConsoleParameter类的parameter来初始化对象
  SudokuSolution(ConsoleParameter parameter);
  //生成parameter参数中数量的对象，并存至文件
  void Generate();
private:
  //生成25个基础数独（不能通过1到9的排列使之相同的，算不同的数独）
  //被Generate()调用
  void GenerateBasicPuzzle();
  //用于初始化对象
  ConsoleParameter parameter;
  //存放25个基础数独，下标从0开始
  int basic_puzzle[25][10][10];
};


