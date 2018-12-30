#include "ConsoleParameter.h"
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

//
// 根据argc和argv，初始化所有成员变量（初始化为空）
//parameters:
//int argc: argc from main()
//char ** argv: argv from main()
//
void ConsoleParameter::Init(int argc, char *argv[]) {
  //初始化成员变量
  islegal = true;
  this->argc = argc;
  this->argv = argv;
  command = '\0';
  operationcode_c = -1;
  string emptystring = "\0";
  operationcode_s = emptystring;
  if (argc != 3) {  // 如果argc不对，islegal参数直接设置成非法，返回-1
    islegal = false;
    return;
  }
  if (ExtractCommand() != 0) {  //调用ExtractCommand()获取-c/-s
    islegal = false;
    return;
  }
  if (ExtractOperationCode() != 0)  //调用ExtractOperationCode()
    islegal = false;
}

//
// 获取-c或者-s指令，失败返回'\0'
//
char ConsoleParameter::GetCommand() {
  if (islegal)
    return command;
  return '\0';
}
//
// 获取-c后面的参数，失败返回-1
//
int ConsoleParameter::GetOperationcode_c() {
  if (islegal)
    return operationcode_c;
  return -1;
}
//
// 获取-s后面的参数，失败返回空string对象
//
string ConsoleParameter::GetOperationcode_s() {
  if (islegal)
    return operationcode_s;
  string emptystring = "\0";
  return emptystring;
}

//
//从控制台获取-c/-s，成功0，失败-1
//
int ConsoleParameter::ExtractCommand() {
  if ( *(*(argv + 1)) == '-' && *(*(argv + 1) + 2) == '\0' &&
    (*(*(argv + 1) + 1) == 'c' || *(*(argv + 1) + 1) == 's'))  {
    command = *(*(argv + 1) + 1);
    return 0;

  } else {
    OutputError("-c or -s required\n");
    return -1;
  }
}

//
// 根据command为'c'还是's'，获取后面的参数，成功返回0，失败-1
//
int ConsoleParameter::ExtractOperationCode() {
  if (argc != 3) {  // acgc != 3, error
    OutputError("wrong parameter amount\n");
    return -1;
  }
  // -c 1-1000000
  if (command == 'c') {
    if (strlen(*(argv + 2)) > 8) {  // 字符串长度限制为8，超出的话非法
      OutputError("1-1000000\n");
      return -1;

    } else {
      for (int i = 0; i < (int)strlen(*(argv + 2)); i++) {  // 检查是否所有字符都是0~9
        if (*(*(argv + 2) + i) < '0' || *(*(argv + 2) + i) > '9') {
          OutputError("1-1000000\n");
          return -1;
        }
      }
      sscanf_s(*(argv + 2), "%d", &operationcode_c);
      if (operationcode_c >= 1 && operationcode_c <= 1000000) {  //检查是否在1——1000000范围内
        return 0;
      } else {
        OutputError("1-1000000\n");
        return -1;
      }
    }
  }
  // -s, string filepath，存文件路径到string
  if (command == 's') {
    char s_tmp[1005] = "";
    sscanf_s(*(argv + 2), "%s", s_tmp, (unsigned int)(1005 * sizeof(char)));
    operationcode_s = s_tmp;
    return 0;
  }
  return -1;
}

//
// 输出错误到控制台 (don't use cout because of unit test)
//
void ConsoleParameter::OutputError(string errorstring) {
  //cout << errorstring << endl;
}
