#pragma once
#include <string>
using namespace std;

class ConsoleParameter {
public:
  ConsoleParameter();
  // get the -c / -s command
  char GetCommand();
  // get Operationcode_c after command c
  int GetOperationcode_c();
  // get Operationcode_s after command s
  string GetOperationcode_s();

private:  
  // extract the -c / -s command
  int ExtractCommand();
  // extract number after command c/s, according to char command
  int ExtractOperationCode();
  // output error string to console
  void OutputError(string errorstring);

  char command;
  int operationcode_c;
  string operationcode_s;
  bool islegal;
};