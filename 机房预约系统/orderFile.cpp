#include "orderFile.h"

//���캯��
OrderFile::OrderFile() {
	ifstream ifs;
	ifs.open(ORDER_FILE,ios::in);
	string date;
	string interval;
	string stuID;
	string stuName;
	string roomID;
	string status;

	//��ʼ����¼����
	this->m_Size = 0;

	while (ifs>>date && ifs>>interval && ifs>>stuID && ifs>>stuName && ifs>>roomID && ifs>>status){
		
		//date:111
		string key;//��¼����
		string value;//��¼ֵ
		map<string, string>m;
		int pos = date.find(":");//4
		if (pos != -1){
			key = date.substr(0,pos);//��0λ��ʼ����ȡ4����pos=4
			value = date.substr(pos+1,date.size()-pos-1);  //8-pos -1= 8 - 4 -1=3

			m.insert(make_pair(key,value));
		}
		/*cout << "key = " << key << endl;
		cout << "value = " << value << endl;*/

		pos = interval.find(":");//4
		if (pos != -1) {
			key = interval.substr(0, pos);//��0λ��ʼ����ȡ4����pos=4
			value = interval.substr(pos + 1, interval.size() - pos - 1);  //8-pos -1= 8 - 4 -1=3

			m.insert(make_pair(key, value));
		}

		pos = stuID.find(":");//4
		if (pos != -1) {
			key = stuID.substr(0, pos);//��0λ��ʼ����ȡ4����pos=4
			value = stuID.substr(pos + 1, stuID.size() - pos - 1);  //8-pos -1= 8 - 4 -1=3

			m.insert(make_pair(key, value));
		}

		pos = stuName.find(":");//4
		if (pos != -1) {
			key = stuName.substr(0, pos);//��0λ��ʼ����ȡ4����pos=4
			value = stuName.substr(pos + 1, stuName.size() - pos - 1);  //8-pos -1= 8 - 4 -1=3

			m.insert(make_pair(key, value));
		}

		pos = roomID.find(":");//4
		if (pos != -1) {
			key = roomID.substr(0, pos);//��0λ��ʼ����ȡ4����pos=4
			value = roomID.substr(pos + 1, roomID.size() - pos - 1);  //8-pos -1= 8 - 4 -1=3

			m.insert(make_pair(key, value));
		}

		pos = status.find(":");//4
		if (pos != -1) {
			key = status.substr(0, pos);//��0λ��ʼ����ȡ4����pos=4
			value = status.substr(pos + 1, status.size() - pos - 1);  //8-pos -1= 8 - 4 -1=3

			m.insert(make_pair(key, value));
		}

		this->m_orderData.insert(make_pair(m_Size,m));//��С����m ������map����
		this->m_Size++;//һ����Ϣ��ɣ�++

	}
	ifs.close();

	//�������map����
	/*for (map<int,map<string,string>>::iterator it = m_orderData.begin(); it != m_orderData.end(); it++){
		cout << "��¼��" << it->first << "��  value=" << endl;
		for (map<string,string>::iterator mit = (*it).second.begin(); mit != it->second.end(); mit++){
			cout << "key=" << mit->first << " value=" << (*mit).second << " ";
		}
		cout << endl;
	}*/
}

//����ԤԼ��¼
void OrderFile::updateOrder() {
	if (this->m_Size == 0){
		return;
	}

	ofstream ofs(ORDER_FILE,ios::out|ios::trunc);
	for (int i = 0; i < this->m_Size; i++){
		ofs << "date:" << m_orderData[i]["date"] << " ";
		ofs << "interval:" << m_orderData[i]["interval"] << " ";
		ofs << "stuID:" << m_orderData[i]["stuID"] << " ";
		ofs << "stuName:" << m_orderData[i]["stuName"] << " ";
		ofs << "roomID:" << m_orderData[i]["roomID"] << " ";
		ofs << "status:" << m_orderData[i]["status"] << endl;
	}
	ofs.close();
}