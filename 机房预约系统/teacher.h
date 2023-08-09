#pragma once
#include <iostream>
using namespace std;
#include "Identity.h"
#include "orderFile.h"
#include <vector>
class Teacher : public Identity {
public:
	//默认构造
	Teacher();

	//有参构造(职工号，姓名，密码)
	Teacher(int empId, string name, string pwd);

	//操作界面
	virtual void operMenu();//操作菜单  纯虚函数

	//查看所有预约
	void showAllOrder();

	//审核
	void validOrder();

	//职工号
	int m_EmpId;

};