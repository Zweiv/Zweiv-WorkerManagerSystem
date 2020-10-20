#include "workerManager.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME,ios::in);

	//文件不存在
	if (!ifs.is_open())
	{
		//cout << "文件不存在" << endl;

		//初始化
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;

		//关闭文件流
		ifs.close();

		return;
	}
	
	//文件存在，但没有数据
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空" << endl;
		
		//初始化
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;

		//关闭文件流
		ifs.close();

		return;
	}

	//文件存在，而且有数据
	this->m_EmpNum = this->get_EmpNum();
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	this->init_Emp();
	this->m_FileIsEmpty = false;

	////测试
	//cout << "员工个数为：" << this->m_EmpNum << endl;
	//for (int i = 0; i < this->m_EmpNum; i++)
	//{
	//	cout << "员工编号：" << this->m_EmpArray[i]->m_id
	//		<< "员工姓名：" << this->m_EmpArray[i]->m_name
	//		<< "部门编号：" << this->m_EmpArray[i]->m_DeptId << endl;
	//}
}

void WorkerManager::Show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统!  **********" << endl;
	cout << "*************  0.退出管理系统  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职员工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空文档数据  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void WorkerManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::add_Emp()
{
	int addNum = 0;

	cout << "请输入增加员工数量：" << endl;
	cin >> addNum;

	if (addNum > 0)
	{
		int newSize = this->m_EmpNum + addNum;
		Worker** newSpace = new Worker * [newSize];

		//复制原数据到新空间中
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = m_EmpArray[i];
			}
		}

		//输入新数据
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;

			cout << "请输入第" << i + 1 << "个新员工编号：" << endl;
			cin >> id;

			cout << "请输入第" << i + 1 << "个新员工姓名：" << endl;
			cin >> name;

			cout << "请选择该员工岗位：" << endl;
			cout << "1、普通员工" << endl;
			cout << "2、经理" << endl;
			cout << "3、总裁" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, dSelect);
				break;
			case 2:
				worker = new Manager(id, name, dSelect);
				break;
			case 3:
				worker = new Boss(id, name, dSelect);
				break;
			default:
				break;
			}

			newSpace[this->m_EmpNum + i] = worker;
		}

		//释放原有空间
		delete[] this->m_EmpArray;

		//更改新空间的指向
		this->m_EmpArray = newSpace;

		//更改新的个数
		this->m_EmpNum = newSize;

		this->m_FileIsEmpty = false;

		//保存至文件中
		this->save();

		//提示信息
		cout << "成功添加" << addNum << "名新员工" << endl;

	}
	else
	{
		cout << "输入错误" << endl;
	}

	system("pause");
	system("cls");
}

void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_id << " "
			<< this->m_EmpArray[i]->m_name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}

	ofs.close();
}

int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;
	int num = 0;

	//while(ifs >> id && ifs >> name && ifs >> dId)
	while(ifs >> id >> name >> dId)
	{
		num++;
	}

	ifs.close();

	return num;
}

void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;

	//while(ifs >> id && ifs >> name && ifs >> dId)
	while (ifs >> id >> name >> dId)
	{
		Worker* worker = NULL;
		switch (dId)
		{
		case 1:
			worker = new Employee(id, name, dId);
			break;
		case 2:
			worker = new Manager(id, name, dId);
			break;
		case 3:
			worker = new Boss(id, name, dId);
			break;
		default:
			break;
		}

		this->m_EmpArray[index++] = worker;
	}

	ifs.close();
}

void WorkerManager::show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或文件中没有数据" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showInfo();
		}
	}

	system("pause");
	system("cls");
}

void WorkerManager::del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或文件中没有数据" << endl;
	}
	else
	{
		cout << "请输入想要删除的员工编号：" << endl;

		int id = 0;
		cin >> id;

		int index = this->findById(id);

		if (-1 != index)
		{
			this->m_EmpArray[index] = this->m_EmpArray[this->m_EmpNum - 1];
			this->m_EmpNum--;
			this->save();
			cout << "删除成功" << endl;
		}
		else
		{
			cout << "删除失败，未找到该编号员工" << endl;
		}
	}
	system("pause");
	system("cls");
}

int WorkerManager::findById(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; ++i)
	{
		if (this->m_EmpArray[i]->m_id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}

int WorkerManager::findByName(string name)
{
	int count = 0;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_name == name)
		{
			count++;
		}
	}
	return count;
}

