#include<iostream>
#include<queue>
using namespace std;

int num = 0;    //��ʾ�˿͵�������
//queue<int> A, B;   //һ������������������һ������������ż��

//дһ����ʽ����
struct Node {
	int data=0;        //��һ���ڵ��д�ŵ�����
	Node* pre = NULL;  //����ǰ��һ���ڵ�
	Node* next = NULL; //���Ӻ���һ���ڵ�
};
//��ʽ��Ķ���
class Queue {
private:
	Node* head = NULL;    //ͷָ��
	Node* tail = NULL;    //βָ��
	int s = 0;            //��������нڵ����������һ���ж��ٸ�Ԫ��
public:
	Queue() :head(NULL), tail(NULL), s(0) {};              //ȱʡ��ʼ��
	~Queue();                                        //��������
	void push(int ele);      //��һ����Ԫ�������β
	int front();             //ȡ����ͷ����Ԫ��
	int pop();               //��ͷ��Ԫ�ص������ҷ�����ֵ
	int size();              //���ض����д���Ԫ�صĸ���
};
void Queue::push(int ele) {
	Node* node = new Node;
	node->data = ele;
	node->pre = NULL;
	node->next = NULL;
	//�����ʱ�����ǿյ�
	if (head == NULL) {
		head = node;    //������¼������Ľڵ����ͷ���
		tail = node;
	}
	else {          //����ֱ�Ӳ�����е�β��
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

Queue A, B;   //һ������������������һ������������ż��
//���ڳ�ʼ���ĺ���





void PutIn() {
	//������˿͵�������
	cin >> num;
	int guest;    //�����н��û����������
	for (int i = 0; i < num; i++) {
		cin >> guest;
		//�����û���ŵ���ż���벻ͬ�Ķ�����
		if (guest % 2) {
			A.push(guest);
		}
		else {
			B.push(guest);
		}
	}
}
//���ҵ�����˳��
void PrintOrder() {
	//�����A�������B������ÿ�������A�����һ��B
	int size_A = A.size(),size_B=B.size();   //�ȼ�������ÿһ�������г�ʼԪ�صĸ���������ÿ���һ���ͼ�һ��ֱ��ȫ�����Ϊֹ
	while (size_A+size_B>1) {             //�����ֻʣ�����һ��û���������Ϊ���һ����Ҫ��������ſ��Ա�֤���û�пո�
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
	PutIn();    //����˿��������Լ��˿͵���ţ����Ҹ�����ŵ���ż���벻ͬ�Ķ���
	PrintOrder();//��������˳��
	system("pause");
	return 0;
}