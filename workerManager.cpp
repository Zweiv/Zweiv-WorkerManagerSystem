#include "workerManager.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME,ios::in);

	//�ļ�������
	if (!ifs.is_open())
	{
		//cout << "�ļ�������" << endl;

		//��ʼ��
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;

		//�ر��ļ���
		ifs.close();

		return;
	}
	
	//�ļ����ڣ���û������
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "�ļ�Ϊ��" << endl;
		
		//��ʼ��
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;

		//�ر��ļ���
		ifs.close();

		return;
	}

	//�ļ����ڣ�����������
	this->m_EmpNum = this->get_EmpNum();
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	this->init_Emp();
	this->m_FileIsEmpty = false;

	////����
	//cout << "Ա������Ϊ��" << this->m_EmpNum << endl;
	//for (int i = 0; i < this->m_EmpNum; i++)
	//{
	//	cout << "Ա����ţ�" << this->m_EmpArray[i]->m_id
	//		<< "Ա��������" << this->m_EmpArray[i]->m_name
	//		<< "���ű�ţ�" << this->m_EmpArray[i]->m_DeptId << endl;
	//}
}

void WorkerManager::Show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*********  ��ӭʹ��ְ������ϵͳ!  **********" << endl;
	cout << "*************  0.�˳�����ϵͳ  *************" << endl;
	cout << "*************  1.����ְ����Ϣ  *************" << endl;
	cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
	cout << "*************  3.ɾ����ְԱ��  *************" << endl;
	cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
	cout << "*************  5.����ְ����Ϣ  *************" << endl;
	cout << "*************  6.���ձ������  *************" << endl;
	cout << "*************  7.����ĵ�����  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void WorkerManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::add_Emp()
{
	int addNum = 0;

	cout << "����������Ա��������" << endl;
	cin >> addNum;

	if (addNum > 0)
	{
		int newSize = this->m_EmpNum + addNum;
		Worker** newSpace = new Worker * [newSize];

		//����ԭ���ݵ��¿ռ���
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = m_EmpArray[i];
			}
		}

		//����������
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;

			cout << "�������" << i + 1 << "����Ա����ţ�" << endl;
			cin >> id;

			cout << "�������" << i + 1 << "����Ա��������" << endl;
			cin >> name;

			cout << "��ѡ���Ա����λ��" << endl;
			cout << "1����ͨԱ��" << endl;
			cout << "2������" << endl;
			cout << "3���ܲ�" << endl;
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

		//�ͷ�ԭ�пռ�
		delete[] this->m_EmpArray;

		//�����¿ռ��ָ��
		this->m_EmpArray = newSpace;

		//�����µĸ���
		this->m_EmpNum = newSize;

		this->m_FileIsEmpty = false;

		//�������ļ���
		this->save();

		//��ʾ��Ϣ
		cout << "�ɹ����" << addNum << "����Ա��" << endl;

	}
	else
	{
		cout << "�������" << endl;
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
		cout << "�ļ������ڻ��ļ���û������" << endl;
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
		cout << "�ļ������ڻ��ļ���û������" << endl;
	}
	else
	{
		cout << "��������Ҫɾ����Ա����ţ�" << endl;

		int id = 0;
		cin >> id;

		int index = this->findById(id);

		if (-1 != index)
		{
			this->m_EmpArray[index] = this->m_EmpArray[this->m_EmpNum - 1];
			this->m_EmpNum--;
			this->save();
			cout << "ɾ���ɹ�" << endl;
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ��ñ��Ա��" << endl;
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
		cout << "�ļ������ڻ��ļ���û������" << endl;
	}
	else
	{
		cout << "��������Ҫ���ҵķ�ʽ��" << endl;
		cout << "1����Ա����Ų���" << endl;
		cout << "2������������" << endl;

		int select = 0;
		cin >> select;

		if (1 == select)
		{
			cout << "��������Ҫ���ҵ�Ա����ţ�" << endl;
			int id;
			cin >> id;

			int index = this->findById(id);
			if (-1 != index)
			{
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->m_EmpArray[index]->showInfo();
			}
			else
			{
				cout << "����ʧ�ܣ�δ�ҵ����Ϊ" << id << "��Ա��" << endl;
			}
		}
		else if(2==select)
		{
			cout << "��������Ҫ���ҵ�Ա��������" << endl;
			string name;
			cin >> name;

			int count = this->findByName(name);
			if (0 != count)
			{
				cout << "���ҳɹ������ҵ�" << count << "��Ա������Ϣ���£�" << endl;
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
				cout << "����ʧ�ܣ�δ�ҵ�����Ϊ" << name << "��Ա��" << endl;
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
		cout << "�ļ������ڻ��ļ���û������" << endl;
	}
	else
	{
		cout << "��������Ҫ�޸ĵ�Ա����ţ�" << endl;

		int id = 0;
		cin >> id;

		int index = this->findById(id);

		if (-1 != index)
		{
			delete this->m_EmpArray[index];


			int newId;
			string newName;
			int dId;

			cout << "���ҵ�" << id << "��Ա�����������±�ţ�" << endl;
			cin >> newId;

			cout << "��������������" << endl;
			cin >> newName;

			cout << "��ѡ���Ա����λ��" << endl;
			cout << "1����ͨԱ��" << endl;
			cout << "2������" << endl;
			cout << "3���ܲ�" << endl;
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
			cout << "�޸ĳɹ�" << endl;
		}
		else
		{
			cout << "�޸�ʧ�ܣ�δ�ҵ��ñ��Ա��" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��ļ���û������" << endl;
	}
	else
	{
		cout << "��ѡ������ʽ��" << endl;
		cout << "1����Ա���������" << endl;
		cout << "2����Ա����Ž���" << endl;

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
		cout << "����ɹ���������Ϊ��" << endl;
		this->save();
		this->show_Emp();
	}
}

void WorkerManager::clean_File()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

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
		cout << "��ճɹ���" << endl;
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