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
  void Init(int argc, char *argv[]);
  // ��ȡ-c����-sָ�ʧ�ܷ���'\0'
  char GetCommand();
  // ��ȡ-c����Ĳ�����ʧ�ܷ���-1
  int GetOperationcode_c();
  // ��ȡ-s����Ĳ�����ʧ�ܷ���"\0"
  string GetOperationcode_s();
private:
  // �ӿ���̨��ȡ-c/-s���ɹ�����0��ʧ��-1
  int ExtractCommand();
  // ����commandΪ'c'����'s'����ȡ����Ĳ������ɹ�����0��ʧ��-1
  int ExtractOperationCode();
  // �����̨��ʾ������Ϣ
  void OutputError(string errorstring);

  // argc������̨��������
  int argc;
  // argv���������̨����������׵�ַ
  char **argv;
  //���-c����-s�����߿�
  char command;
  //���-c����Ĳ���
  int operationcode_c;
  //���-s����Ĳ���
  string operationcode_s;
  //��ʾ�����Ƿ�Ϸ�
  bool islegal;
};
