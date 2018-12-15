#pragma once
#include <string>

class ConsoleParameter {
public:
  //ConsoleParameter(const int argc, const char *(*argv));

  //
  //int GetString();
  // get the -c / -s command
  int GetCommand();
  // get the operation code
  int GetOperationCode();
private:
  //std::string input_string;
  
  char command;
  int operation_code;
  void OutputError();
};