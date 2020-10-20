#include "manager.h"

Manager::Manager(int id, string name, int dId)
{
	this->m_id = id;
	this->m_name = name;
	this->m_DeptId = dId;
}

void Manager::showInfo()
{
	cout << "职工编号：" << this->m_id
		<< "\t职工姓名：" << this->m_name
		<< "\t岗位：" << this->getDeptName()
		<< "\t岗位职责：完成总裁交给的任务，并下发给员工" << endl;
}

string Manager::getDeptName()
{
	return string("经理");
}
