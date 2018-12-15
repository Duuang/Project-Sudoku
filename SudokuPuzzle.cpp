#include "SudokuPuzzle.h"
#include <string>
#include <iostream>

#define TOP_LEFT_CORNER_NUMBER 2

using namespace std;

struct Position { // denotes the position of certain number in puzzle
  int row, column;
};

SudokuPuzzle::SudokuPuzzle(ConsoleParameter parameter) {
  this->parameter = parameter;
}

void SudokuPuzzle::Generate() {  // TODO: use muti-thread and buffer?
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
  Position pos[9][9][2] = { { {1, 1}, {2, 7}, {3, 4}, {4, 3}, {5, 9}, {6, 6}, {7, 2}, {8, 8}, {9, 5} }
                          , { {1, 2}, {2, 8}, {3, 5}, {4, 1}, {5, 7}, {6, 4}, {7, 3}, {8, 9}, {9, 6} }
                          , { {1, 3}, {2, 9}, {3, 6}, {4, 2}, {5, 8}, {6, 5}, {7, 1}, {8, 7}, {9, 4} }
                          , { {1, 4}, {2, 1}, {3, 7}, {4, 6}, {5, 3}, {6, 9}, {7, 5}, {8, 2}, {9, 8} }
                          , { {1, 5}, {2, 2}, {3, 8}, {4, 4}, {5, 1}, {6, 7}, {7, 6}, {8, 3}, {9, 9} }
                          , { {1, 6}, {2, 3}, {3, 9}, {4, 5}, {5, 2}, {6, 8}, {7, 4}, {8, 1}, {9, 7} }
                          , { {1, 7}, {2, 4}, {3, 1}, {4, 9}, {5, 6}, {6, 3}, {7, 8}, {8, 5}, {9, 2} }
                          , { {1, 8}, {2, 5}, {3, 2}, {4, 7}, {5, 4}, {6, 1}, {7, 9}, {8, 6}, {9, 3} }
                          , { {1, 9}, {2, 6}, {3, 3}, {4, 8}, {5, 5}, {6, 2}, {7, 7}, {8, 4}, {9, 1} } };*/
  
  GenerateBasicPuzzle();
  FILE *fp;
  errno_t err;
  err = fopen_s(&fp, "sudoku.txt", "a+");
  int count = 0;
  int maxcount = parameter.GetOperationcode_c();
  int n1, n2, n3, n4, n5, n6, n7, n8, n9;
  int sequence[10];
  char outputstring[1005] = "\0";
  for (int i = 0; i < 25; i++) {
    n1 = TOP_LEFT_CORNER_NUMBER;
    int puzzle[10][10];
    for (n2 = 1; n2 <= 9; n2++) {  // ugly...but quicker(?) than recursive function
      if (n2 == n1)  continue;     // probably there isn't much difference?
      for (n3 = 1; n3 <= 9; n3++) {// TODO: try recursive function
        if (n3 == n1 || n3 == n2)  break;
        for (n4 = 1; n4 <= 9; n4++) {
          if (n4 == n1 || n4 == n2 || n4 == n3)  break;
          for (n5 = 1; n5 <= 9; n5++) {
            if (n5 == n1 || n5 == n2 || n5 == n3 || n5 == n4)  break;
            for (n6 = 1; n6 <= 9; n6++) {
              if (n6 == n1 || n6 == n2 || n6 == n3 || n6 == n4 || n6 == n5)  break;
              for (n7 = 1; n7 <= 9; n7++) {
                if (n7 == n1 || n7 == n2 || n7 == n3 || n7 == n4 || n7 == n5 || n7 == n6) break;
                for (n8 = 1; n8 <= 9; n8++) {
                  if (n8 == n1 || n8 == n2 || n8 == n3 || n8 == n4 || n8 == n5
                    || n8 == n6 || n8 == n7) {
                    break;
                  }
                  n9 = 45 - (n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8);
                  sequence[1] = n1;   sequence[2] = n2;   sequence[3] = n3;  // store in sequence
                  sequence[4] = n4;   sequence[5] = n5;   sequence[6] = n6;
                  sequence[7] = n7;   sequence[8] = n8;   sequence[9] = n9;
                  for (int row = 1; row <= 9; row++) {  //substitute with numbers in sequence[]
                    for (int column = 1; column <= 9; column++) {
                      int basic_value = basic_puzzle[i][row][column];
                      puzzle[row][column] = sequence[basic_value];
                    }
                  }
                  outputstring[0] = '\0';  // init outputstring as empty string
                  if (count != 0)          // empty line before puzzle
                    strcat_s(outputstring, sizeof("\n"), "\n");
                  for (int row = 1; row <= 9; row++) {
                    for (int column = 1; column <= 9; column++) {
                      if (column <= 8) {
                        char tmpchar[3];
                        tmpchar[0] = puzzle[row][column] + 48;
                        tmpchar[1] = ' ';
                        tmpchar[2] = '\0';
                        strcat_s(outputstring, sizeof(tmpchar), tmpchar);
                      } else if (row <= 8) {
                        char tmpchar[3];
                        tmpchar[0] = puzzle[row][column] + 48;
                        tmpchar[1] = '\n';
                        tmpchar[2] = '\0';
                        strcat_s(outputstring, sizeof(tmpchar), tmpchar);
                      } else {
                        char tmpchar[2];
                        tmpchar[0] = puzzle[row][column] + 48;
                        tmpchar[1] = '\0';
                        strcat_s(outputstring, sizeof(tmpchar), tmpchar);
                      }
                    }
                  }
                  fwrite(outputstring, sizeof(char) * (strlen(outputstring) + 1), 1, fp);

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
  fclose(fp);
}



//
// generate 25 basic puzzle that the first row is 123456789,
// so that can generate 25 * 8! = 1008000 puzzles later on
//
void SudokuPuzzle::GenerateBasicPuzzle() { 
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
          } else {
            basic_puzzle[count][row][column] = basic_puzzle[count][row - 3][column - 2];
          }
        }
      }
      for (int row = 7; row <= 9; row++) {  // fill 7~9 rows, right shift 1
        for (int column = 1; column <= 9; column++) {
          if (column % 3 != 0) {
            basic_puzzle[count][row][column] = basic_puzzle[count][row - 3][column + 1];
          } else {
            basic_puzzle[count][row][column] = basic_puzzle[count][row - 3][column - 2];
          }
        }
      }
    }
  }
}

