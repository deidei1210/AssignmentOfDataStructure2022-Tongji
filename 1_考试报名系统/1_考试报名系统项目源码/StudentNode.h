#pragma once
#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

class StudentList;

//学生链表中间的节点
class StudentNode {
	friend class StudentList;
private:
	int num;                 //报考学生的学号
	string name;             //报考学生的姓名
	string sex;              //报考学生的性别
	int age;                 //报考学生的年龄
	string sort;             //报考学生的报考类别
	StudentNode* next;       //指向下一个节点
public:
	StudentNode();                                                      //链表节点缺省构造函数
	StudentNode(int n, string Name, string Sex, int Age, string Sort);   //用数据的大小初始化节点
	StudentNode* NextNode();                                            //返回下一个节点的地址
	StudentNode* GetNode(int n, string Name, string Sex, int Age, string Sort, StudentNode* Next = NULL);//创建数据为上述数据，指针为Next的新节点
	void InsertAfter(StudentNode* p);                                  //在当前节点后插入节点p
	StudentNode* RemoveAfter();                                        //删除下一个节点
	void PrintNode();                                                   //打印节点信息
	void ModifyNode();                                                  //修改这个节点的制定一个内容
};

