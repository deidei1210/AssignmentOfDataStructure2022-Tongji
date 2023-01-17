#define NEEDPAUSE 1
#define NONEEDPAUSE 0

#include<iostream>
#include<string>
#include<iomanip>
#include "StudentNode.h"
#include "StudentList.h"

using namespace std;

//Hint表示输入内容之前的提示语
//a表示要输入的内容
//choice表示是否需要pause
template<typename T>
void PutIn(string Hint,bool choice,T& a) {
	if (choice==NEEDPAUSE) {
		//在输入内容之前，先停顿一下
		char m = 0;
		while(m!='\n')
	    	m = getchar();
	}
	//先输出提示语
	cout << Hint;
	cin >> a;
	return;
}

//Hint表示输入内容之前的提示语
//a表示要输入的内容
//choice表示是否需要pause
//range_a表示下限，range_b表示上限，如果有这两个选项说明对输入的内容会有范围的要求，一般情况下是输入整数的时候
void PutIn(string Hint, bool choice, int& a,int range_a,int range_b) {
	if (choice == NEEDPAUSE) {
		//在输入内容之前，先停顿一下
		char m = 0;
		while (m != '\n')
			m = getchar();
	}
	//先输出提示语
	cout << Hint;
	cin >> a;
	while (a<range_a || a>range_b) {
		cout << "输入的内容不在合法范围内，请重新输入！" << endl;
		cin >> a;
	}

	return;
}

//输出提示语，直到按a以继续
void ToContinue(string Hint, const char a) {
	cout << endl << Hint ;
	char m = 0;
	while (m != a) {
		m = getchar();
	}
}

//菜单显示，输出可供选择的操作选项
void menu() {
	cout << "1、输出所有考生信息        2、查询指定考生信息" << endl;
	cout << "3、添加考生信息            4、修改考生信息" << endl;
	cout << "5、删除指定考生信息        6、退出系统" << endl;
	cout << "0、查看菜单" << endl;
}

int main()
{
	cout << "首先请建立考生信息系统!(输入回车以继续建立考生信息系统)";
	
	//输入学生的总人数
	int StudentNum = 0;
	PutIn("请输入考生人数：",NEEDPAUSE, StudentNum);

	//先初始化一个链表
	StudentList Stu;
	//然后按照学生的人数创建链表
	Stu.CreateList(StudentNum);
	char m = getchar();

	//按回车打印出刚刚建立的链表
	ToContinue("恭喜你！考生信息录入完成！按回车核对录入信息！",'\n');

	Stu.PrintList();

	ToContinue("考生信息显示完毕，按回车继续......", '\n');
	menu();

	int choice = 0;                                        //表示选择的操作
	int num = 0;                                           //用于表示考生的编号
	string name = "";                                      //用于表示考生的姓名
	StudentNode* result;
	while (1) {
		PutIn("请选择您要进行的操作:",NONEEDPAUSE, choice,0,6);
		if (choice == 1) {                                 //打印全体考生的信息
			cout << "全体考生信息如下：" << endl;
			Stu.PrintList();
		}
		else if (choice == 2) {		                                              
			int c = 0;                                     //查询指定考生的信息可以通过考号也可以通过姓名
			PutIn("输入 1 进行根据考号查找考生，输入 2 进行根据姓名查找考生：",NONEEDPAUSE, c,1,2);			
			switch (c) {
				case 1:                                   //根据考号查找
					PutIn("请输入学生的考号：", NONEEDPAUSE, num);
				    result = Stu.Find(num);
					if (result != NULL) {
						cout << "考号        姓名        性别        年龄        报考类别" << endl;
						result->PrintNode();              //如果不是空指针的话说明找到了这个考生，那就可以直接输出节点信息
					}
					break;
				case 2:                                   //根据姓名查找
					PutIn("请输入学生的姓名：", NONEEDPAUSE, name);
					result = Stu.Find(name);
					if (result != NULL) {
						cout << "考号        姓名        性别        年龄        报考类别" << endl;
						result->PrintNode();              //如果不是空指针的话说明找到了这个考生，那就可以直接输出节点信息
					}
					break;
				default:
					break;
			}
		}
		else if (choice == 3) {                            //添加考生的信息
			Stu.Insert();
			cout << endl << "插入后结果如下：" << endl;
			Stu.PrintList();
		}
		else if (choice == 4) {                    //修改考生信息
			Stu.Modify();
			Stu.PrintList();
		}
		else if (choice == 5) {                             //用于删除指定的考生信息
			int c = 0;
			int num = 0;
			string name = "";
			PutIn("按学号查找考生并删除选择1，按姓名查找考生并删除请按2：", NONEEDPAUSE, c, 1, 2);
			switch (c) {
				case 1:
					PutIn("请输入要删除的考生的学号：", NONEEDPAUSE, num);
					Stu.Remove(num);
					Stu.PrintList();
					break;
				case 2:
					PutIn("请输入要删除的考生的姓名：", NONEEDPAUSE, name);
					Stu.Remove(name);
					Stu.PrintList();
					break;
				default:
					break;
			}
		}
		else if (choice == 6) {
			break;
		}
		else if (choice == 0) {
			cout << endl;
			menu();
		}
		cout << endl;
	}
	return 0;
}