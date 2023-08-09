#define _CRT_SECURE_NO_WARNINGS 1
#include "teacher.h"

//Ĭ�Ϲ���
Teacher::Teacher() {

}

//�вι���(ְ���ţ�����������)
Teacher::Teacher(int empId, string name, string pwd) {
	//��ʼ������
	this->m_EmpId = empId;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

//��������
void Teacher::operMenu() {//�����˵�  ���麯��
	cout << " ��ӭ��ʦ: " << this->m_Name << "��¼��" << endl;
	cout << "\t\t--����������������������������---------" << endl;
	cout << "\t\t|              1.�鿴����ԤԼ         |" << endl;
	cout << "\t\t|                                     |" << endl;
	cout << "\t\t|              2.���ԤԼ             |" << endl;
	cout << "\t\t|                                     |" << endl;
	cout << "\t\t|              0.ע����¼             |" << endl;
	cout << "\t\t|                                     |" << endl;
	cout << "\t\t-����������������������-����-----------" << endl;
	cout << "��ѡ�����Ĳ���:" << endl;

}

//�鿴����ԤԼ
void Teacher::showAllOrder() {
	OrderFile of;//�õ�����ԤԼ������
	if (of.m_Size == 0) {
		cout << "��ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_Size; i++) {
		cout << i + 1 << "��";

		cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"];
		cout << " ʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");//��Ŀ����
		cout << " ѧ�ţ�" << of.m_orderData[i]["stuID"];
		cout << " ������" << of.m_orderData[i]["stuName"];
		cout << " ������" << of.m_orderData[i]["roomID"];
		string status = " ״̬��";// 0 ȡ����ԤԼ   1 �����    2 ��ԤԼ     -1 ԤԼʧ��
		if (of.m_orderData[i]["status"] == "1") {
			status += "�����";
		}
		else if (of.m_orderData[i]["status"] == "2") {
			status += "ԤԼ�ɹ�";
		}
		else if (of.m_orderData[i]["status"] == "-1") {
			status += "���δͨ����ԤԼʧ��";
		}
		else {
			status += "ԤԼ��ȡ��";
		}
		cout << status << endl;
	}

	system("pause");
	system("cls");
}

//���ԤԼ
void Teacher::validOrder() {
	OrderFile of;
	if (of.m_Size == 0){
		cout << "��ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "����˼�¼���£�" << endl;
	int index = 0;
	vector<int>v;
	for (int i = 0; i < of.m_Size; i++){
		if (of.m_orderData[i]["status"] == "1"){
			v.push_back(i);
			cout << ++index << "��";

			cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"];
			cout << " ʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");//��Ŀ����
			cout << " ѧ�ţ�" << of.m_orderData[i]["stuID"];
			cout << " ������" << of.m_orderData[i]["stuName"];
			cout << " ������ţ�" << of.m_orderData[i]["roomID"];
			string status = " ״̬��";// 0 ȡ����ԤԼ   1 �����    2 ��ԤԼ     -1 ԤԼʧ��
			if (of.m_orderData[i]["status"] == "1") {
				status += "�����";
			}
			cout << status << endl;
		}
	}
	cout << "������Ҫ��˵�ԤԼ��¼��0������" << endl;
	int select = 0; //�����û�ѡ��ĵڼ���ԤԼ��¼
	int ret = 0;//����ԤԼ�����¼�� �Ƿ� ͬ��
	while (true){
		cin >> select;
		if (select >= 0 && select <= of.m_Size){
			if (select == 0){
				break;
			}
			else{
				cout << "�Ƿ�ͬ��ԤԼ��" << endl;
				cout << "1.ͬ��" << endl;
				cout << "2.��ͬ��"<<endl;
				while (true)
				{
					cin >> ret;
					if (ret == 1) {//ͨ��
						of.m_orderData[v[select - 1]]["status"] = "2";
						break;
					}
					else if (ret == 2){//�ܾ�
						of.m_orderData[v[select - 1]]["status"] = "-1";
						break;
					}
					cout << "�����������������룡" << endl;
				}
				of.updateOrder();//������Ϣ
				cout << "�����ϣ�" << endl;
				break;
			}
		}
		cout << "�����������������룡" << endl;
	}
	system("pause");
	system("cls");
}