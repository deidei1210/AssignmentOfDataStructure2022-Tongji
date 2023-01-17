#pragma once
#include<iostream>
#include<string>
#include "StudentNode.h"
using namespace std;

//����
class StudentList {
private:
	StudentNode* phead;//�����ͷ���ָ��
	StudentNode* plast;//�����β�ڵ�ָ��
	int lengh = 0;//����ĳ���

public:
	StudentList();
	StudentList(StudentNode* p);//��һ���ڵ�����ʼ������
	void CreateList(int n);//��ʾͨ�����봴��һ������Ϊn������
	void MakeEmpty();//�������ÿ�
	int Lengh()const;//������ĳ���
	StudentNode* Find(int num);//���ݿ�����ѧ��������ѧ������Ϣ
	StudentNode* Find(string name);//���ݿ���������������ѧ������Ϣ
	void PrintList();//���ڴ�ӡ������Ϣ
	int Insert();//������i������ڵ�p
	int Remove(int num);//ɾȥѧ��Ϊnum��ѧ������Ϣ
	int Remove(string name);//ɾȥ����Ϊname��ѧ������Ϣ
	StudentNode* Get(int i);//�õ�i���Ľڵ�
	void Modify();//�����޸������е�һ���ڵ��е�ĳ������
	~StudentList();
};

