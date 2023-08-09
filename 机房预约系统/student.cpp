#define _CRT_SECURE_NO_WARNINGS 1
#include "student.h"

//Ĭ�Ϲ���
Student::Student() {

}

//�вι���(ѧ�š�����������)
Student::Student(int id, string name, string pwd) {
	//��ʼ������
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	//��ȡ��������Ϣ
	ifstream ifs;
	ifs.open(COMPUTER_FILE,ios::in);

	ComputerRoom c;//��ȡ��������
	while (ifs>>c.m_ComID && ifs>>c.m_MaxNum){
		vCom.push_back(c);
	}
	ifs.close();
}

//�����˵�����   ������д�����е��麯��
void Student::operMenu() {
	cout << " ��ӭѧ������: " << this->m_Name << "��¼��" << endl;
	cout << "\t\t--����������������������������---------" << endl;
	cout << "\t\t|             1.����ԤԼ              |" << endl;
	cout << "\t\t|                                     |" << endl;
	cout << "\t\t|             2.�鿴�ҵ�ԤԼ          |" << endl;
	cout << "\t\t|                                     |" << endl;
	cout << "\t\t|             3.�鿴����ԤԼ          |" << endl;
	cout << "\t\t|                                     |" << endl;
	cout << "\t\t|             4.ȡ��ԤԼ              |" << endl;
	cout << "\t\t|                                     |" << endl;
	cout << "\t\t|             0.ע����¼              |" << endl;
	cout << "\t\t|                                     |" << endl;
	cout << "\t\t-����������������������-����-----------" << endl;
	cout << "��ѡ�����Ĳ���:" << endl;
}

//����ԤԼ
void Student::applyOrder() {
	cout << "��������ʱ��Ϊ��һ�����壡" << endl;
	cout << "����������ԤԼ��ʱ�䣺" << endl;
	cout << "1.��һ" << endl;
	cout << "2.�ܶ�" << endl;
	cout << "3.����" << endl;
	cout << "4.����" << endl;
	cout << "5.����" << endl;
	int date = 0;//����
	while (true){
		cin >> date;
		if (date>=1 && date<= 5){
			break;
		}
		cout << "����������������룡" << endl;
	}
	cout << "����������ԤԼ��ʱ��Σ�" << endl;
	cout << "1.����" << endl;
	cout << "2.����" << endl;
	int interval = 0;//ʱ���
	while (true) {
		cin >> interval;
		if (interval == 1 || interval == 2) {
			break;
		}
		cout << "����������������룡" << endl;
	}
	cout << "��ѡ�������" << endl;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++){
		cout << it->m_ComID << "�Ż�������:" << it->m_MaxNum << endl;
	}
	int roomID = 0;//�������
	while (true) {
		cin >> roomID;
		if (roomID >= 1 && roomID <= vCom.size()) {
			break;
		}
		cout << "����������������룡" << endl;
	}
	ofstream ofs;
	ofs.open(ORDER_FILE,ios::out | ios::app);
	ofs << "date:" << date << " "
		<< "interval:" << interval << " "
		<< "stuID:" << this->m_Id << " "
		<< "stuName:" << this->m_Name << " "
		<< "roomID:" << roomID << " "
		<< "status:" << 1 << endl;//ԤԼ״̬��1����ԤԼ

	cout << "ԤԼ�ɹ�������У���" << endl;
	ofs.close();
	system("pause");
	system("cls");
}

//�鿴�ҵ�ԤԼ
void Student::showMyOrder() {
	OrderFile of;
	if (of.m_Size == 0){
		cout << "��ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_Size; i++){
		//string ���� .c_str() תΪ const char *
		//����  atoi(const char *) ת int
		if (atoi(of.m_orderData[i]["stuID"].c_str()) == this->m_Id){//��string����תΪint����     �ҵ������ԤԼ
			cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"];
			cout << " ʱ��:" << (of.m_orderData[i]["interval"] == "1" ? "����":"����");//��Ŀ����
			cout << " ������" << of.m_orderData[i]["roomID"];
			string status = " ״̬��";// 0 ȡ����ԤԼ   1 �����    2 ��ԤԼ     -1 ԤԼʧ��
			if (of.m_orderData[i]["status"]=="1"){
				status += "�����";
			}
			else if (of.m_orderData[i]["status"] == "2"){
				status += "ԤԼ�ɹ�";
			}
			else if (of.m_orderData[i]["status"] == "-1") {
				status += "���δͨ����ԤԼʧ��";
			}
			else  {
				status += "ԤԼ��ȡ��";
			}
			cout << status << endl;
		}
	}
	system("pause");
	system("cls");
}

//�鿴����ԤԼ
void Student::showAllOrder() {
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

//ȡ��ԤԼ
void Student::cancelOrder() {
	OrderFile of;
	if (of.m_Size == 0){
		cout << "��ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "����л�ԤԼ�ɹ��ļ�¼����ȡ����������ȡ���ļ�¼" << endl;
	int index = 1;
	vector<int>v;//��Ŷ�Ӧ�Ĵ�map������ĵ�i����¼ ���±�
	for (int i = 0; i < of.m_Size; i++){
		//�ҵ������ԤԼ��¼
		if (atoi(of.m_orderData[i]["stuID"].c_str()) == this->m_Id){
			//ɸѡ״̬Ϊ 1��2 �ļ�¼
			if (of.m_orderData[i]["status"]=="1" || of.m_orderData[i]["status"] == "2"){
				v.push_back(i);
				cout << index++ << "��" ;
				cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"];
				cout << " ʱ��:" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");//��Ŀ����
				cout << " ������ţ�" << of.m_orderData[i]["roomID"];
				string status = " ״̬��";// 0 ȡ����ԤԼ   1 �����    2 ��ԤԼ     -1 ԤԼʧ��
				if (of.m_orderData[i]["status"] == "1") {
					status += "�����";
				}
				else if (of.m_orderData[i]["status"] == "2") {
					status += "ԤԼ�ɹ�";
				}
				cout << status << endl;
			}
		}
	}
	cout << "������ȡ���ڼ�����¼��0������" << endl;
	int select = 0;
	while (true){
		cin >> select;
		if (select >= 0 && select <= v.size()) {
			if (select == 0) {
				break;//����
			}
			else {
				of.m_orderData[v[select - 1]]["status"] = "0";
				//�����ļ�
				of.updateOrder();
				cout << "��ȡ��ԤԼ��" << endl;
				break;
			}
		}
		cout << "������������������" << endl;
	}
	system("pause");
	system("cls");
}