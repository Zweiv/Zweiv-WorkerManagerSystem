#pragma once
#include <iostream>
#include <string>
using namespace std;

//职工抽象基类
class Worker
{
public:
	//显示员工信息
	virtual void showInfo() = 0;
	//获取岗位名称
	virtual string getDeptName() = 0;
	//员工编号
	int m_id;
	//员工姓名
	string m_name;
	//岗位编号
	int m_DeptId;

private:
};
