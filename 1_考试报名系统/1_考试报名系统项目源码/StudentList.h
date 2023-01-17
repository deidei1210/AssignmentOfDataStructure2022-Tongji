#pragma once
#include<iostream>
#include<string>
#include "StudentNode.h"
using namespace std;

//链表
class StudentList {
private:
	StudentNode* phead;//链表的头结点指针
	StudentNode* plast;//链表的尾节点指针
	int lengh = 0;//链表的长度

public:
	StudentList();
	StudentList(StudentNode* p);//用一个节点来初始化链表
	void CreateList(int n);//表示通过输入创建一个长度为n的链表
	void MakeEmpty();//将链表置空
	int Lengh()const;//求链表的长度
	StudentNode* Find(int num);//根据考生的学号来查找学生的信息
	StudentNode* Find(string name);//根据考生的姓名来查找学生的信息
	void PrintList();//用于打印链表信息
	int Insert();//用于在i处插入节点p
	int Remove(int num);//删去学号为num的学生的信息
	int Remove(string name);//删去姓名为name的学生的信息
	StudentNode* Get(int i);//得到i处的节点
	void Modify();//用于修改链表中的一个节点中的某个内容
	~StudentList();
};

