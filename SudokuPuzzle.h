#pragma once
#include "ConsoleParameter.h"
class SudokuPuzzle {
public:
  SudokuPuzzle(ConsoleParameter parameter);
  void Generate();
private:
// generate 25 basic puzzle that the first row is 123456789,
// so that can generate 25 * 8! = 1008000 puzzles later on
  void GenerateBasicPuzzle();

  ConsoleParameter parameter;
  int basic_puzzle[25][10][10];
};


