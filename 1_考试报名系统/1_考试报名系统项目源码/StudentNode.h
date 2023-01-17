#pragma once
#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

class StudentList;

//ѧ�������м�Ľڵ�
class StudentNode {
	friend class StudentList;
private:
	int num;                 //����ѧ����ѧ��
	string name;             //����ѧ��������
	string sex;              //����ѧ�����Ա�
	int age;                 //����ѧ��������
	string sort;             //����ѧ���ı������
	StudentNode* next;       //ָ����һ���ڵ�
public:
	StudentNode();                                                      //����ڵ�ȱʡ���캯��
	StudentNode(int n, string Name, string Sex, int Age, string Sort);   //�����ݵĴ�С��ʼ���ڵ�
	StudentNode* NextNode();                                            //������һ���ڵ�ĵ�ַ
	StudentNode* GetNode(int n, string Name, string Sex, int Age, string Sort, StudentNode* Next = NULL);//��������Ϊ�������ݣ�ָ��ΪNext���½ڵ�
	void InsertAfter(StudentNode* p);                                  //�ڵ�ǰ�ڵ�����ڵ�p
	StudentNode* RemoveAfter();                                        //ɾ����һ���ڵ�
	void PrintNode();                                                   //��ӡ�ڵ���Ϣ
	void ModifyNode();                                                  //�޸�����ڵ���ƶ�һ������
};

