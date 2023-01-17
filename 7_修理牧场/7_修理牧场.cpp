#include<iostream>
#include<queue>
using namespace std;

//дһ����ʽ���ȶ��У���ģ�¹����������㷨
struct Node {
	int data = 0;        //��һ���ڵ��д�ŵ�����
	Node* pre = NULL;  //����ǰ��һ���ڵ�
	Node* next = NULL; //���Ӻ���һ���ڵ�
};
//��ʽ���ȶ�����Ķ���
//�����ȶ�����Ҫ���������ڵ�Ԫ�ض��ǰ�����ֵ��С�������е�
//����ÿ�ζ�ֻ�ܷ���ͷ���
class PriorityQueue {
private:
	Node* head = NULL;    //ͷָ��
	Node* tail = NULL;    //βָ��
	int s = 0;            //��������нڵ����������һ���ж��ٸ�Ԫ��
public:
	PriorityQueue() :head(NULL), tail(NULL), s(0) {};              //ȱʡ��ʼ��
	~PriorityQueue();                                        //��������
	void push(int ele);      //��һ����Ԫ�������β
	int front();             //ȡ����ͷ����Ԫ��
	int pop();               //��ͷ��Ԫ�ص������ҷ�����ֵ
	int size();              //���ض����д���Ԫ�صĸ���
};
//��һ����Ԫ�ط������ȶ����У���Ҫ�ȴ�ͷ��β�ҵ�һ��λ�ã�ʹ��ǰ���Ԫ�ض�����С�������Ԫ�ض�������
void PriorityQueue::push(int ele) {
	//�ȴ�������½ڵ�
	Node* node = new Node;
	node->data = ele;     //��ֵ
	node->pre = NULL;
	node->next = NULL;
	//�����ʱ�����ǿյ�
	if (head == NULL) {
		head = node;    //������¼������Ľڵ����ͷ���
		tail = node;
	}
	else {          //�����ڶ������ҵ�һ��λ�ã�ʹ��ǰ��Ľڵ�Ԫ��ֵ������С������ڵ�Ԫ��ֵ��������
		Node* p=head;
		while (p != NULL) {
			//�Ƚ�p����ֵ��ele�Ĵ�С�������eleС�Ǿͼ�������
			if (p->data <= ele) {
				p = p->next;
				continue;
			}
			else {    //����һ���ҵ�������Ľڵ㣬�Ǿͽ�node������ǰ��
				Node* q = p->pre;
				p->pre = node;
				node->next = p;
				if (p != head) {
					node->pre = q;
					q->next = node;
				}
				if (p == head) {
					head = node;
				}
				break;
			}
		}
		//���˵ǰ�涼û�в��룬�ǾͲ��뵽β���ϣ�˵�����ȱ�Ķ�С
		if (tail->data <= ele) {
			tail->next = node;
			node->pre = tail;
			tail = node;
		}
	}
	s++;
}
int PriorityQueue::front() {
	if (head == NULL) {
		return -1;
	}
	else {
		return head->data;
	}
}
int PriorityQueue::pop() {
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
int PriorityQueue::size() {
	return s;
}
PriorityQueue::~PriorityQueue() {
	Node* p;
	while (head != NULL) {
		p = head;
		head = head->next;
		delete head;
	}
}

PriorityQueue q;      //���ڴ洢ÿ��ľͷ�ĳ��ȵĳ��ȣ������մ�С�����˳���źöӣ����γ���
int n = 0;            //���ڴ洢��Ҫ��ľͷ���ܶ���
int len=0;            //ÿһ��ľͷ�ĳ���
int cost = 0;          //�ܵ���С����
char ch = 0;          //���ڿ����Ƿ���Ҫ��һ�ֲ���
//������Ҫ��ֵ
void PutIn() {
	while (1) {
		cout << "��������Ҫ�еĿ���:" << endl;
		cin >> n;
		if (n <= 1) {
			cout << "����̫�ٲ���Ҫ�У�������������Ҫ�еĿ�����" << endl;
			continue;
		}
		else
			break;
	}
	cout << "������ÿһ����Ҫ�гɵĳ���!" << endl;
	for (int i = 0; i < n; i++) {
		cin >> len;
		q.push(len);
	}
}
//���㻨����Сֵ
void Caculate() {
	while (q.size() > 1) {
		//�ҵ�������С��
		int a = q.front();
		q.pop();
		int b = q.front();
		q.pop();
		q.push(a + b);
		cost += (a + b);
	}
}
//����ѯ���Ƿ����
int ToContinue(){
	cout << endl << "�Ƿ���Ҫ������ľ�飿(Y/N)";
	while (1) {
		cin >> ch;
		if (ch != 'Y' && ch != 'N') {
			cout << "����������������룡" << endl;
			continue;
		}
		break;
	}
	if (ch == 'Y') {
		q.pop(); //������ʣ�µĽڵ㣬׼����һ�ֲ���
		cost = 0; //���cost��׼����һ�ֲ���
		ch = 0;  //�������ѡ��ı���ch
		return 1;
	}
	else {
		return 0;
	}

}
int main()
{
	while (1) {
		PutIn();      //������Ҫ�еĿ����Լ�ÿһ��ĳ���
		Caculate();  //���ڼ�����С����
		cout << cost << endl;  //������
		if (ToContinue()) {   //ѯ���Ƿ������һ��
			continue;
		}
		else
			break;
	}

    return 0;
}