void WorkerManager::find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或文件中没有数据" << endl;
	}
	else
	{
		cout << "请输入想要查找的方式：" << endl;
		cout << "1、按员工编号查找" << endl;
		cout << "2、按姓名查找" << endl;

		int select = 0;
		cin >> select;

		if (1 == select)
		{
			cout << "请输入想要查找的员工编号：" << endl;
			int id;
			cin >> id;

			int index = this->findById(id);
			if (-1 != index)
			{
				cout << "查找成功，该职工信息如下：" << endl;
				this->m_EmpArray[index]->showInfo();
			}
			else
			{
				cout << "查找失败，未找到编号为" << id << "的员工" << endl;
			}
		}
		else if(2==select)
		{
			cout << "请输入想要查找的员工姓名：" << endl;
			string name;
			cin >> name;

			int count = this->findByName(name);
			if (0 != count)
			{
				cout << "查找成功，共找到" << count << "名员工，信息如下：" << endl;
				for (int i = 0; i < this->m_EmpNum; ++i)
				{
					if (this->m_EmpArray[i]->m_name == name)
					{
						this->m_EmpArray[i]->showInfo();
					}
				}
			}
			else
			{
				cout << "查找失败，未找到姓名为" << name << "的员工" << endl;
			}
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::alt_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或文件中没有数据" << endl;
	}
	else
	{
		cout << "请输入想要修改的员工编号：" << endl;

		int id = 0;
		cin >> id;

		int index = this->findById(id);

		if (-1 != index)
		{
			delete this->m_EmpArray[index];


			int newId;
			string newName;
			int dId;

			cout << "查找到" << id << "号员工，请输入新编号：" << endl;
			cin >> newId;

			cout << "请输入新姓名：" << endl;
			cin >> newName;

			cout << "请选择该员工岗位：" << endl;
			cout << "1、普通员工" << endl;
			cout << "2、经理" << endl;
			cout << "3、总裁" << endl;
			cin >> dId;

			Worker* worker = NULL;
			switch (dId)
			{
			case 1:
				worker = new Employee(newId, newName, dId);
				break;
			case 2:
				worker = new Manager(newId, newName, dId);
				break;
			case 3:
				worker = new Boss(newId, newName, dId);
				break;
			default:
				break;
			}

			this->m_EmpArray[index] = worker;
			this->save();
			cout << "修改成功" << endl;
		}
		else
		{
			cout << "修改失败，未找到该编号员工" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或文件中没有数据" << endl;
	}
	else
	{
		cout << "请选择排序方式：" << endl;
		cout << "1、按员工编号升序" << endl;
		cout << "2、按员工编号降序" << endl;

		int select = 0;
		cin >> select;

		for (int i = 0; i < this->m_EmpNum; ++i)
		{
			int minOrMax = i;
			for (int j = i + 1; j < this->m_EmpNum; ++j)
			{
				if (1 == select)
				{
					if (this->m_EmpArray[minOrMax]->m_id > this->m_EmpArray[j]->m_id)
					{
						minOrMax = j;
					}
				}
				else if (2 == select)
				{
					if (this->m_EmpArray[minOrMax]->m_id < this->m_EmpArray[j]->m_id)
					{
						minOrMax = j;
					}
				}
			}
			if (minOrMax != i)
			{
				Worker* temp = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = this->m_EmpArray[i];
				this->m_EmpArray[i] = temp;
			}
		}
		cout << "排序成功，排序结果为：" << endl;
		this->save();
		this->show_Emp();
	}
}

void WorkerManager::clean_File()
{
	cout << "确定清空？" << endl;
	cout << "1、确定" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;

	if (1 == select)
	{
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		if (NULL != this->m_EmpArray)
		{
			for (int i = 0; i < this->m_EmpNum; ++i)
			{
				if (NULL != this->m_EmpArray[i])
				{
					delete this->m_EmpArray[i];
					m_EmpArray[i] = NULL;
				}
			}
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功！" << endl;
	}

	system("pause");
	system("cls");
}

WorkerManager::~WorkerManager()
{
	if (NULL != this->m_EmpArray)
	{
		for (int i = 0; i < this->m_EmpNum; ++i)
		{
			if (NULL != this->m_EmpArray[i])
			{
				delete this->m_EmpArray[i];
				m_EmpArray[i] = NULL;
			}
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
	}
}