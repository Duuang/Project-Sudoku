#include "ConsoleParameter.h"
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

//
// ����argc��argv����ʼ�����г�Ա��������ʼ��Ϊ�գ�
//parameters:
//int argc: argc from main()
//char ** argv: argv from main()
//
void ConsoleParameter::Init(int argc, char *argv[]) {
  //��ʼ����Ա����
  islegal = true;
  this->argc = argc;
  this->argv = argv;
  command = '\0';
  operationcode_c = -1;
  string emptystring = "\0";
  operationcode_s = emptystring;
  if (argc != 3) {  // ���argc���ԣ�islegal����ֱ�����óɷǷ�������-1
    islegal = false;
    return;
  }
  if (ExtractCommand() != 0) {  //����ExtractCommand()��ȡ-c/-s
    islegal = false;
    return;
  }
  if (ExtractOperationCode() != 0)  //����ExtractOperationCode()
    islegal = false;
}

//
// ��ȡ-c����-sָ�ʧ�ܷ���'\0'
//
char ConsoleParameter::GetCommand() {
  if (islegal)
    return command;
  return '\0';
}
//
// ��ȡ-c����Ĳ�����ʧ�ܷ���-1
//
int ConsoleParameter::GetOperationcode_c() {
  if (islegal)
    return operationcode_c;
  return -1;
}
//
// ��ȡ-s����Ĳ�����ʧ�ܷ��ؿ�string����
//
string ConsoleParameter::GetOperationcode_s() {
  if (islegal)
    return operationcode_s;
  string emptystring = "\0";
  return emptystring;
}

//
//�ӿ���̨��ȡ-c/-s���ɹ�0��ʧ��-1
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
// ����commandΪ'c'����'s'����ȡ����Ĳ������ɹ�����0��ʧ��-1
//
int ConsoleParameter::ExtractOperationCode() {
  if (argc != 3) {  // acgc != 3, error
    OutputError("wrong parameter amount\n");
    return -1;
  }
  // -c 1-1000000
  if (command == 'c') {
    if (strlen(*(argv + 2)) > 8) {  // �ַ�����������Ϊ8�������Ļ��Ƿ�
      OutputError("1-1000000\n");
      return -1;

    } else {
      for (int i = 0; i < (int)strlen(*(argv + 2)); i++) {  // ����Ƿ������ַ�����0~9
        if (*(*(argv + 2) + i) < '0' || *(*(argv + 2) + i) > '9') {
          OutputError("1-1000000\n");
          return -1;
        }
      }
      sscanf_s(*(argv + 2), "%d", &operationcode_c);
      if (operationcode_c >= 1 && operationcode_c <= 1000000) {  //����Ƿ���1����1000000��Χ��
        return 0;
      } else {
        OutputError("1-1000000\n");
        return -1;
      }
    }
  }
  // -s, string filepath�����ļ�·����string
  if (command == 's') {
    char s_tmp[1005] = "";
    sscanf_s(*(argv + 2), "%s", s_tmp, (unsigned int)(1005 * sizeof(char)));
    operationcode_s = s_tmp;
    return 0;
  }
  return -1;
}

//
// ������󵽿���̨ (don't use cout because of unit test)
//
void ConsoleParameter::OutputError(string errorstring) {
  //cout << errorstring << endl;
}
