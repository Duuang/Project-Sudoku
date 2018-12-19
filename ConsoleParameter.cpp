#include "ConsoleParameter.h"
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

//
//init data members, and alter them according to argc and argv
//parameters:
//int argc: argc from main()
//char ** argv: argv from main()
//
void ConsoleParameter::Init(int argc, char *argv[]) {
  //init data members
  islegal = true;
  this->argc = argc;
  this->argv = argv;
  command = '\0';
  operationcode_c = -1;
  string emptystring = "\0";
  operationcode_s = emptystring;
  if (argc != 3) {  // if argc not correct, return
    islegal = -1;
    return;
  }
  if (ExtractCommand() != 0) {  //ExtractCommand()
    islegal = false;
    return;
  }
  if (ExtractOperationCode() != 0)  //ExtractOperationCode()
    islegal = false;
}

//
// get the -c / -s command from data member
//
char ConsoleParameter::GetCommand() {
  if (islegal)
    return command;
  return '\0';
}
//
// get Operationcode_c after command c from data member
//
int ConsoleParameter::GetOperationcode_c() {
  if (islegal)
    return operationcode_c;
  return -1;
}
//
// get Operationcode_s after command s from data member
//
string ConsoleParameter::GetOperationcode_s() {
  if (islegal)
    return operationcode_s;
  string emptystring = "\0";
  return emptystring;
}

//
//get -c/-s from console (argc and argv)
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
// get number after command c/s from console(argc and argv), according to char command
//
int ConsoleParameter::ExtractOperationCode() {
  if (argc != 3) {  // acgc != 3, error
    OutputError("wrong parameter amount\n");
    return -1;
  }
  // -c 1-1000000
  if (command == 'c') {
    if (strlen(*(argv + 2)) > 8) {  // strlen limit = 8
      OutputError("1-1000000\n");
      return -1;

    } else {
      for (int i = 0; i < (int)strlen(*(argv + 2)); i++) {  // check if all characters in '0'-'9'
        if (*(*(argv + 2) + i) < '0' || *(*(argv + 2) + i) > '9') {
          OutputError("1-1000000\n");
          return -1;
        }
      }
      sscanf_s(*(argv + 2), "%d", &operationcode_c);
      if (operationcode_c >= 1 && operationcode_c <= 1000000) {
        return 0;
      } else {
        OutputError("1-1000000\n");
        return -1;
      }
    }
  }
  // -s, string filepath
  if (command == 's') {
    char s_tmp[1005];
    sscanf_s(*(argv + 2), "%s", s_tmp, 1005 * sizeof(char));
    operationcode_s = s_tmp;
    return 0;
  }
  return -1;
}

//
// output error string (don't use cout because of unit test)
//
void ConsoleParameter::OutputError(string errorstring) {
  //cout << errorstring << endl;
}