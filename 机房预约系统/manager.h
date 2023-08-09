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
	//Ĭ�Ϲ���
	Manager();

	//�вι��죨���������룩
	Manager(string name, string pwd);

	//ѡ�����
	virtual void operMenu();

	//����˺�
	void addPerson();

	//�鿴�˺�
	void showPerson();

	//�鿴������Ϣ
	void showComputer();

	//����ļ�
	void clearFile();

	//��ʼ����������ֹ¼���ظ�����Ա��
	void initVector();

	//ѧ������
	vector<Student> vStu;

	//��ʦ����
	vector<Teacher> vTea;

	//����ظ�����
	bool checkRepeat(int id,int type); //����1 ���ѧ��/ְ���� ������2 �������

	//��������
	vector<ComputerRoom> vCom; 
};

