#define _CRT_SECURE_NO_WARNINGS 1
#include "student.h"

//默认构造
Student::Student() {

}

//有参构造(学号、姓名、密码)
Student::Student(int id, string name, string pwd) {
	//初始化属性
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	//获取机房的信息
	ifstream ifs;
	ifs.open(COMPUTER_FILE,ios::in);

	ComputerRoom c;//读取机房数据
	while (ifs>>c.m_ComID && ifs>>c.m_MaxNum){
		vCom.push_back(c);
	}
	ifs.close();
}

//操作菜单界面   子类重写父类中的虚函数
void Student::operMenu() {
	cout << " 欢迎学生代表: " << this->m_Name << "登录！" << endl;
	cout << "\t\t--——————————————---------" << endl;
	cout << "\t\t|             1.申请预约              |" << endl;
	cout << "\t\t|                                     |" << endl;
	cout << "\t\t|             2.查看我的预约          |" << endl;
	cout << "\t\t|                                     |" << endl;
	cout << "\t\t|             3.查看所有预约          |" << endl;
	cout << "\t\t|                                     |" << endl;
	cout << "\t\t|             4.取消预约              |" << endl;
	cout << "\t\t|                                     |" << endl;
	cout << "\t\t|             0.注销登录              |" << endl;
	cout << "\t\t|                                     |" << endl;
	cout << "\t\t-———————————-——-----------" << endl;
	cout << "请选择您的操作:" << endl;
}

//申请预约
void Student::applyOrder() {
	cout << "机房开放时间为周一至周五！" << endl;
	cout << "请输入申请预约的时间：" << endl;
	cout << "1.周一" << endl;
	cout << "2.周二" << endl;
	cout << "3.周三" << endl;
	cout << "4.周四" << endl;
	cout << "5.周五" << endl;
	int date = 0;//日期
	while (true){
		cin >> date;
		if (date>=1 && date<= 5){
			break;
		}
		cout << "输入错误，请重新输入！" << endl;
	}
	cout << "请输入申请预约的时间段：" << endl;
	cout << "1.上午" << endl;
	cout << "2.下午" << endl;
	int interval = 0;//时间段
	while (true) {
		cin >> interval;
		if (interval == 1 || interval == 2) {
			break;
		}
		cout << "输入错误，请重新输入！" << endl;
	}
	cout << "请选择机房：" << endl;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++){
		cout << it->m_ComID << "号机房容量:" << it->m_MaxNum << endl;
	}
	int roomID = 0;//机房编号
	while (true) {
		cin >> roomID;
		if (roomID >= 1 && roomID <= vCom.size()) {
			break;
		}
		cout << "输入错误，请重新输入！" << endl;
	}
	ofstream ofs;
	ofs.open(ORDER_FILE,ios::out | ios::app);
	ofs << "date:" << date << " "
		<< "interval:" << interval << " "
		<< "stuID:" << this->m_Id << " "
		<< "stuName:" << this->m_Name << " "
		<< "roomID:" << roomID << " "
		<< "status:" << 1 << endl;//预约状态，1是在预约

	cout << "预约成功！审核中！！" << endl;
	ofs.close();
	system("pause");
	system("cls");
}

//查看我的预约
void Student::showMyOrder() {
	OrderFile of;
	if (of.m_Size == 0){
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_Size; i++){
		//string 利用 .c_str() 转为 const char *
		//利用  atoi(const char *) 转 int
		if (atoi(of.m_orderData[i]["stuID"].c_str()) == this->m_Id){//将string类型转为int类型     找到自身的预约
			cout << "预约日期：周" << of.m_orderData[i]["date"];
			cout << " 时段:" << (of.m_orderData[i]["interval"] == "1" ? "上午":"下午");//三目运算
			cout << " 机房：" << of.m_orderData[i]["roomID"];
			string status = " 状态：";// 0 取消的预约   1 审核中    2 已预约     -1 预约失败
			if (of.m_orderData[i]["status"]=="1"){
				status += "审核中";
			}
			else if (of.m_orderData[i]["status"] == "2"){
				status += "预约成功";
			}
			else if (of.m_orderData[i]["status"] == "-1") {
				status += "审核未通过，预约失败";
			}
			else  {
				status += "预约已取消";
			}
			cout << status << endl;
		}
	}
	system("pause");
	system("cls");
}

//查看所有预约
void Student::showAllOrder() {
	OrderFile of;//拿到所有预约的数据
	if (of.m_Size == 0) {
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_Size; i++) {
		cout << i + 1 << "、";

		cout << "预约日期：周" << of.m_orderData[i]["date"];
		cout << " 时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");//三目运算
		cout << " 学号：" << of.m_orderData[i]["stuID"];
		cout << " 姓名：" << of.m_orderData[i]["stuName"];
		cout << " 机房：" << of.m_orderData[i]["roomID"];
		string status = " 状态：";// 0 取消的预约   1 审核中    2 已预约     -1 预约失败
		if (of.m_orderData[i]["status"] == "1") {
			status += "审核中";
		}
		else if (of.m_orderData[i]["status"] == "2") {
			status += "预约成功";
		}
		else if (of.m_orderData[i]["status"] == "-1") {
			status += "审核未通过，预约失败";
		}
		else {
			status += "预约已取消";
		}
		cout << status << endl;
	}
	
	system("pause");
	system("cls");
}

//取消预约
void Student::cancelOrder() {
	OrderFile of;
	if (of.m_Size == 0){
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "审核中或预约成功的记录可以取消，请输入取消的记录" << endl;
	int index = 1;
	vector<int>v;//存放对应的大map容器里的第i条记录 的下标
	for (int i = 0; i < of.m_Size; i++){
		//找到自身的预约记录
		if (atoi(of.m_orderData[i]["stuID"].c_str()) == this->m_Id){
			//筛选状态为 1或2 的记录
			if (of.m_orderData[i]["status"]=="1" || of.m_orderData[i]["status"] == "2"){
				v.push_back(i);
				cout << index++ << "、" ;
				cout << "预约日期：周" << of.m_orderData[i]["date"];
				cout << " 时段:" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");//三目运算
				cout << " 机房编号：" << of.m_orderData[i]["roomID"];
				string status = " 状态：";// 0 取消的预约   1 审核中    2 已预约     -1 预约失败
				if (of.m_orderData[i]["status"] == "1") {
					status += "审核中";
				}
				else if (of.m_orderData[i]["status"] == "2") {
					status += "预约成功";
				}
				cout << status << endl;
			}
		}
	}
	cout << "请输入取消第几条记录，0代表返回" << endl;
	int select = 0;
	while (true){
		cin >> select;
		if (select >= 0 && select <= v.size()) {
			if (select == 0) {
				break;//返回
			}
			else {
				of.m_orderData[v[select - 1]]["status"] = "0";
				//更新文件
				of.updateOrder();
				cout << "已取消预约！" << endl;
				break;
			}
		}
		cout << "输入有误，请重新输入" << endl;
	}
	system("pause");
	system("cls");
}