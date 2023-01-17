#include<iostream>
#include<string>
#include<iomanip>
#include "StudentNode.h"
#include "StudentList.h"
using namespace std;


StudentList::StudentList() {
	//��ͷָ��ָ��ͷ��㣬βָ��ָ��β���
	phead = new(nothrow)StudentNode;//����ͷ
	plast = new(nothrow)StudentNode;//���һ���ڵ�
	if (phead == NULL||plast==NULL) {
		cout << "�ڴ�����ʧ��!" << endl;
		exit(0);
	}
	phead = plast;//��ͷ����β�������
	plast->next = NULL;//��β����next��Ϊ��ָ��
	lengh = 0;//������

}
//��һ���ڵ�����ʼ������
StudentList::StudentList(StudentNode* p) {
	//��ͷָ��ָ��ͷ��㣬βָ��ָ��β���
	phead = new(nothrow)StudentNode;//����ͷ
	plast = new(nothrow)StudentNode;//���һ���ڵ�
	if (phead == NULL || plast == NULL) {
		cout << "�ڴ�����ʧ�ܣ�" << endl;
		exit(0);
	}
	phead->next = p;//��ͷ�����¼ӽ����Ľڵ�����
	plast = p;
	p->next = NULL;
	lengh = 1;//������

}
//�ÿ�����
void StudentList::MakeEmpty() {
	StudentNode* q;
	while (phead->next != NULL) {
		q = phead->next;
		phead->next = q->next;
		delete q;
	}
	//���һ���Ǳ�βָ��lastҲ�ᱻ�ͷţ�����Ҫ��lastָ��ָ��head
	plast = phead;
	return;
}
//��������
int StudentList::Lengh()const {
	StudentNode* p;
	p = phead->next;//�Ƚ�ָ��ָ���һ���ڵ�
	int c = 0;//������ָ��һ���������˶���
	while (p != NULL) {
		p = p->next;
		c++;
	}
	return c;
}
//����ѧ���Ŀ���������ѧ������Ϣ
StudentNode* StudentList::Find(int num) {
	StudentNode* p;
	p = phead->next;
	int flag = 0;//������¼�Ƿ��Ѿ��ҵ������ѧ��������ҵ��˾���1�����û���ҵ�����0
	while (p != NULL) {
		if (p->num == num) {//˵���Ѿ��ҵ���
			return p;
		}
		else {
			p = p->next;//������һ��
		}
	}
	cout << "δ���ҵ�ѧ��Ϊ" << num << "��ѧ��!" << endl;
	//���������������������û���ҵ����Ǿͷ��ؿ�ָ��
	return NULL;
}
//����ѧ��������������ѧ������Ϣ
StudentNode* StudentList::Find(string name) {
	StudentNode* p;
	p = phead->next;
	int flag = 0;//������¼�Ƿ��Ѿ��ҵ������ѧ��������ҵ��˾���1�����û���ҵ�����0
	while (p != NULL) {
		if (p->name == name) {//˵���Ѿ��ҵ���
			return p;
		}
		else {
			p = p->next;//������һ��
		}
	}
	//���������������������û���ҵ����Ǿͷ��ؿ�ָ��
	cout << "û���ҵ����ֽ�" << name << "��ѧ����" << endl;
	return NULL;
}
//���ڴ�ӡ������Ϣ
void StudentList::PrintList() {
	//�ȴ�ӡ����
	cout << "����    ����    �Ա�    ����    �������" << endl;
	StudentNode* p;
	p = phead->next;
	while (p != NULL) {
		p->PrintNode();//�ȴ�ӡ��һ���ڵ����Ϣ��һ��
		p = p->next;//Ȼ��ָ���Ƶ���һ���ڵ�
	}
	return;
}
//�ڵ�i������p
int StudentList::Insert() {
	cout << "��������Ҫ����Ŀ�����λ��:";
	int n = 0;
	//һֱ���룬ֱ���õ���Ч����
	while (1) {
		cin >> n;//�����λ��
		if (n <= 0 || n > lengh + 1) {
			cout << endl << "������Ч���ȣ�����������!" << endl;
			continue;
		}
		break;
	}
	//�ҵ���n-1���ڵ㣬��Ϊ��n-1���ڵ�������n,������Ҫ����ĵط�
	StudentNode* p = Get(n-1);
	if (p == NULL) {
		return 0;
	}
	cout << "����������Ҫ����Ŀ����Ŀ��ţ��������Ա����估�������!" << endl;
	StudentNode* node = new(nothrow)StudentNode;
	if (node == NULL) {
		cout << "ָ���ڴ����ʧ��!" << endl;
		return 0;
	}
	cin >> node->num >> node->name >> node->sex >> node->age >> node->sort;
	//Ȼ������ڵ�嵽����
	node->next = p->next;
	p->next = node;
	lengh++;
	return 1;
}
//ժ��ѧ��Ϊnum��ѧ������Ϣ�ڵ�
int StudentList::Remove(int num) {
	StudentNode* pre,*p;//preʼ��ָ��pǰ����һ���ڵ㣬pȥѰ��ѧ��Ϊnum�Ľڵ�
	pre = phead;
	p = phead->next;
	while (p!= NULL&&p->num!=num) {
		p = p->next;
		pre = pre->next;
	}
	if (p == NULL) {
		cout << "û���ҵ�ѧ��Ϊ" << num << "�Ŀ�����" << endl;
		return 0;
	}
	cout << "��ɾ����ѧ����ϢΪ:"; p->PrintNode(); cout << endl;
	//���p�ҵ���ѧ����num�Ľڵ㣬��ô�ͽ���ɾ��
	pre->next = p->next;
	delete p;
	return 1;
}
//ժ������Ϊname��ѧ������Ϣ�ڵ�
int StudentList::Remove(string name) {
	StudentNode* pre, * p;//preʼ��ָ��pǰ����һ���ڵ㣬pȥѰ��ѧ��Ϊnum�Ľڵ�
	pre = phead;
	p = phead->next;
	while (p != NULL && p->name != name) {
		p = p->next;
		pre = pre->next;
	}
	if (p == NULL) {
		cout << "û���ҵ�����Ϊ" << name << "�Ŀ�����" << endl;
		return 0;
	}
	cout << "��ɾ����ѧ����ϢΪ:"; p->PrintNode(); cout << endl;
	//���p�ҵ���������name�Ľڵ㣬��ô�ͽ���ɾ��
	pre->next = p->next;
	delete p;
	return 1;
}

