#pragma once
#include <iostream>
using namespace std;
#include "Identity.h"
#include "computerRoom.h"
#include <vector>
#include <fstream>
#include "globalFile.h"
#include "orderFile.h"


class Student :public Identity {
public:
	//默认构造
	Student();

	//有参构造(学号、姓名、密码)
	Student(int id, string name, string pwd);

	//操作菜单界面   子类重写父类中的虚函数
	virtual void operMenu();
	 
	//申请预约
	void applyOrder();

	//查看我的预约
	void showMyOrder();

	//查看所有预约
	void showAllOrder();

	//取消预约
	void cancelOrder();

	int m_Id;//学生学号

	//机房容器
	vector<ComputerRoom> vCom;
};