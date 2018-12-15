#include <iostream>
#include "ConsoleParameter.h"
using namespace std;

int main(int argc, char *argv[]) {
  ConsoleParameter parameter;

  if (parameter.GetCommand() == 0 && parameter.GetOperationCode == 0) {
    printf("aaa\n");

  }
  system("pause");
  return 0;
}