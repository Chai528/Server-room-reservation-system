#include "manager.h"

//默认构造
Manager::Manager() {

}

//有参构造（姓名，密码）
Manager::Manager(string name, string pwd) {
	//初始化管理员信息
	this->m_Name = name;
	this->m_Pwd = pwd;
	this->initVector();//初始化容器，获取到所有文件中 学生、老师的信息

	//由于后续不改动，所以写在这里而没有封装成一个函数
	ifstream ifs;
	ifs.open(COMPUTER_FILE,ios::in);

	ComputerRoom c;
	while (ifs>>c.m_ComID && ifs>>c.m_MaxNum){
		vCom.push_back(c);
	}
	cout << "当前机房的数量为：" << vCom.size() << endl;
	ifs.close();
}

//选择界面
void Manager::operMenu() {
	cout << " 欢迎管理员: "<<this->m_Name<<"登录！" << endl;
	cout << "\t\t--——————————————------" << endl;
	cout << "\t\t|             1.添加账号           |" << endl;
	cout << "\t\t|                                  |" << endl;
	cout << "\t\t|             2.查看账号           |" << endl;
	cout << "\t\t|                                  |" << endl;
	cout << "\t\t|             3.查看机房           |" << endl;
	cout << "\t\t|                                  |" << endl;
	cout << "\t\t|             4.清空预约           |" << endl;
	cout << "\t\t|                                  |" << endl;
	cout << "\t\t|             0.注销登录           |" << endl;
	cout << "\t\t|                                  |" << endl;
	cout << "\t\t-——————————————-------" << endl;
	cout << "请选择您的操作:" << endl;
}

//添加账号
void Manager::addPerson() {
	cout << "输入添加账号的类型：" << endl;
	cout << "1.学生账号" << endl;
	cout << "2.教师账号" << endl;
	
	string fileName;//操作文件名
	string tip;//提示是学生还是老师
	ofstream ofs;//写文件操作对象
	string errTip;//重复错误提示

	int select = 0;
	cin >> select;

	if (select == 1){//添加学生
		fileName = STUDENT_FILE;
		tip = "请输入你的学号:";
		errTip = "学号重复，请重新输入!";
	}
	else{//添加教师
		fileName = TEACHER_FILE;
		tip = "请输入你的职工号：";
		errTip = "职工号重复，请重新输入!";
	}
	ofs.open(fileName,ios::out | ios::app);//利用追加方式 写文件
	int id;//保存用户的输入信息
	string name;
	string pwd;
	cout << tip << endl;
	while (true) {
		cin >> id;
		bool ret = checkRepeat(id, select);
		if (ret){//有重复
			cout << errTip << endl;
		}
		else{
			break;
		}
	}

	cout << "请输入你的姓名：" << endl;
	cin >> name;
	cout << "请输入你的密码：" << endl;
	cin >> pwd;

	
	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "添加成功！" << endl;
	system("pause");
	system("cls");

	ofs.close();

	//重新初始化容器，因为刚才又加入了一个
	this->initVector();
}
//打印学生信息
void printStudent(Student &s) {
	cout << "学号：" << s.m_Id << " 姓名：" << s.m_Name << " 密码：" << s.m_Pwd << endl;
}
//打印教师信息
void printTeacher(Teacher& t) {
	cout << "职工号：" << t.m_EmpId << " 姓名：" << t.m_Name << " 密码：" << t.m_Pwd << endl;
}
//查看账号
void Manager::showPerson() {
	cout << "请选择查看的内容" << endl;
	cout << "1.查看所有学生" << endl;
	cout << "2.查看所有教师"<<endl;
	int select = 0;//接收用户选择
	cin >> select;
	if (select == 1){
		cout << "所有学生的信息如下：" << endl;
		for_each(vStu.begin(),vStu.end(),printStudent);
	}
	else {
		cout << "所有教师的信息如下：" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}
	system("pause");
	system("cls");
}

//查看机房信息
void Manager::showComputer() {
	cout << "机房的信息如下："<<endl;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++){
		cout << "机房编号：" << it->m_ComID << "  机房最大容量：" << it->m_MaxNum<<endl;
	}
	system("pause");
	system("cls");
}

//清空文件
void Manager::clearFile() {
	ofstream ofs(ORDER_FILE,ios::trunc);//trunc是把文件删除并重新建立，相当于清空了文件

	ofs.close();
	cout << "预约清空成功！" << endl;
	system("pause");
	system("cls");
}

//初始化容器（防止录入重复的人员）
void Manager::initVector() {
	//确保容器清空状态
	vStu.clear();
	vTea.clear();

	ifstream ifs;
	//读取学生文件中信息
	ifs.open(STUDENT_FILE,ios::in);
	if (!ifs.is_open()){
		cout << "学生文件打开失败" << endl;
		return;
	}
	
	Student s;
	while (ifs>>s.m_Id && ifs>>s.m_Name && ifs>>s.m_Pwd){
		vStu.push_back(s);
	}
	cout << "当前学生的数量为：" << vStu.size() << endl;
	ifs.close();//学生初始化

	//读取教师文件中的信息
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "教师文件打开失败" << endl;
		return;
	}
	Teacher t;
	while (ifs>>t.m_EmpId && ifs>>t.m_Name && ifs>>t.m_Pwd){
		vTea.push_back(t);
	}
	cout << "当前教师的数量为：" << vTea.size() << endl;
	ifs.close();//教师初始化
}

//检测重复输入
bool Manager::checkRepeat(int id, int type) {
	if (type == 1){//学生重复检测
		for (vector<Student>::iterator it = vStu.begin();it != vStu.end();it++ ){
			if (id == it->m_Id) {
				return true;//有重复
			}
		}
	}
	else{
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++) {
			if (id == it->m_EmpId) {
				return true;//有重复
			}
		}
	}
	return false;//无重复
}