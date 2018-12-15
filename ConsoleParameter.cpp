#include "ConsoleParameter.h"
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;


//get -c/-s from console
int ConsoleParameter::GetCommand() {
  if (*(*(__argv + 1)) == '-' && *(*(__argv + 1) + 2) == '\0' &&
    (*(*(__argv + 1) + 1) == 'c' || *(*(__argv + 1) + 1) == 's'))  {
    command = *(*(__argv + 1) + 1);
    return 0;

  } else {
    return -1;
  }
}
 // get number after -c from console
int ConsoleParameter::GetOperationCode() {
  if (__argc > 3) {
    return -1;
  } else if (strlen(*(__argv + 2)) > 8) {
    return -1;

  } else {
    sscanf_s(*(__argv + 2), "%d", &operation_code);
    if (operation_code >= 1 && operation_code <= 1000000) {
      return 0;
    } else {
      return -1;
    }
  }
}