//�õ���i���Ľڵ��ַ
StudentNode* StudentList::Get(int i) {
	if (i < 0||i>lengh)return NULL;
	if (i == 0)return phead;
	//ʣ�µ�˵�������Ƿ��������߼���
	StudentNode* p = phead->next;//Ĭ��0�Ǳ�ͷ��1�ǵ�һ��ѧ��
	int count = 1;
	while (p != NULL && count < i) {
		p = p->next;
		count++;
	}
	return p;
}
//��������
StudentList::~StudentList() {
	MakeEmpty();
	delete phead;
}
//����n��ѧ�����ݣ�����n���½ڵ�
void StudentList::CreateList(int n) {
	StudentNode* p = phead;
	StudentNode* q;
	//��ָ���Ƶ�β��
	while (p->next != NULL) {
		p = p->next;
	}

	cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
	while (n--) {
		p->next = new(nothrow)StudentNode;
		if (p->next == NULL) {
			cout << "�ڴ����ʧ��!" << endl;
			return;
		}
		q = p->next;
		cin >> q->num >> q->name >> q->sex >>q->age >> q->sort;
		q->next = NULL;
		p = q;
		lengh++;
	}
	return;
}
//�����޸������е�i���ڵ��ĳһ������
void StudentList::Modify() {
	cout << "��������Ҫ�޸ĵڼ����ڵ㣺";
	int n = 0;//��ʾ��Ҫ�޸ĵĽڵ�
	//cout << lengh << endl;
	while (1) {
		cin >> n;
		if (n <= 0 || n > lengh) {
			cout << "����Ľڵ�����������Χ�ڣ�" << endl;
			continue;
		}
		break;
	}
	StudentNode* p = Get(n);//��pȥ�ҵ���n���ڵ�
	p->ModifyNode();
}

