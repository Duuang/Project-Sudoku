#include "ConsoleParameter.h"
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;


ConsoleParameter::ConsoleParameter() {
  islegal = true;
  if (ExtractCommand() != 0) {
    islegal = false;
    return;
  }
  if (ExtractOperationCode() != 0)
    islegal = false;
}
// get the -c / -s command
char ConsoleParameter::GetCommand() {
  if (islegal)
    return command;
  return '\0';
}

// get Operationcode_c after command c
int ConsoleParameter::GetOperationcode_c() {
  if (islegal)
    return operationcode_c;
  return -1;
}
// get Operationcode_s after command s
string ConsoleParameter::GetOperationcode_s() {
  if (islegal)
    return operationcode_s;
  string emptystring = "\0";
  return emptystring;
}



//
//get -c/-s from console
//
int ConsoleParameter::ExtractCommand() {
  if ( *(*(__argv + 1)) == '-' && *(*(__argv + 1) + 2) == '\0' &&
    (*(*(__argv + 1) + 1) == 'c' || *(*(__argv + 1) + 1) == 's'))  {
    command = *(*(__argv + 1) + 1);
    return 0;

  } else {
    OutputError("-c or -s required\n");
    return -1;
  }
}
//
// get number after command c/s, according to char command
//
int ConsoleParameter::ExtractOperationCode() {
  if (__argc > 3) {  // acgc > 3, error
    OutputError("too many parameters\n");
    return -1;
  }
  // -c 1-1000000
  if (command == 'c') {
    if (strlen(*(__argv + 2)) > 8) {  // strlen limit = 8
      OutputError("1-1000000\n");
      return -1;

    } else {
      for (int i = 0; i < (int)strlen(*(__argv + 2)); i++) {  // check if all characters in '0'-'9'
        if (*(*(__argv + 2) + i) < '0' || *(*(__argv + 2) + i) > '9') {
          OutputError("1-1000000\n");
          return -1;
        }
      }
      sscanf_s(*(__argv + 2), "%d", &operationcode_c);
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
    sscanf_s(*(__argv + 2), "%s", s_tmp, 1005 * sizeof(char));
    operationcode_s = s_tmp;
    return 0;
  }
  return -1;
}

//
// output error string to console
//
void ConsoleParameter::OutputError(string errorstring) {
  cout << errorstring << endl;
}