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

	//展示菜单
	void Show_Menu();
	//退出系统
	void exitSystem();
	//添加员工
	void add_Emp();
	//保存文件
	void save();
	//获取文件中员工数量
	int get_EmpNum();
	//初始化员工信息
	void init_Emp();
	//显示员工信息
	void show_Emp();
	//删除员工信息
	void del_Emp();
	//用编号查找员工是否存在，存在返回下标，否则返回-1
	int findById(int id);
	//用姓名查找员工是否存在，返回值为同名员工的数量
	int findByName(string name);
	//查找员工信息
	void find_Emp();
	//修改员工信息
	void alt_Emp();
	//按编号排序员工信息
	void sort_Emp();
	//清空文件数据
	void clean_File();

private:
	int m_EmpNum;
	Worker** m_EmpArray;
	bool m_FileIsEmpty;
};

