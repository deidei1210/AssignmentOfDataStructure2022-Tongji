#include<iostream>
#include<string>
#include<iomanip>
#include "StudentNode.h"
#include "StudentList.h"
using namespace std;
const int N = 7;//�������ô�ӡ��ʱ��������Ϣ֮��Ŀո�

//ȱʡ��ʼ��
StudentNode::StudentNode() {
	num = 0;
	name = "";
	sex = "";
	age = 0;
	sort = "";
	next = NULL;
}
//�ñ�����ݳ�ʼ��
StudentNode::StudentNode(int n, string Name, string Sex, int Age, string Sort) {
	num = n;
	name = Name;
	sex = Sex;
	age = Age;
	sort = Sort;
	next = NULL;
}
//������һ���ڵ�ĵ�ַ
StudentNode* StudentNode::NextNode() {
	return next;
}
//��������Ϊ�������ݣ�ָ��ΪNext���½ڵ�
StudentNode* StudentNode::GetNode(int n, string Name, string Sex, int Age, string Sort, StudentNode* Next) {
	//����һ���½ڵ㲢�����ڴ�
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
//�ڵ�ǰ�ڵ�����ڵ�p
void StudentNode::InsertAfter(StudentNode* p) {
	p->next = next;//����Ҫ����Ľڵ�ָ��ǰ�ڵ����һ���ڵ�
	next = p;//Ȼ���õ�ǰ�ڵ�ָ�����Ľڵ�
}
//ժ�µ�ǰ�ڵ����һ���ڵ�
StudentNode* StudentNode::RemoveAfter() {
	if (next == NULL) {
		return NULL;
	}
	next = next->next;
	return next;
}
//��ӡ�ڵ���Ϣ
void StudentNode::PrintNode() {
	cout << num << "       "<< name
		<< "       "<< sex << "       " << age
		<< "       "<< sort << endl;
	return;
}
//�޸Ľڵ�ָ�����ݵ���Ϣ
void StudentNode::ModifyNode() {
	cout << "�������޸ĺ�Ľڵ����ݣ�";
	cin >> num >> name >> sex >> age >> sort;
}
