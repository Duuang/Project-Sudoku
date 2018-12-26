#pragma once
#include "ConsoleParameter.h"

//
//接收ConsoleParameter对象，并求解文件中数独，输出到sudoku_answers文件
//
class SudokuPuzzle {
public:
  //用ConsoleParameter类的参数初始化对象（无默认构造函数），并初始化所有数据成员
  SudokuPuzzle(ConsoleParameter parameter);
  //用于关闭两个文件
  ~SudokuPuzzle();
  //从文件中读取下一个数独题，成功返回0，失败-1
  int GetNextPuzzle();
  //调用dfs_solve()，解当前puzzle中存放的数独
  int SolveCurrentPuzzle();
  //反复调用GetNextPuzzle();、SolveCurrentPuzzle();
  //解文件中的所有数独题，并输出到sudoku_answers文件
  int SolveAll();
private:
  //用于根据puzzle[10][10]解一个数独，把解存至solution[90]
  void dfs_solve(int depth);
  //用于构造对象
  ConsoleParameter parameter;
  //存数独题，0代表空格，1~9行和1~9列为有效数据
  int puzzle[10][10];
  //数独题是否符合格式要求
  bool islegal;
  //数独题中的0个数
  int number_of_blanks;
  //数独题中每个0的位置，从0下标开始
  int position_of_blanks[90][2];
  //存数独的解，从0下标开始
  int solution[90];
  //数独是否有解
  bool solvable;
  //输入文件的指针
  FILE *finput;
  //输出文件的指针
  FILE *foutput;
  //表示读了几个题进来，纯粹是为了输出到文件的时候区分第一个
  int count;
};
