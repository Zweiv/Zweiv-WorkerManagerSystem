#include <iostream>
using namespace std;
#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

void test();

int main()
{
	//test();

	WorkerManager wm;
	int choice = -1;
	while (true)
	{
		wm.Show_Menu();
		cout << "ÇëÊäÈëÄúµÄÑ¡Ôñ£º" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:
			wm.exitSystem();
			break;
		case 1:
			wm.add_Emp();
			break;
		case 2:
			wm.show_Emp();
			break;
		case 3:
			wm.del_Emp();
			break;
		case 4:
			wm.alt_Emp();
			break;
		case 5:
			wm.find_Emp();
			break;
		case 6:
			wm.sort_Emp();
			break;
		case 7:
			wm.clean_File();
			break;
		default:
			system("cls");
			break;
		}
	}
	

	system("pause");

	return 0;
}

void test()
{
	Worker* w = NULL;

	w = new Employee(1, "111", 1);
	w->showInfo();
	delete w;

	w = new Manager(2, "222", 2);
	w->showInfo();
	delete w;

	w = new Boss(3, "333", 3);
	w->showInfo();
	delete w;
}