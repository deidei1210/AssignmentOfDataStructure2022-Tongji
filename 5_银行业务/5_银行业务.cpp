#include<iostream>
#include<queue>
using namespace std;

int num = 0;    //表示顾客的总人数
//queue<int> A, B;   //一个队列用来放奇数，一个队列用来放偶数

//写一个链式队列
struct Node {
	int data=0;        //这一个节点中存放的数据
	Node* pre = NULL;  //连接前面一个节点
	Node* next = NULL; //连接后面一个节点
};
//链式类的定义
class Queue {
private:
	Node* head = NULL;    //头指针
	Node* tail = NULL;    //尾指针
	int s = 0;            //储存队列中节点的数量，即一共有多少个元素
public:
	Queue() :head(NULL), tail(NULL), s(0) {};              //缺省初始化
	~Queue();                                        //析构函数
	void push(int ele);      //将一个新元素塞入队尾
	int front();             //取队列头部的元素
	int pop();               //将头部元素弹出并且返回其值
	int size();              //返回队列中储存元素的个数
};
void Queue::push(int ele) {
	Node* node = new Node;
	node->data = ele;
	node->pre = NULL;
	node->next = NULL;
	//如果此时队列是空的
	if (head == NULL) {
		head = node;    //那这个新加上来的节点就是头结点
		tail = node;
	}
	else {          //否则直接插入队列的尾部
		tail->next = node;
		node->pre = tail;
		node->next = NULL;
		tail = node;
	}
	s++;
}
int Queue::front() {
	if (head == NULL) {
		return -1;
	}
	else {
		return head->data;
	}
}
int Queue::pop() {
	if (head == NULL) {
		return -1;
	}
	else {
		int a = head->data;
		Node* node = head;
		head = node->next;
		delete node;
		s--;
		return a;
	}
	return -1;
}
int Queue::size() {
	return s;
}
Queue::~Queue() {
	Node* p;
	while (head != NULL) {
		p = head;
		head = head->next;
		delete head;
	}
}

Queue A, B;   //一个队列用来放奇数，一个队列用来放偶数
//用于初始化的函数





void PutIn() {
	//先输入顾客的总人数
	cin >> num;
	int guest;    //用来承接用户的序号输入
	for (int i = 0; i < num; i++) {
		cin >> guest;
		//根据用户序号的奇偶放入不同的队列中
		if (guest % 2) {
			A.push(guest);
		}
		else {
			B.push(guest);
		}
	}
}
//输出业务完成顺序
void PrintOrder() {
	//先输出A，再输出B，并且每输出两个A，输出一个B
	int size_A = A.size(),size_B=B.size();   //先记下他们每一个队列中初始元素的个数，后面每输出一个就减一，直到全部输出为止
	while (size_A+size_B>1) {             //输出到只剩下最后一个没有输出，因为最后一个需要单独输出才可以保证最后没有空格
		for (int i = 0; (i < 2)&&(size_A != 0)&&(size_A + size_B > 1); i++) {
			cout << A.front() << " ";
			A.pop();
			size_A--;
		}
		if (size_B != 0&&(size_A + size_B > 1)) {
			cout << B.front() << " ";
			B.pop();
			size_B--;
		}
	}
	if (size_B == 1) {
		cout << B.front();
		B.pop();
		size_B--;
	}
	else if(size_A==1){
		cout << A.front();
		A.pop();
		size_A--;
	}
}
int main()
{
	PutIn();    //输入顾客总人数以及顾客的序号，并且根据序号的奇偶放入不同的队列
	PrintOrder();//输出办理的顺序
	system("pause");
	return 0;
}