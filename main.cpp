#include <iostream>
#include "ConsoleParameter.h"
using namespace std;

int main(int argc, char *argv[]) {
  ConsoleParameter parameter;
  parameter.GetCommand();
  
  system("pause");
  return 0;
}