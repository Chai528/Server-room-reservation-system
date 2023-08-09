#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include "Identity.h"
#include <fstream>
#include "globalFile.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"

void teacherMenu(Identity* &teacher) {
	while (true){
		//��ʦ��������
		teacher->operMenu();
		Teacher* tea = (Teacher*)teacher;

		int select = 0;
		cin >> select;
		if (select == 1){
			//�鿴����ԤԼ
			tea->showAllOrder();
		}
		else if(select == 2){
			//���ԤԼ
			tea->validOrder();
		}
		else{
			//ע����¼
			delete teacher;
			cout << "ע����ʦ��¼�ɹ���" << endl;
			system("pause");
			system("cls");
			return;
		}
	}


}
void studentMenu(Identity* &student) {
	while (true){
		//ѧ�������˵�
		student->operMenu();
		Student* stu = (Student *)student;//ǿת

		int select = 0;
		cin >> select;
		if (select == 1){//����ԤԼ
			stu->applyOrder();
		}
		else if (select == 2){//�鿴�ҵ�ԤԼ
			stu->showMyOrder();
		}
		else if (select == 3){//�鿴����ԤԼ
			stu->showAllOrder();
		}
		else if (select == 4) {//ȡ��ԤԼ
			stu->cancelOrder();
		}
		else{//ע����¼
			delete student;//���ٵ���������
			cout << "ѧ��ע����¼�ɹ���" << endl;
			system("pause");
			system("cls");
			return;
		}

	}
}
void managerMenu(Identity* &manager) {
/* ���������ָ����������������Ҳ������⣬��identity*����һ���࣬�������&������Ӧ�������Ķ������������������õķ�ʽ������identity���ָ��ʵ��
   �Ӳ���&����������ڣ����ӣ����¿��ٿռ䲢������һ��ָ��Ϊmanager��ָ�룬���ָ���ڲ���ŵ������Ƕ�ʵ�����ݵĿ�����������һ���ַ��ţ�
   ����&��������������õı��ʣ���ô���൱�ڸ�ʵ��ָ�����˵ڶ������֣�����manager�����ǿ���ͨ��manager�������ֱ��ȥ����ʵ��
   ���ﻹҪ�ٲ��ϵ�һ��֪ʶ����ǣ��β���n��ָ�룬ʵ��Ҳ��n��ָ��ʱ���β�ָ�벻��ָ��ʵ�Σ����ǽ��ж�ʵ�εĿ������������ָ��ָ��ָ�룬��ô�β�ָ����Ҫ��ʵ��ָ���һ��*/
	while (true){
		//����Ա�˵�
		manager->operMenu();
		int select = 0;
		Manager* man = (Manager*) manager;//��������� ǿת Ϊ������󣬷���ʹ�����������������Ľӿ�
		cin >> select;
		if (select == 1){
			//����˺�
			man->addPerson();
		}
		else if (select == 2) {
			//�鿴�˺�
			man->showPerson();
		}
		else if (select == 3) {
			//�鿴����
			man->showComputer();
		}
		else if (select == 4) {
			//���ԤԼ
			man->clearFile();
		}
		else{
			//ע����¼
			delete manager;    //���ٵ���������
			cout << "ע���ɹ���" << endl;
			system("pause");
			system("cls");
			return;
		}
	}

}
//��¼����
void LoginIn(string fileName,int type) { //type����������ͣ�1--ѧ����2--��ʦ��3--����Ա
	Identity* person = NULL;//����ָ��ָ���������

	//������ʽ��
	ifstream ifs;
	ifs.open(fileName,ios::in);

	//�ж��ļ��Ƿ����
	if ( !ifs.is_open() ){
		cout << "�ļ������ڣ�" << endl;
		ifs.close();
		return;
	}
	//׼�������û���Ϣ
	int id = 0;
	string name;
	string pwd;
	//�ж����
	if (type == 1){//ѧ�����
		cout << "���������ѧ�ţ�" << endl;
		cin >> id;
	}else if (type == 2 ){//��ʦ���
		cout << "���������ְ���ţ�" << endl;
		cin >> id;
	}

	cout << "���������������" << endl;
	cin >> name;
	cout << "������������룺" << endl;
	cin >> pwd;

	if (type == 1){//ѧ�������֤
		int fId;//���ļ��ж�ȡ��id��
		string fName;
		string fPwd;
		while (ifs>>fId && ifs>>fName && ifs>>fPwd){//�����ո�ifs��ȡ�ͽ���
			//cout << fId << " " << fName << " " << fPwd << endl;
			if (fId == id && fName == name && fPwd == pwd){//���û��������Ϣ���Ա�
				cout << "ѧ�������֤�ɹ���" << endl;
				system("pause");
				system("cls");
				
				person = new Student(id, name, pwd);//���������ѧ������
				//����ѧ����ݵ��Ӳ˵�
				studentMenu(person);//�ӿڶԽ�
				return;
			}
		}
	}
	else if (type == 2){//��ʦ�����֤
		//���ļ��ж�ȡ��ʦid
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {//�����ո�ifs��ȡ�ͽ���
			//cout << fId << " " << fName << " " << fPwd << endl;
			if (fId == id && fName == name && fPwd == pwd) {//���û��������Ϣ���Ա�
				cout << "��ʦ�����֤�ɹ���" << endl;
				system("pause");
				system("cls");

				person = new Teacher(id, name, pwd);//��������Ľ�ʦ����
				//�����ʦ��ݵ��Ӳ˵�
				teacherMenu(person);//�ӿڶԽ�
				return;
			}
		}
	}
	else if (type == 3){//����Ա�����֤
		//���ļ��ж�ȡ����Ա����������
		string fName;
		string fPwd;
		while (ifs >> fName && ifs >> fPwd) {//�����ո�ifs��ȡ�ͽ���
			//cout << fId << " " << fName << " " << fPwd << endl;
			if ( fName == name && fPwd == pwd) {//���û��������Ϣ���Ա�
				cout << "����Ա�����֤�ɹ���" << endl;
				system("pause");
				system("cls");

				person = new Manager( name, pwd);//��������Ĺ���Ա����
				//�������Ա��ݵ��Ӳ˵�
				managerMenu(person);//�ӿڶԽ�
				return;
			}
		}
	}
	cout << "�û���������������󣬵�½ʧ�ܣ�" << endl;
	system("pause");
	system("cls");
	return;
}

