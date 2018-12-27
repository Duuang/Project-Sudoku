#include "SudokuPuzzle.h"
#include <iostream>
#include <string>

using namespace std;

//
//用ConsoleParameter类的参数初始化对象（无默认构造函数），并初始化所有数据成员
//
SudokuPuzzle::SudokuPuzzle(ConsoleParameter parameter) {
  //初始化数据成员
  this->parameter = parameter;
  memset(puzzle, -1, sizeof(puzzle));
  islegal = false;
  number_of_blanks = -1;
  memset(position_of_blanks, -1, sizeof(position_of_blanks));
  solvable = false;
  errno_t err;
  //err = fopen_s(&finput, "C:\\Users\\cky\\source\\repos\\Project9\\Project9\\problems.txt", "r");
  err = fopen_s(&finput, parameter.GetOperationcode_s().c_str(), "r");
  if (finput == NULL)
    printf("打开数独题的输入文件失败\n");
  err = fopen_s(&foutput, "solution_of_puzzles.txt", "w");
  if (foutput == NULL)
    printf("打开数独解的输出文件失败\n");
  count = 0;
}

//
//用于关闭两个文件
//
SudokuPuzzle::~SudokuPuzzle() {
  if (finput != NULL)
    fclose(finput);  //由于用了errno_t，好像不用判断是否为空指针了（至少没报warning..）
  if (foutput != NULL)
    fclose(foutput);
}

//
//从文件中读取下一个数独题，成功返回0，失败-1
//
int SudokuPuzzle::GetNextPuzzle() {
  if (finput == NULL || foutput == NULL)  //如果打开文件失败，则无法继续
    return -2;
  char tmpchar;  //按字符读取文件，存到tmpchar
  int count_charsgot = 0;  //记录已读取的0~9的字符数
  number_of_blanks = 0;  //记录为'0'的数目，初始化
  solvable = false;
  islegal = false;
  while (true) {
    if (count_charsgot == 81) {  //如果读取完了81个0~9，则数独读取完毕，函数返回0，正常结束
      islegal = true;
      count++;
      return 0;
    }
    tmpchar = fgetc(finput);
    if (feof(finput)) {  //读取到文件结束的EOF，则结束函数，并且没读到81个，说明错误
      islegal = false;
      return -1;
    }
    //如果为0~9，则将81个数字赋值至puzzle[10][10]
    if (tmpchar >= '0' && tmpchar <= '9') {
      count_charsgot++;
      int row = (count_charsgot - 1)/ 9 + 1;
      int column = (count_charsgot - 1) % 9 + 1;
      puzzle[row][column] = tmpchar - 48;
      if (tmpchar == '0') {
        position_of_blanks[number_of_blanks][0] = row;
        position_of_blanks[number_of_blanks][1] = column;
        number_of_blanks++;
      }
    }
  }
  count++;
  islegal = true;
  return 0;
}

//
//反复调用GetNextPuzzle();、SolveCurrentPuzzle();
//解文件中的所有数独题，并输出到sudoku_answers文件
//
int SudokuPuzzle::SolveAll() {
  if (finput == NULL || foutput == NULL)  //如果打开文件失败，则无法继续
    return -2;
  int solved_count = 0;
  while (true) {
    if (GetNextPuzzle() != 0)
      break;
    if (SolveCurrentPuzzle() != 0) {
      continue;   //无解的情况
    }
    solved_count++;  //有解，已解的数目加1
  }
  return solved_count;
}

