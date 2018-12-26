#pragma once
#include <string>

using namespace std;

//
//������ȡ����̨�������������жϴ��󣬵õ���������
//֮��������������������������ʱ�Ĳ���
//
class ConsoleParameter {
public:
  // ����argc��argv����ʼ�����г�Ա����
  ConsoleParameter(int argc, char *argv[]);
  // ��ȡ-c����-sָ�ʧ�ܷ���'\0'
  char GetCommand();
  // ��ȡ-c��-s����Ĳ�����ʧ�ܷ���"\0"
  string GetOperationcode();
private:
  // �����̨��ʾ������Ϣ
  void OutputError(string errorstring);
  // argc������̨��������
  int argc;
  // argv���������̨����������׵�ַ
  char **argv;
  //���-c����-s�����߿�
  char command;
  //���-c����-s����Ĳ���
  string operationcode;
};
