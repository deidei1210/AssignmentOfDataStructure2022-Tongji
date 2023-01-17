#include<iostream>
#include<string>
#include<iomanip>
#include "StudentNode.h"
#include "StudentList.h"
using namespace std;
const int N = 7;//用于设置打印的时候两个信息之间的空格

//缺省初始化
StudentNode::StudentNode() {
	num = 0;
	name = "";
	sex = "";
	age = 0;
	sort = "";
	next = NULL;
}
//用别的数据初始化
StudentNode::StudentNode(int n, string Name, string Sex, int Age, string Sort) {
	num = n;
	name = Name;
	sex = Sex;
	age = Age;
	sort = Sort;
	next = NULL;
}
//返回下一个节点的地址
StudentNode* StudentNode::NextNode() {
	return next;
}
//创建数据为上述数据，指针为Next的新节点
StudentNode* StudentNode::GetNode(int n, string Name, string Sex, int Age, string Sort, StudentNode* Next) {
	//创建一个新节点并分配内存
	StudentNode* newnode = new(nothrow) StudentNode;
	if (newnode == NULL) {
		return NULL;
	}
	newnode->num = n;
	newnode->name = Name;
	newnode->sex = Sex;
	newnode->age = Age;
	newnode->sort = Sort;
	newnode->next = Next;
	return newnode;
}
//在当前节点后插入节点p
void StudentNode::InsertAfter(StudentNode* p) {
	p->next = next;//先让要插入的节点指向当前节点的下一个节点
	next = p;//然后让当前节点指向插入的节点
}
//摘下当前节点的下一个节点
StudentNode* StudentNode::RemoveAfter() {
	if (next == NULL) {
		return NULL;
	}
	next = next->next;
	return next;
}
//打印节点信息
void StudentNode::PrintNode() {
	cout << num << "       "<< name
		<< "       "<< sex << "       " << age
		<< "       "<< sort << endl;
	return;
}
//修改节点指定内容的信息
void StudentNode::ModifyNode() {
	cout << "请输入修改后的节点内容：";
	cin >> num >> name >> sex >> age >> sort;
}
