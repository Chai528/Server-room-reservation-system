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
		//教师操作界面
		teacher->operMenu();
		Teacher* tea = (Teacher*)teacher;

		int select = 0;
		cin >> select;
		if (select == 1){
			//查看所有预约
			tea->showAllOrder();
		}
		else if(select == 2){
			//审核预约
			tea->validOrder();
		}
		else{
			//注销登录
			delete teacher;
			cout << "注销教师登录成功！" << endl;
			system("pause");
			system("cls");
			return;
		}
	}


}
void studentMenu(Identity* &student) {
	while (true){
		//学生操作菜单
		student->operMenu();
		Student* stu = (Student *)student;//强转

		int select = 0;
		cin >> select;
		if (select == 1){//申请预约
			stu->applyOrder();
		}
		else if (select == 2){//查看我的预约
			stu->showMyOrder();
		}
		else if (select == 3){//查看所有预约
			stu->showAllOrder();
		}
		else if (select == 4) {//取消预约
			stu->cancelOrder();
		}
		else{//注销登录
			delete student;//销毁掉堆区对象
			cout << "学生注销登录成功！" << endl;
			system("pause");
			system("cls");
			return;
		}

	}
}
void managerMenu(Identity* &manager) {
/* 这里出现了指针的引用这个东西，也不难理解，把identity*当做一个类，类名后加&，就是应用这个类的对象，所以这里是以引用的方式来接收identity类的指针实参
   加不加&的区别就在于，不加，重新开辟空间并创建了一个指名为manager的指针，这个指针内部存放的数据是对实参数据的拷贝（拷贝了一块地址编号）
   加了&，如果不考虑引用的本质，那么就相当于给实参指针起了第二个名字，叫做manager，我们可以通过manager这个名字直接去调用实参
   这里还要再补上的一个知识点就是，形参是n级指针，实参也是n级指针时，形参指针不会指向实参，而是进行对实参的拷贝，如果想让指针指向指针，那么形参指针需要比实参指针高一级*/
	while (true){
		//管理员菜单
		manager->operMenu();
		int select = 0;
		Manager* man = (Manager*) manager;//将父类对象 强转 为子类对象，方便使用子类对象调用其他的接口
		cin >> select;
		if (select == 1){
			//添加账号
			man->addPerson();
		}
		else if (select == 2) {
			//查看账号
			man->showPerson();
		}
		else if (select == 3) {
			//查看机房
			man->showComputer();
		}
		else if (select == 4) {
			//清空预约
			man->clearFile();
		}
		else{
			//注销登录
			delete manager;    //销毁掉堆区对象
			cout << "注销成功！" << endl;
			system("pause");
			system("cls");
			return;
		}
	}

}
//登录功能
void LoginIn(string fileName,int type) { //type代表身份类型，1--学生，2--老师，3--管理员
	Identity* person = NULL;//父类指针指向子类对象

	//读的形式打开
	ifstream ifs;
	ifs.open(fileName,ios::in);

	//判断文件是否存在
	if ( !ifs.is_open() ){
		cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}
	//准备接收用户信息
	int id = 0;
	string name;
	string pwd;
	//判断身份
	if (type == 1){//学生身份
		cout << "请输入你的学号：" << endl;
		cin >> id;
	}else if (type == 2 ){//老师身份
		cout << "请输入你的职工号：" << endl;
		cin >> id;
	}

	cout << "请输入你的姓名：" << endl;
	cin >> name;
	cout << "请输入你的密码：" << endl;
	cin >> pwd;

	if (type == 1){//学生身份验证
		int fId;//从文件中读取的id号
		string fName;
		string fPwd;
		while (ifs>>fId && ifs>>fName && ifs>>fPwd){//遇到空格ifs读取就结束
			//cout << fId << " " << fName << " " << fPwd << endl;
			if (fId == id && fName == name && fPwd == pwd){//与用户输入的信息做对比
				cout << "学生身份验证成功！" << endl;
				system("pause");
				system("cls");
				
				person = new Student(id, name, pwd);//创建具体的学生对象
				//进入学生身份的子菜单
				studentMenu(person);//接口对接
				return;
			}
		}
	}
	else if (type == 2){//教师身份验证
		//从文件中读取教师id
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {//遇到空格ifs读取就结束
			//cout << fId << " " << fName << " " << fPwd << endl;
			if (fId == id && fName == name && fPwd == pwd) {//与用户输入的信息做对比
				cout << "教师身份验证成功！" << endl;
				system("pause");
				system("cls");

				person = new Teacher(id, name, pwd);//创建具体的教师对象
				//进入教师身份的子菜单
				teacherMenu(person);//接口对接
				return;
			}
		}
	}
	else if (type == 3){//管理员身份验证
		//从文件中读取管理员姓名和密码
		string fName;
		string fPwd;
		while (ifs >> fName && ifs >> fPwd) {//遇到空格ifs读取就结束
			//cout << fId << " " << fName << " " << fPwd << endl;
			if ( fName == name && fPwd == pwd) {//与用户输入的信息做对比
				cout << "管理员身份验证成功！" << endl;
				system("pause");
				system("cls");

				person = new Manager( name, pwd);//创建具体的管理员对象
				//进入管理员身份的子菜单
				managerMenu(person);//接口对接
				return;
			}
		}
	}
	cout << "用户名或密码输入错误，登陆失败！" << endl;
	system("pause");
	system("cls");
	return;
}

int main() {
	int select = 0;//接收用户输入
	while (true) {
		cout << " ==============欢迎使用机房预约系统系统============" << endl;
		cout << endl << "请输入你的身份？" << endl;
		cout << "\t\t--——————————————----" << endl;
		cout << "\t\t|             1.学生代表         |" << endl;
		cout << "\t\t|                                |" << endl;
		cout << "\t\t|             2.老  师           |" << endl;
		cout << "\t\t|                                |" << endl;
		cout << "\t\t|             3.管理员           |" << endl;
		cout << "\t\t|                                |" << endl;
		cout << "\t\t|             0.退  出           |" << endl;
		cout << "\t\t|                                |" << endl;
		cout << "\t\t-——————————————-----" << endl;
		cout << "请输入您的选择:" << endl;
		cin >> select;
		switch (select) {
		case 1://学生身份
			LoginIn(STUDENT_FILE, 1);

			break;
		case 2://老师身份
			LoginIn(TEACHER_FILE, 2);

			break;
		case 3://管理员身份
			LoginIn(ADMIN_FILE, 3);

			break;
		case 0://退出功能
			cout << "欢迎下次使用!" << endl;
			system("pause");
			return 0;
			break;
		default://输入错误
			cout << "输入有误，请重新输入！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	return 0;
}
	