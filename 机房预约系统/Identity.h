#pragma once
#include <iostream>
using namespace std;

class Identity {
public:
	//多态技术
	virtual void operMenu() = 0;//操作菜单  纯虚函数

	string m_Name;//用户名
	string m_Pwd;//密码
};