#include<iostream>
#include<string>
#include<iomanip>
#include "StudentNode.h"
#include "StudentList.h"
using namespace std;


StudentList::StudentList() {
	//让头指针指向头结点，尾指针指向尾结点
	phead = new(nothrow)StudentNode;//链表头
	plast = new(nothrow)StudentNode;//最后一个节点
	if (phead == NULL||plast==NULL) {
		cout << "内存申请失败!" << endl;
		exit(0);
	}
	phead = plast;//将头结点和尾结点连接
	plast->next = NULL;//将尾结点的next设为空指针
	lengh = 0;//链表长度

}
//用一个节点来初始化链表
StudentList::StudentList(StudentNode* p) {
	//让头指针指向头结点，尾指针指向尾结点
	phead = new(nothrow)StudentNode;//链表头
	plast = new(nothrow)StudentNode;//最后一个节点
	if (phead == NULL || plast == NULL) {
		cout << "内存申请失败！" << endl;
		exit(0);
	}
	phead->next = p;//将头结点和新加进来的节点连接
	plast = p;
	p->next = NULL;
	lengh = 1;//链表长度

}
//置空链表
void StudentList::MakeEmpty() {
	StudentNode* q;
	while (phead->next != NULL) {
		q = phead->next;
		phead->next = q->next;
		delete q;
	}
	//最后一定是表尾指针last也会被释放，所以要将last指针指回head
	plast = phead;
	return;
}
//求链表长度
int StudentList::Lengh()const {
	StudentNode* p;
	p = phead->next;//先将指针指向第一个节点
	int c = 0;//用于数指针一共往后移了多少
	while (p != NULL) {
		p = p->next;
		c++;
	}
	return c;
}
//根据学生的考号来搜索学生的信息
StudentNode* StudentList::Find(int num) {
	StudentNode* p;
	p = phead->next;
	int flag = 0;//用来记录是否已经找到了这个学生，如果找到了就是1，如果没有找到就是0
	while (p != NULL) {
		if (p->num == num) {//说明已经找到了
			return p;
		}
		else {
			p = p->next;//往后移一格
		}
	}
	cout << "未能找到学号为" << num << "的学生!" << endl;
	//如果遍历完了整个链表都还没有找到，那就返回空指针
	return NULL;
}
//根据学生的姓名来搜索学生的信息
StudentNode* StudentList::Find(string name) {
	StudentNode* p;
	p = phead->next;
	int flag = 0;//用来记录是否已经找到了这个学生，如果找到了就是1，如果没有找到就是0
	while (p != NULL) {
		if (p->name == name) {//说明已经找到了
			return p;
		}
		else {
			p = p->next;//往后移一格
		}
	}
	//如果遍历完了整个链表都还没有找到，那就返回空指针
	cout << "没有找到名字叫" << name << "的学生！" << endl;
	return NULL;
}
//用于打印链表信息
void StudentList::PrintList() {
	//先打印标题
	cout << "考号    姓名    性别    年龄    报考类别" << endl;
	StudentNode* p;
	p = phead->next;
	while (p != NULL) {
		p->PrintNode();//先打印这一个节点的信息打一行
		p = p->next;//然后将指针移到下一个节点
	}
	return;
}
//在第i处增加p
int StudentList::Insert() {
	cout << "请输入你要插入的考生的位置:";
	int n = 0;
	//一直输入，直到得到有效输入
	while (1) {
		cin >> n;//插入的位置
		if (n <= 0 || n > lengh + 1) {
			cout << endl << "不是有效长度，请重新输入!" << endl;
			continue;
		}
		break;
	}
	//找到第n-1个节点，因为第n-1个节点后面就是n,就是需要插入的地方
	StudentNode* p = Get(n-1);
	if (p == NULL) {
		return 0;
	}
	cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别!" << endl;
	StudentNode* node = new(nothrow)StudentNode;
	if (node == NULL) {
		cout << "指针内存分配失败!" << endl;
		return 0;
	}
	cin >> node->num >> node->name >> node->sex >> node->age >> node->sort;
	//然后将这个节点插到后面
	node->next = p->next;
	p->next = node;
	lengh++;
	return 1;
}
//摘下学号为num的学生的信息节点
int StudentList::Remove(int num) {
	StudentNode* pre,*p;//pre始终指向p前面那一个节点，p去寻找学号为num的节点
	pre = phead;
	p = phead->next;
	while (p!= NULL&&p->num!=num) {
		p = p->next;
		pre = pre->next;
	}
	if (p == NULL) {
		cout << "没有找到学号为" << num << "的考生！" << endl;
		return 0;
	}
	cout << "您删除的学生信息为:"; p->PrintNode(); cout << endl;
	//如果p找到了学号是num的节点，那么就将它删除
	pre->next = p->next;
	delete p;
	return 1;
}
//摘下姓名为name的学生的信息节点
int StudentList::Remove(string name) {
	StudentNode* pre, * p;//pre始终指向p前面那一个节点，p去寻找学号为num的节点
	pre = phead;
	p = phead->next;
	while (p != NULL && p->name != name) {
		p = p->next;
		pre = pre->next;
	}
	if (p == NULL) {
		cout << "没有找到姓名为" << name << "的考生！" << endl;
		return 0;
	}
	cout << "您删除的学生信息为:"; p->PrintNode(); cout << endl;
	//如果p找到了姓名是name的节点，那么就将它删除
	pre->next = p->next;
	delete p;
	return 1;
}

//得到第i处的节点地址
StudentNode* StudentList::Get(int i) {
	if (i < 0||i>lengh)return NULL;
	if (i == 0)return phead;
	//剩下的说明输入是符合正常逻辑的
	StudentNode* p = phead->next;//默认0是表头，1是第一个学生
	int count = 1;
	while (p != NULL && count < i) {
		p = p->next;
		count++;
	}
	return p;
}
//析构函数
StudentList::~StudentList() {
	MakeEmpty();
	delete phead;
}
//输入n组学生数据，创建n个新节点
void StudentList::CreateList(int n) {
	StudentNode* p = phead;
	StudentNode* q;
	//将指针移到尾部
	while (p->next != NULL) {
		p = p->next;
	}

	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
	while (n--) {
		p->next = new(nothrow)StudentNode;
		if (p->next == NULL) {
			cout << "内存分配失败!" << endl;
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
//用于修改链表中第i个节点的某一个特性
void StudentList::Modify() {
	cout << "请输入想要修改第几个节点：";
	int n = 0;//表示想要修改的节点
	//cout << lengh << endl;
	while (1) {
		cin >> n;
		if (n <= 0 || n > lengh) {
			cout << "输入的节点数不在链表范围内！" << endl;
			continue;
		}
		break;
	}
	StudentNode* p = Get(n);//用p去找到第n个节点
	p->ModifyNode();
}

