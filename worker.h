#pragma once
#include <iostream>
#include <string>
using namespace std;

//ְ���������
class Worker
{
public:
	//��ʾԱ����Ϣ
	virtual void showInfo() = 0;
	//��ȡ��λ����
	virtual string getDeptName() = 0;
	//Ա�����
	int m_id;
	//Ա������
	string m_name;
	//��λ���
	int m_DeptId;

private:
};
