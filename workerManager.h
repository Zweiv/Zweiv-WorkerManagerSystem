#pragma once
#include <iostream>
#include<fstream>
using namespace std;
#include "worker.h"
#define FILENAME "empFile.txt"

class WorkerManager
{
public:
	WorkerManager();
	~WorkerManager();

	//չʾ�˵�
	void Show_Menu();
	//�˳�ϵͳ
	void exitSystem();
	//���Ա��
	void add_Emp();
	//�����ļ�
	void save();
	//��ȡ�ļ���Ա������
	int get_EmpNum();
	//��ʼ��Ա����Ϣ
	void init_Emp();
	//��ʾԱ����Ϣ
	void show_Emp();
	//ɾ��Ա����Ϣ
	void del_Emp();
	//�ñ�Ų���Ա���Ƿ���ڣ����ڷ����±꣬���򷵻�-1
	int findById(int id);
	//����������Ա���Ƿ���ڣ�����ֵΪͬ��Ա��������
	int findByName(string name);
	//����Ա����Ϣ
	void find_Emp();
	//�޸�Ա����Ϣ
	void alt_Emp();
	//���������Ա����Ϣ
	void sort_Emp();
	//����ļ�����
	void clean_File();

private:
	int m_EmpNum;
	Worker** m_EmpArray;
	bool m_FileIsEmpty;
};

