#pragma once
#include "Identity.h"
#include <fstream> 
#include "globalFile.h"
#include <vector>
#include "student.h"
#include "teacher.h"
#include <algorithm>
#include "computerRoom.h"

class Manager: public Identity{
public:
	//默认构造
	Manager();

	//有参构造（姓名，密码）
	Manager(string name, string pwd);

	//选择界面
	virtual void operMenu();

	//添加账号
	void addPerson();

	//查看账号
	void showPerson();

	//查看机房信息
	void showComputer();

	//清空文件
	void clearFile();

	//初始化容器（防止录入重复的人员）
	void initVector();

	//学生容器
	vector<Student> vStu;

	//教师容器
	vector<Teacher> vTea;

	//检测重复输入
	bool checkRepeat(int id,int type); //参数1 检测学号/职工号 ；参数2 检测类型

	//机房容器
	vector<ComputerRoom> vCom; 
};

