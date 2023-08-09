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
	//Ĭ�Ϲ���
	Student();

	//�вι���(ѧ�š�����������)
	Student(int id, string name, string pwd);

	//�����˵�����   ������д�����е��麯��
	virtual void operMenu();
	 
	//����ԤԼ
	void applyOrder();

	//�鿴�ҵ�ԤԼ
	void showMyOrder();

	//�鿴����ԤԼ
	void showAllOrder();

	//ȡ��ԤԼ
	void cancelOrder();

	int m_Id;//ѧ��ѧ��

	//��������
	vector<ComputerRoom> vCom;
};