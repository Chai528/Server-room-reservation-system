#pragma once
#include <iostream>
using namespace std;
#include "Identity.h"
#include "orderFile.h"
#include <vector>
class Teacher : public Identity {
public:
	//Ĭ�Ϲ���
	Teacher();

	//�вι���(ְ���ţ�����������)
	Teacher(int empId, string name, string pwd);

	//��������
	virtual void operMenu();//�����˵�  ���麯��

	//�鿴����ԤԼ
	void showAllOrder();

	//���
	void validOrder();

	//ְ����
	int m_EmpId;

};