int main() {
	int select = 0;//�����û�����
	while (true) {
		cout << " ==============��ӭʹ�û���ԤԼϵͳϵͳ============" << endl;
		cout << endl << "�����������ݣ�" << endl;
		cout << "\t\t--����������������������������----" << endl;
		cout << "\t\t|             1.ѧ������         |" << endl;
		cout << "\t\t|                                |" << endl;
		cout << "\t\t|             2.��  ʦ           |" << endl;
		cout << "\t\t|                                |" << endl;
		cout << "\t\t|             3.����Ա           |" << endl;
		cout << "\t\t|                                |" << endl;
		cout << "\t\t|             0.��  ��           |" << endl;
		cout << "\t\t|                                |" << endl;
		cout << "\t\t-����������������������������-----" << endl;
		cout << "����������ѡ��:" << endl;
		cin >> select;
		switch (select) {
		case 1://ѧ�����
			LoginIn(STUDENT_FILE, 1);

			break;
		case 2://��ʦ���
			LoginIn(TEACHER_FILE, 2);

			break;
		case 3://����Ա���
			LoginIn(ADMIN_FILE, 3);

			break;
		case 0://�˳�����
			cout << "��ӭ�´�ʹ��!" << endl;
			system("pause");
			return 0;
			break;
		default://�������
			cout << "�����������������룡" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	return 0;
}
	