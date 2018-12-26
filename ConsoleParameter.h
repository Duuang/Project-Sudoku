#pragma once
#include <string>

using namespace std;

//
//用来获取控制台参数，并处理，判断错误，得到两个参数
//之后可以用于生成数独或求解数独时的参数
//
class ConsoleParameter {
public:
  // 根据argc和argv，初始化所有成员变量
  void Init(int argc, char *argv[]);
  // 获取-c或者-s指令，失败返回'\0'
  char GetCommand();
  // 获取-c后面的参数，失败返回-1
  int GetOperationcode_c();
  // 获取-s后面的参数，失败返回"\0"
  string GetOperationcode_s();
private:
  // 从控制台获取-c/-s，成功返回0，失败-1
  int ExtractCommand();
  // 根据command为'c'还是's'，获取后面的参数，成功返回0，失败-1
  int ExtractOperationCode();
  // 向控制台显示错误信息
  void OutputError(string errorstring);

  // argc，控制台参数个数
  int argc;
  // argv，多个控制台参数数组的首地址
  char **argv;
  //存放-c或者-s，或者空
  char command;
  //存放-c后面的参数
  int operationcode_c;
  //存放-s后面的参数
  string operationcode_s;
  //表示参数是否合法
  bool islegal;
};
