#include "manager.h"

//Ĭ�Ϲ���
Manager::Manager() {

}

//�вι��죨���������룩
Manager::Manager(string name, string pwd) {
	//��ʼ������Ա��Ϣ
	this->m_Name = name;
	this->m_Pwd = pwd;
	this->initVector();//��ʼ����������ȡ�������ļ��� ѧ������ʦ����Ϣ

	//���ں������Ķ�������д�������û�з�װ��һ������
	ifstream ifs;
	ifs.open(COMPUTER_FILE,ios::in);

	ComputerRoom c;
	while (ifs>>c.m_ComID && ifs>>c.m_MaxNum){
		vCom.push_back(c);
	}
	cout << "��ǰ����������Ϊ��" << vCom.size() << endl;
	ifs.close();
}

//ѡ�����
void Manager::operMenu() {
	cout << " ��ӭ����Ա: "<<this->m_Name<<"��¼��" << endl;
	cout << "\t\t--����������������������������------" << endl;
	cout << "\t\t|             1.����˺�           |" << endl;
	cout << "\t\t|                                  |" << endl;
	cout << "\t\t|             2.�鿴�˺�           |" << endl;
	cout << "\t\t|                                  |" << endl;
	cout << "\t\t|             3.�鿴����           |" << endl;
	cout << "\t\t|                                  |" << endl;
	cout << "\t\t|             4.���ԤԼ           |" << endl;
	cout << "\t\t|                                  |" << endl;
	cout << "\t\t|             0.ע����¼           |" << endl;
	cout << "\t\t|                                  |" << endl;
	cout << "\t\t-����������������������������-------" << endl;
	cout << "��ѡ�����Ĳ���:" << endl;
}

//����˺�
void Manager::addPerson() {
	cout << "��������˺ŵ����ͣ�" << endl;
	cout << "1.ѧ���˺�" << endl;
	cout << "2.��ʦ�˺�" << endl;
	
	string fileName;//�����ļ���
	string tip;//��ʾ��ѧ��������ʦ
	ofstream ofs;//д�ļ���������
	string errTip;//�ظ�������ʾ

	int select = 0;
	cin >> select;

	if (select == 1){//���ѧ��
		fileName = STUDENT_FILE;
		tip = "���������ѧ��:";
		errTip = "ѧ���ظ�������������!";
	}
	else{//��ӽ�ʦ
		fileName = TEACHER_FILE;
		tip = "���������ְ���ţ�";
		errTip = "ְ�����ظ�������������!";
	}
	ofs.open(fileName,ios::out | ios::app);//����׷�ӷ�ʽ д�ļ�
	int id;//�����û���������Ϣ
	string name;
	string pwd;
	cout << tip << endl;
	while (true) {
		cin >> id;
		bool ret = checkRepeat(id, select);
		if (ret){//���ظ�
			cout << errTip << endl;
		}
		else{
			break;
		}
	}

	cout << "���������������" << endl;
	cin >> name;
	cout << "������������룺" << endl;
	cin >> pwd;

	
	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "��ӳɹ���" << endl;
	system("pause");
	system("cls");

	ofs.close();

	//���³�ʼ����������Ϊ�ղ��ּ�����һ��
	this->initVector();
}
//��ӡѧ����Ϣ
void printStudent(Student &s) {
	cout << "ѧ�ţ�" << s.m_Id << " ������" << s.m_Name << " ���룺" << s.m_Pwd << endl;
}
//��ӡ��ʦ��Ϣ
void printTeacher(Teacher& t) {
	cout << "ְ���ţ�" << t.m_EmpId << " ������" << t.m_Name << " ���룺" << t.m_Pwd << endl;
}
//�鿴�˺�
void Manager::showPerson() {
	cout << "��ѡ��鿴������" << endl;
	cout << "1.�鿴����ѧ��" << endl;
	cout << "2.�鿴���н�ʦ"<<endl;
	int select = 0;//�����û�ѡ��
	cin >> select;
	if (select == 1){
		cout << "����ѧ������Ϣ���£�" << endl;
		for_each(vStu.begin(),vStu.end(),printStudent);
	}
	else {
		cout << "���н�ʦ����Ϣ���£�" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}
	system("pause");
	system("cls");
}

//�鿴������Ϣ
void Manager::showComputer() {
	cout << "��������Ϣ���£�"<<endl;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++){
		cout << "������ţ�" << it->m_ComID << "  �������������" << it->m_MaxNum<<endl;
	}
	system("pause");
	system("cls");
}

//����ļ�
void Manager::clearFile() {
	ofstream ofs(ORDER_FILE,ios::trunc);//trunc�ǰ��ļ�ɾ�������½������൱��������ļ�

	ofs.close();
	cout << "ԤԼ��ճɹ���" << endl;
	system("pause");
	system("cls");
}

//��ʼ����������ֹ¼���ظ�����Ա��
void Manager::initVector() {
	//ȷ���������״̬
	vStu.clear();
	vTea.clear();

	ifstream ifs;
	//��ȡѧ���ļ�����Ϣ
	ifs.open(STUDENT_FILE,ios::in);
	if (!ifs.is_open()){
		cout << "ѧ���ļ���ʧ��" << endl;
		return;
	}
	
	Student s;
	while (ifs>>s.m_Id && ifs>>s.m_Name && ifs>>s.m_Pwd){
		vStu.push_back(s);
	}
	cout << "��ǰѧ��������Ϊ��" << vStu.size() << endl;
	ifs.close();//ѧ����ʼ��

	//��ȡ��ʦ�ļ��е���Ϣ
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "��ʦ�ļ���ʧ��" << endl;
		return;
	}
	Teacher t;
	while (ifs>>t.m_EmpId && ifs>>t.m_Name && ifs>>t.m_Pwd){
		vTea.push_back(t);
	}
	cout << "��ǰ��ʦ������Ϊ��" << vTea.size() << endl;
	ifs.close();//��ʦ��ʼ��
}

//����ظ�����
bool Manager::checkRepeat(int id, int type) {
	if (type == 1){//ѧ���ظ����
		for (vector<Student>::iterator it = vStu.begin();it != vStu.end();it++ ){
			if (id == it->m_Id) {
				return true;//���ظ�
			}
		}
	}
	else{
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++) {
			if (id == it->m_EmpId) {
				return true;//���ظ�
			}
		}
	}
	return false;//���ظ�
}