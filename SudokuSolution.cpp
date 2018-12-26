#include "SudokuSolution.h"
#include <string>
#include <iostream>
#include <fstream>

#define TOP_LEFT_CORNER_NUMBER 2

using namespace std;

//
//用ConsoleParameter类的parameter来初始化对象
//
SudokuSolution::SudokuSolution(ConsoleParameter parameter) {
  this->parameter = parameter;
}

//
//生成parameter参数中数量的对象，并存至文件
//
void SudokuSolution::Generate() {  // TODO: 多线程和缓冲区？
/*int puzzle[10][10] = {
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, 1, 2, 3, 4, 5, 6, 7, 8, 9},
    {-1, 4, 5, 6, 7, 8, 9, 1, 2, 3},
    {-1, 7, 8, 9, 1, 2, 3, 4, 5, 6},
    {-1, 2, 3, 1, 5, 6, 4, 8, 9, 7},
    {-1, 5, 6, 4, 8, 9, 7, 2, 3, 1},
    {-1, 8, 9, 7, 2, 3, 1, 5, 6, 4},
    {-1, 3, 1, 2, 6, 4, 5, 9, 7, 8},
    {-1, 6, 4, 5, 9, 7, 8, 3, 1, 2},
    {-1, 9, 7, 8, 3, 1, 2, 6, 4, 5} };
  ;*/
  //创建25个基础数独，存在数组里
  GenerateBasicPuzzle();
  //用C++的文件流的话：by fstream: (a bit slower than use C fread/fwrite)
  //======================
  //ofstream outfile;
  //outfile.open("sudoku1.txt", ios::out | ios::trunc);
  //==================================
  FILE *fp;
  errno_t err;
  err = fopen_s(&fp, "sudoku.txt", "w+");
  int count = 0;
  int amount = parameter.GetOperationcode_c();
  int maxcount = amount;
  int n1, n2, n3, n4, n5, n6, n7, n8, n9;
  int sequence[10];
  char outputstring[1005] = "";
  //优化版本1： 用指针操作，代替strcat，因为strcat每次都是从字符串开始处往后，浪费时间
  char *currentpos;

  for (int i = 0; i < 25; i++) {
    n1 = TOP_LEFT_CORNER_NUMBER;
    int puzzle[10][10];            
    for (n2 = 1; n2 <= 9; n2++) {  // ugly...but quicker(?) than recursive function
      if (n2 == n1)  continue;     // probably there isn't much difference?
      for (n3 = 1; n3 <= 9; n3++) {// TODO: try recursive function
        if (n3 == n1 || n3 == n2)  continue;
        for (n4 = 1; n4 <= 9; n4++) {
          if (n4 == n1 || n4 == n2 || n4 == n3)  continue;
          for (n5 = 1; n5 <= 9; n5++) {
            if (n5 == n1 || n5 == n2 || n5 == n3 || n5 == n4)  continue;
            for (n6 = 1; n6 <= 9; n6++) {
              if (n6 == n1 || n6 == n2 || n6 == n3 || n6 == n4 || n6 == n5)  continue;
              for (n7 = 1; n7 <= 9; n7++) {
                if (n7 == n1 || n7 == n2 || n7 == n3 || n7 == n4 || n7 == n5 || n7 == n6) continue;
                for (n8 = 1; n8 <= 9; n8++) {
                  if (n8 == n1 || n8 == n2 || n8 == n3 || n8 == n4 || n8 == n5
                    || n8 == n6 || n8 == n7) {
                    continue;
                  }
                  n9 = 45 - (n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8);
                  currentpos = outputstring;

                  sequence[1] = n1;   sequence[2] = n2;   sequence[3] = n3;  // store in sequence
                  sequence[4] = n4;   sequence[5] = n5;   sequence[6] = n6;
                  sequence[7] = n7;   sequence[8] = n8;   sequence[9] = n9;
                  for (int row = 1; row <= 9; row++) {  //substitute with numbers in sequence[]
                    for (int column = 1; column <= 9; column++) {
                      int basic_value = basic_puzzle[i][row][column];
                      puzzle[row][column] = sequence[basic_value];
                    }
                  }
                  //优化版本1：因为是缓冲区，不初始化也没事，把初始化注释掉了
                  //outputstring[0] = '\0';  // init outputstring as empty string
                  //memset(outputstring, '\0', sizeof(outputstring));
                  if (count != 0) {      // empty line before puzzle
                    //strcat_s(outputstring, sizeof(outputstring), "\n\n\0");
                    *currentpos++ = '\n';
                    *currentpos++ = '\n';
                  }
                  for (int row = 1; row <= 9; row++) {
                    for (int column = 1; column <= 9; column++) {
                      if (column <= 8) {    // 前8列
                        /*char tmpchar[3];
                        tmpchar[0] = puzzle[row][column] + 48;
                        tmpchar[1] = ' ';
                        tmpchar[2] = '\0';
                        strcat_s(outputstring, sizeof(outputstring) , tmpchar);*/
                        *currentpos++ = puzzle[row][column] + 48;
                        *currentpos++ = ' ';
                        
                      } else if (row <= 8) {   //第9列前8行
                        /*char tmpchar[3];
                        tmpchar[0] = puzzle[row][column] + 48;
                        tmpchar[1] = '\n';
                        tmpchar[2] = '\0';
                        strcat_s(outputstring, sizeof(outputstring), tmpchar);*/
                        *currentpos++ = puzzle[row][column] + 48;
                        *currentpos++ = '\n';
                      } else {    //右下角的数
                        /*char tmpchar[2];
                        tmpchar[0] = puzzle[row][column] + 48;
                        tmpchar[1] = '\0';
                        strcat_s(outputstring, sizeof(outputstring) , tmpchar);*/
                        *currentpos++ = puzzle[row][column] + 48;
                      }
                    }
                  }
                  //将缓冲区中的整个数独的字符串写入文件
                  *currentpos++ = '\0';
                  fwrite(outputstring, sizeof(char) * (strlen(outputstring)), 1, fp);
                  //==================================
                  //outfile << outputstring;
                  //==================================
                  count++;
                  if (count == maxcount) {
                    return;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  if (fp != NULL)
    fclose(fp);
  //=======================
  //outfile.close();
  //========================
}

//
//生成parameter参数中数量的对象，并存至文件
//重载，生成指定数量的数独，不受限于parameter
//
void SudokuSolution::Generate(int amount) {  
  //创建25个基础数独，存在数组里
  GenerateBasicPuzzle();
  //用C++的文件流的话：by fstream: (a bit slower than use C fread/fwrite)
  //======================
  //ofstream outfile;
  //outfile.open("sudoku1.txt", ios::out | ios::trunc);
  //==================================
  FILE *fp;
  errno_t err;
  err = fopen_s(&fp, "sudoku.txt", "w+");
  int count = 0;
  //int amount = parameter.GetOperationcode_c();
  int maxcount = amount;
  int n1, n2, n3, n4, n5, n6, n7, n8, n9;
  int sequence[10];
  char outputstring[1005] = "";
  //优化版本1： 用指针操作，代替strcat，因为strcat每次都是从字符串开始处往后，浪费时间
  char *currentpos;

  for (int i = 0; i < 25; i++) {
    n1 = TOP_LEFT_CORNER_NUMBER;
    int puzzle[10][10];            
    for (n2 = 1; n2 <= 9; n2++) {  // ugly...but quicker(?) than recursive function
      if (n2 == n1)  continue;     // probably there isn't much difference?
      for (n3 = 1; n3 <= 9; n3++) {// TODO: try recursive function
        if (n3 == n1 || n3 == n2)  continue;
        for (n4 = 1; n4 <= 9; n4++) {
          if (n4 == n1 || n4 == n2 || n4 == n3)  continue;
          for (n5 = 1; n5 <= 9; n5++) {
            if (n5 == n1 || n5 == n2 || n5 == n3 || n5 == n4)  continue;
            for (n6 = 1; n6 <= 9; n6++) {
              if (n6 == n1 || n6 == n2 || n6 == n3 || n6 == n4 || n6 == n5)  continue;
              for (n7 = 1; n7 <= 9; n7++) {
                if (n7 == n1 || n7 == n2 || n7 == n3 || n7 == n4 || n7 == n5 || n7 == n6) continue;
                for (n8 = 1; n8 <= 9; n8++) {
                  if (n8 == n1 || n8 == n2 || n8 == n3 || n8 == n4 || n8 == n5
                    || n8 == n6 || n8 == n7) {
                    continue;
                  }
                  n9 = 45 - (n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8);
                  currentpos = outputstring;

                  sequence[1] = n1;   sequence[2] = n2;   sequence[3] = n3;  // store in sequence
                  sequence[4] = n4;   sequence[5] = n5;   sequence[6] = n6;
                  sequence[7] = n7;   sequence[8] = n8;   sequence[9] = n9;
                  for (int row = 1; row <= 9; row++) {  //substitute with numbers in sequence[]
                    for (int column = 1; column <= 9; column++) {
                      int basic_value = basic_puzzle[i][row][column];
                      puzzle[row][column] = sequence[basic_value];
                    }
                  }
                  //优化版本1：因为是缓冲区，不初始化也没事，把初始化注释掉了
                  //outputstring[0] = '\0';  // init outputstring as empty string
                  //memset(outputstring, '\0', sizeof(outputstring));
                  if (count != 0) {      // empty line before puzzle
                    //strcat_s(outputstring, sizeof(outputstring), "\n\n\0");
                    *currentpos++ = '\n';
                    *currentpos++ = '\n';
                  }
                  for (int row = 1; row <= 9; row++) {
                    for (int column = 1; column <= 9; column++) {
                      if (column <= 8) {    // 前8列
                        /*char tmpchar[3];
                        tmpchar[0] = puzzle[row][column] + 48;
                        tmpchar[1] = ' ';
                        tmpchar[2] = '\0';
                        strcat_s(outputstring, sizeof(outputstring) , tmpchar);*/
                        *currentpos++ = puzzle[row][column] + 48;
                        *currentpos++ = ' ';
                        
                      } else if (row <= 8) {   //第9列前8行
                        /*char tmpchar[3];
                        tmpchar[0] = puzzle[row][column] + 48;
                        tmpchar[1] = '\n';
                        tmpchar[2] = '\0';
                        strcat_s(outputstring, sizeof(outputstring), tmpchar);*/
                        *currentpos++ = puzzle[row][column] + 48;
                        *currentpos++ = '\n';
                      } else {    //右下角的数
                        /*char tmpchar[2];
                        tmpchar[0] = puzzle[row][column] + 48;
                        tmpchar[1] = '\0';
                        strcat_s(outputstring, sizeof(outputstring) , tmpchar);*/
                        *currentpos++ = puzzle[row][column] + 48;
                      }
                    }
                  }
                  //将缓冲区中的整个数独的字符串写入文件
                  *currentpos++ = '\0';
                  fwrite(outputstring, sizeof(char) * (strlen(outputstring)), 1, fp);
                  //==================================
                  //outfile << outputstring;
                  //==================================
                  count++;
                  if (count == maxcount) {
                    return;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  if (fp != NULL)
    fclose(fp);
  //=======================
  //outfile.close();
  //========================
}

//
//生成25个基础数独（不能通过1到9的排列使之相同的，算不同的数独）
//被Generate()调用
//
void SudokuSolution::GenerateBasicPuzzle() { 
  /*int puzzle[25][10][10] = { {   // example puzzle
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, 1, 2, 3, 4, 5, 6, 7, 8, 9},
    {-1, 4, 5, 6, 7, 8, 9, 1, 2, 3},
    {-1, 7, 8, 9, 1, 2, 3, 4, 5, 6},
    {-1, 2, 3, 1, 5, 6, 4, 8, 9, 7},
    {-1, 5, 6, 4, 8, 9, 7, 2, 3, 1},
    {-1, 8, 9, 7, 2, 3, 1, 5, 6, 4},
    {-1, 3, 1, 2, 6, 4, 5, 9, 7, 8},
    {-1, 6, 4, 5, 9, 7, 8, 3, 1, 2},
    {-1, 9, 7, 8, 3, 1, 2, 6, 4, 5} } };*/
  int sequence456[6][3] = { {4, 5, 6}, {4, 6, 5}, {5, 4, 6}, {5, 6, 4}, {6, 4, 5} };
  int sequence789[6][3] = { {7, 8, 9}, {7, 9, 8}, {8, 7, 9}, {8, 9, 7}, {9, 7, 8} };
  int sequence123[3] = { 1, 2, 3 };
  for (int i = 0; i < 5; i++) { // i: choose in sequence456
    for (int j = 0; j < 5; j++) {  //j: choose in sequence 567
      int count = i * 5 + j;
      for (int k = 1; k <= 9; k++)  // fill first row with 123456789
        basic_puzzle[count][1][k] = k;
      for (int k = 0; k < 3; k++) { // loop for sequence, fill 2~3rd rows
        basic_puzzle[count][2][1 + k] = basic_puzzle[count][3][7 + k] = sequence456[i][k];
        basic_puzzle[count][3][1 + k] = basic_puzzle[count][2][4 + k] = sequence789[j][k];
        basic_puzzle[count][3][4 + k] = basic_puzzle[count][2][7 + k] = sequence123[k];
      }
      for (int row = 4; row <= 6; row++) {  // fill 4~6 rows, right shift 1
        for (int column = 1; column <= 9; column++) {
          if (column % 3 != 0) {
            basic_puzzle[count][row][column] = basic_puzzle[count][row - 3][column + 1];
          } else if(column % 3 == 0 && column > 2){
            basic_puzzle[count][row][column] = basic_puzzle[count][row - 3][column - 2];
          }
        }
      }
      for (int row = 7; row <= 9; row++) {  // fill 7~9 rows, right shift 1
        for (int column = 1; column <= 9; column++) {
          if (column % 3 != 0) {
            basic_puzzle[count][row][column] = basic_puzzle[count][row - 3][column + 1];
          } else if(column % 3 == 0 && column > 2) {
            basic_puzzle[count][row][column] = basic_puzzle[count][row - 3][column - 2];
          }
        }
      }
    }
  }
}

