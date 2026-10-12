#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<map>
using namespace std;
struct Student {
	string id;
	string name;
	vector<double> cj;
	double suanshu() const {
		double sum = 0;
		for (double x : cj) sum += x;
		return sum;
	}
	double average() const {
		if (cj.empty()) return 0.0;
		return suanshu() / cj.size();
	}
};
void printOne(const Student& stu) {
	cout << stu.id << "\t" << stu.name << "\t";
	for (size_t i = 0; i < stu.cj.size(); ++i)
		cout << stu.cj[i] << "\t";
	cout << stu.suanshu() << "\t" << stu.average() << endl;
}
void printHeader() {
	cout << "学号\t姓名\t成绩1\t成绩2\t成绩3\t总分\t平均分" << endl;
}
bool readInt(int& value) {
	cin >> value;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(10000, '\n');
		return false;
	}
	return true;
}
bool readDouble(double& sce) {
	cin >> sce;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(10000, '\n');
		return false;
	}
	return true;
}
map<string, Student> students;
void addStudent() {
	string xuehao, xingming;
	double s1, s2, s3;
	Student m;
	cout << "请输入学号：";
	cin >> xuehao;
	cout << "请输入姓名：";
	cin >> xingming;
	cout << "请输入成绩1：";
	while (!readDouble(s1)) { cout << "输入无效，请重新输入："; }
	cout << "请输入成绩2：";
	while (!readDouble(s2)) { cout << "输入无效，请重新输入："; }
	cout << "请输入成绩3：";
	while (!readDouble(s3)) { cout << "输入无效，请重新输入："; }
	m.id = xuehao;
	m.name = xingming;
	m.cj.push_back(s1); m.cj.push_back(s2); m.cj.push_back(s3);//存入成绩
	if (students.count(xuehao) > 0) {
		cout << "学号" << xuehao << "已存在，添加失败" << endl;
		return;
	}
	students[xuehao] = m;
	cout << "添加成功!当前共" << students.size() << "名学生" << endl;
}
void showAll(const map<string,Student>& xuesheng) {
	if (xuesheng.empty()) {
		cout << "暂无学生数据" << endl;
		return;
	}
	printHeader();
	for (auto it = xuesheng.begin(); it != xuesheng.end(); ++it) {
		printOne(it->second);
	}
}
void findStu(const map<string,Student>& xuesheng) {
	string target;
	cout << "请输入要查找的学号：";
	cin >> target;
	auto it = xuesheng.find(target);
	if (it != xuesheng.end()) {
		printHeader();
		printOne(it->second);
	}
	else
		cout << "未找到学号为 " << target << " 的学生" << endl;
}
void removeStudent(map<string,Student>& xuesheng) {
	if (xuesheng.empty()) {
		cout << "暂无学生数据！" << endl;
		return;
	}
	string target;
	cout << "请输入要删除的学号：";
	cin >> target;
	auto it = xuesheng.find(target);
	if (it == xuesheng.end()) {
		cout << "未找到学号为 " << target << " 的学生" << endl;
		return;
	}
	cout << "找到学生：" << it->first << "  " << it->second.name << endl;
	cout << "确定要删除吗（y/n）：";
	char confirm;
	cin >> confirm;
	if (confirm == 'y' || confirm == 'Y') {
		xuesheng.erase(it);
		cout << "删除成功!" << endl;
	}
	else {
		cout << "已取消" << endl;
	}

}
void modifyStudent(map<string,Student>& xuesheng) {
	if (xuesheng.empty()) {
		cout << "暂无学生数据！" << endl;
		return;
	}
	string target;
	cout << "请输入要修改的学号：";
	cin >> target;
	auto it = xuesheng.find(target);
	if (it == xuesheng.end()) {
		cout << "未找到学号为 " << target << " 的学生" << endl;
		return;
	}
	cout << "找到该学生，当前信息：" << endl;
	printHeader();
	printOne(it->second);
	cout << "----------------------------" << endl;
	cout << "现在输入新信息" << endl;
	string xingming;
	double ns1, ns2, ns3;
	cout << "请输入新姓名：";
	cin >> xingming;
	cout << "请输入成绩1：";
	while (!readDouble(ns1)) { cout << "输入无效，请重新输入："; }
	cout << "请输入成绩2：";
	while (!readDouble(ns2)) { cout << "输入无效，请重新输入："; }
	cout << "请输入成绩3：";
	while (!readDouble(ns3)) { cout << "输入无效，请重新输入："; }
	it->second.name = xingming;
	it->second.cj.clear();
	it->second.cj.push_back(ns1);
	it->second.cj.push_back(ns2);
	it->second.cj.push_back(ns3);
	cout << "修改成功！" << endl;
}
bool compareByTotal(const Student& a, const Student& b) {
	return a.suanshu() > b.suanshu();
}
void sortByTotal(const map<string,Student>& xuesheng) {
	if (xuesheng.empty()) {
		cout << "暂无学生数据" << endl;
		return;
	}
	vector<Student> temp;
	for (auto it = xuesheng.begin(); it != xuesheng.end(); ++it)
		temp.push_back(it->second);
	sort(temp.begin(), temp.end(), compareByTotal);
	cout << "===== 按总分排名 =====" << endl;
	printHeader();
	for (size_t i = 0; i < temp.size(); ++i) 
		printOne(temp[i]);
}
int main() {
	int k;
	while (true) {
		cout << "===== 学生管理系统 =====" << endl;
		cout << "1.添加学生" << endl;
		cout << "2.显示所有学生" << endl;
		cout << "3.按学号查找" << endl;
		cout << "4.删除学生" << endl;
		cout << "5.修改信息" << endl;
		cout << "6.按总分排名" << endl;
		cout << "0.退出" << endl;
		cout << "请选择：";
		while (!readInt(k)) { cout << "输入无效，请重新输入："; }
		switch (k) {
		case 1:
			addStudent();
			break;
		case 2:
			showAll(students);
			break;
		case 3:
			findStu(students);
			break;
		case 4:
			removeStudent(students);
			break;
		case 5:
			modifyStudent(students);
			break;
		case 6:
			sortByTotal(students);
			break;
		case 0:
			cout << "你退出了系统" << endl;
			break;
		default:
			cout << "无效选项" << endl;
			break;
		}
		if (k == 0)
			break;

	}
	return 0;
}