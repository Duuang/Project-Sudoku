#include "SudokuPuzzle.h"
#include <iostream>
#include <string>

using namespace std;

//
//��ConsoleParameter��Ĳ�����ʼ��������Ĭ�Ϲ��캯����������ʼ���������ݳ�Ա
//
SudokuPuzzle::SudokuPuzzle(ConsoleParameter parameter) {
  //��ʼ�����ݳ�Ա
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
    printf("��������������ļ�ʧ��\n");
  err = fopen_s(&foutput, "solution_of_puzzles.txt", "w");
  if (foutput == NULL)
    printf("�������������ļ�ʧ��\n");
  count = 0;
}

//
//���ڹر������ļ�
//
SudokuPuzzle::~SudokuPuzzle() {
  if (finput != NULL)
    fclose(finput);  //��������errno_t���������ж��Ƿ�Ϊ��ָ���ˣ�����û��warning..��
  if (foutput != NULL)
    fclose(foutput);
}

//
//���ļ��ж�ȡ��һ�������⣬�ɹ�����0��ʧ��-1
//
int SudokuPuzzle::GetNextPuzzle() {
  if (finput == NULL || foutput == NULL)  //������ļ�ʧ�ܣ����޷�����
    return -2;
  char tmpchar;  //���ַ���ȡ�ļ����浽tmpchar
  int count_charsgot = 0;  //��¼�Ѷ�ȡ��0~9���ַ���
  number_of_blanks = 0;  //��¼Ϊ'0'����Ŀ����ʼ��
  solvable = false;
  islegal = false;
  while (true) {
    if (count_charsgot == 81) {  //�����ȡ����81��0~9����������ȡ��ϣ���������0����������
      islegal = true;
      count++;
      return 0;
    }
    tmpchar = fgetc(finput);
    if (feof(finput)) {  //��ȡ���ļ�������EOF�����������������û����81����˵������
      islegal = false;
      return -1;
    }
    //���Ϊ0~9����81�����ָ�ֵ��puzzle[10][10]
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
//��������GetNextPuzzle();��SolveCurrentPuzzle();
//���ļ��е����������⣬�������sudoku_answers�ļ�
//
int SudokuPuzzle::SolveAll() {
  if (finput == NULL || foutput == NULL)  //������ļ�ʧ�ܣ����޷�����
    return -2;
  int solved_count = 0;
  while (true) {
    if (GetNextPuzzle() != 0)
      break;
    if (SolveCurrentPuzzle() != 0) {
      continue;   //�޽�����
    }
    solved_count++;  //�н⣬�ѽ����Ŀ��1
  }
  return solved_count;
}

//
//����dfs_solve()���⵱ǰpuzzle�д�ŵ�����
//
int SudokuPuzzle::SolveCurrentPuzzle() {
  if (finput == NULL || foutput == NULL)  //������ļ�ʧ�ܣ����޷�����
    return -2;
  if (!islegal) {
    return -1;
  } else {
    //�ڽ�����ǰ����Ҫ���жϣ��Ѿ���������������û�б����ͳ�ͻ�ĵط�
    //����еĻ����ǲ��ý��ˣ�ֱ������޽⼴��
    for (int row = 1; row <= 9; row++) {
      for (int column = 1; column <= 9; column++) {
        if (puzzle[row][column] == 0)
          continue;
        for (int i = 1; i <= 9; i++) {  //�ж��Ƿ���л����ظ�
          if ((i != row && puzzle[i][column] == puzzle[row][column])
            || (i != column && puzzle[row][i] == puzzle[row][column])) {  //�ظ���
            solvable = false;
            return -1;
          }
        }
        for (int k1 = 0; k1 < 3; k1++)
          for (int k2 = 0; k2 < 3; k2++) {  //�ж��Ƿ��9�����е��ظ�
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
    //��������һ���н��ˡ���
    dfs_solve(1);
    if (solvable) {  //ֱ�ӽ�puzzle�е�0�滻Ϊsolution�����еĽ⣬Ȼ��������ļ����ɣ���ʵ�������������������һ����
      char outputstring[1005] = { '\0' };  //������
      if (count >= 2)
        strcat_s(outputstring, sizeof(outputstring), "\n\n\0");  //�����ǵ�һ���������������
      int solution_count = 0;
      for (int row = 1; row <= 9; row++)
        for (int column = 1; column <= 9; column++) {
          //ǰ8��
          if (column <= 8) {  
            char tmpchar[3];
            if (puzzle[row][column] != 0) {  //��Ϊ0��ֱ�����
              tmpchar[0] = puzzle[row][column] + 48;
            }
            else {  //Ϊ0���滻��solution�����еĽ�
              tmpchar[0] = solution[solution_count] + 48;
              solution_count++;
            }
            tmpchar[1] = ' ';
            tmpchar[2] = '\0';
            strcat_s(outputstring, sizeof(outputstring), tmpchar);  //���뵽������
            //��9�У�ǰ8��
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
            //���½�
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
      //�ӻ�����������ļ�
      fwrite(outputstring, sizeof(char) * (strlen(outputstring)), 1, foutput);
      return 0;
    } else {
      return -1;
    }
  }
}

//
//���ڸ���puzzle[10][10]��һ���������ѽ����solution[90]
//�õ��ǻ��ݷ���ö��
//TODO: �Ӽ�֦����������ʽ�����������ٶ�
//
void SudokuPuzzle::dfs_solve(int depth) {
  if (solvable)
    return;
  if (depth > number_of_blanks) {  //��ֹ�����������ȴ����˿հ׵ĸ�����Ϊ���н⣬��solvableΪtrue
    solvable = true;
    return;
  } else {
    for (int i = 1; i <= 9; i++) {  //����1~9�Ľڵ�
      for (int j = 1; j <= 9; j++) {  //������л����ظ�
        if ((j != position_of_blanks[depth - 1][0]) && (puzzle[j][position_of_blanks[depth - 1][1]] == i)
          || (j != position_of_blanks[depth - 1][1]) && (puzzle[position_of_blanks[depth - 1][0]][j] == i)) {
          goto continue_next_branch;  //do nothing and stop searching this branch
        }
      }
      for (int k1 = 0; k1 < 3; k1++)
        for (int k2 = 0; k2 < 3; k2++) {  //�����9�����е��ظ�
          int baserow = (position_of_blanks[depth - 1][0] - 1) / 3 * 3 + 1;
          int basecolumn = (position_of_blanks[depth - 1][1] - 1) / 3 * 3 + 1;
          if (puzzle[baserow + k1][basecolumn + k2] == i && baserow + k1 != position_of_blanks[depth - 1][0] 
            && basecolumn + k2 != position_of_blanks[depth - 1][1])
            goto continue_next_branch;  //do nothing and stop searching this branch
        }
      solution[depth - 1] = i;  //��¼��ǰ�ڵ��
      puzzle[position_of_blanks[depth - 1][0]][position_of_blanks[depth - 1][1]] = i;
      dfs_solve(depth + 1);   //�ݹ����
      //solution[depth - 1] = 0;
      puzzle[position_of_blanks[depth - 1][0]][position_of_blanks[depth - 1][1]] = 0;
      if (solvable)  // !! ֮ǰ�����˰��졣��ԭ������û����������������һ�����˻�����ѭ���ء���
        break;
      continue_next_branch:  ;  //do nothing and stop searching this branch
    }
  }
}