//
//调用dfs_solve()，解当前puzzle中存放的数独
//
int SudokuPuzzle::SolveCurrentPuzzle() {
  if (finput == NULL || foutput == NULL)  //如果打开文件失败，则无法继续
    return -2;
  if (!islegal) {
    return -1;
  } else {
    //在解数独前，还要先判断，已经给的数独题中有没有本来就冲突的地方
    //如果有的话，那不用解了，直接输出无解即可
    for (int row = 1; row <= 9; row++) {
      for (int column = 1; column <= 9; column++) {
        if (puzzle[row][column] == 0)
          continue;
        for (int i = 1; i <= 9; i++) {  //判断是否和行或列重复
          if ((i != row && puzzle[i][column] == puzzle[row][column])
            || (i != column && puzzle[row][i] == puzzle[row][column])) {  //重复了
            solvable = false;
            return -1;
          }
        }
        for (int k1 = 0; k1 < 3; k1++)
          for (int k2 = 0; k2 < 3; k2++) {  //判断是否和9宫格中的重复
            int baserow = (row - 1) / 3 * 3 + 1;
            int basecolumn = (column - 1) / 3 * 3 + 1;
            if (puzzle[baserow + k1][basecolumn + k2] == puzzle[row][column]
              && (baserow + k1 != row && basecolumn + k2 != column)) {
              solvable = false;
              return -1;
            }
          }
      }
    }
    //现在数独一定有解了。。
    dfs_solve(1);
    if (solvable) {  //直接将puzzle中的0替换为solution数组中的解，然后输出到文件即可（其实和生成数独的输出部分一样）
      char outputstring[1005] = { '\0' };  //缓冲区
      if (count >= 2)
        strcat_s(outputstring, sizeof(outputstring), "\n\n\0");  //若不是第一个，则先输出空行
      int solution_count = 0;
      for (int row = 1; row <= 9; row++)
        for (int column = 1; column <= 9; column++) {
          //前8列
          if (column <= 8) {  
            char tmpchar[3];
            if (puzzle[row][column] != 0) {  //不为0，直接输出
              tmpchar[0] = puzzle[row][column] + 48;
            }
            else {  //为0，替换成solution数组中的解
              tmpchar[0] = solution[solution_count] + 48;
              solution_count++;
            }
            tmpchar[1] = ' ';
            tmpchar[2] = '\0';
            strcat_s(outputstring, sizeof(outputstring), tmpchar);  //加入到缓冲区
            //第9列，前8行
          } else if (row <= 8) {  
            char tmpchar[3];
            if (puzzle[row][column] != 0) {
              tmpchar[0] = puzzle[row][column] + 48;
            }
            else {
              tmpchar[0] = solution[solution_count] + 48;
              solution_count++;
            }
            tmpchar[1] = '\n';
            tmpchar[2] = '\0';
            strcat_s(outputstring, sizeof(outputstring), tmpchar);
            //右下角
          } else {
            char tmpchar[2];
            if (puzzle[row][column] != 0) {
              tmpchar[0] = puzzle[row][column] + 48;
            }
            else {
              tmpchar[0] = solution[solution_count] + 48;
              solution_count++;
            }
            tmpchar[1] = '\0';
            strcat_s(outputstring, sizeof(outputstring), tmpchar);
          }
        }
      //从缓冲区输出到文件
      fwrite(outputstring, sizeof(char) * (strlen(outputstring)), 1, foutput);
      return 0;
    } else {
      return -1;
    }
  }
}

//
//用于根据puzzle[10][10]解一个数独，把解存至solution[90]
//用的是回溯法，枚举
//TODO: 加剪枝条件、启发式函数，提升速度
//
void SudokuPuzzle::dfs_solve(int depth) {
  if (solvable)
    return;
  if (depth > number_of_blanks) {  //终止条件，如果深度大于了空白的个数，为可行解，置solvable为true
    solvable = true;
    return;
  } else {
    for (int i = 1; i <= 9; i++) {  //遍历1~9的节点
      for (int j = 1; j <= 9; j++) {  //如果和行或列重复
        if ((j != position_of_blanks[depth - 1][0]) && (puzzle[j][position_of_blanks[depth - 1][1]] == i)
          || (j != position_of_blanks[depth - 1][1]) && (puzzle[position_of_blanks[depth - 1][0]][j] == i)) {
          goto continue_next_branch;  //do nothing and stop searching this branch
        }
      }
      for (int k1 = 0; k1 < 3; k1++)
        for (int k2 = 0; k2 < 3; k2++) {  //如果和9宫格中的重复
          int baserow = (position_of_blanks[depth - 1][0] - 1) / 3 * 3 + 1;
          int basecolumn = (position_of_blanks[depth - 1][1] - 1) / 3 * 3 + 1;
          if (puzzle[baserow + k1][basecolumn + k2] == i && baserow + k1 != position_of_blanks[depth - 1][0] 
            && basecolumn + k2 != position_of_blanks[depth - 1][1])
            goto continue_next_branch;  //do nothing and stop searching this branch
        }
      solution[depth - 1] = i;  //记录当前节点解
      puzzle[position_of_blanks[depth - 1][0]][position_of_blanks[depth - 1][1]] = i;
      dfs_solve(depth + 1);   //递归回溯
      //solution[depth - 1] = 0;
      puzzle[position_of_blanks[depth - 1][0]][position_of_blanks[depth - 1][1]] = 0;
      if (solvable)  // !! 之前调试了半天。。原来是这没跳出。。都解完了一个解了还接着循环呢。。
        break;
      continue_next_branch:  ;  //do nothing and stop searching this branch
    }
  }
}
