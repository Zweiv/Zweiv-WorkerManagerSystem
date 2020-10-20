#pragma once
#pragma once
#include <iostream>
using namespace std;
#include "worker.h"

//‘±π§¿‡
class Boss :public Worker
{
public:
	Boss(int id, string name, int dId);
	virtual void showInfo();
	virtual string getDeptName();

private:
};