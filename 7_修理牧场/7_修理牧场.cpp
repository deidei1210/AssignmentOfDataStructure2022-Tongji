#include<iostream>
#include<queue>
using namespace std;

//写一个链式优先队列，来模仿哈夫曼树的算法
struct Node {
	int data = 0;        //这一个节点中存放的数据
	Node* pre = NULL;  //连接前面一个节点
	Node* next = NULL; //连接后面一个节点
};
//链式优先队列类的定义
//该优先队列需要做到队列内的元素都是按照数值从小到大排列的
//但是每次都只能访问头结点
class PriorityQueue {
private:
	Node* head = NULL;    //头指针
	Node* tail = NULL;    //尾指针
	int s = 0;            //储存队列中节点的数量，即一共有多少个元素
public:
	PriorityQueue() :head(NULL), tail(NULL), s(0) {};              //缺省初始化
	~PriorityQueue();                                        //析构函数
	void push(int ele);      //将一个新元素塞入队尾
	int front();             //取队列头部的元素
	int pop();               //将头部元素弹出并且返回其值
	int size();              //返回队列中储存元素的个数
};
//将一个新元素放入优先队列中，需要先从头到尾找到一个位置，使得前面的元素都比他小，后面的元素都比他大
void PriorityQueue::push(int ele) {
	//先创建这个新节点
	Node* node = new Node;
	node->data = ele;     //赋值
	node->pre = NULL;
	node->next = NULL;
	//如果此时队列是空的
	if (head == NULL) {
		head = node;    //那这个新加上来的节点就是头结点
		tail = node;
	}
	else {          //否则在队列中找到一个位置，使得前面的节点元素值都比他小，后面节点元素值都比他大
		Node* p=head;
		while (p != NULL) {
			//比较p处的值和ele的大小，如果比ele小那就继续往后
			if (p->data <= ele) {
				p = p->next;
				continue;
			}
			else {    //否则一旦找到比他大的节点，那就将node插在他前面
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
		//如果说前面都没有插入，那就插入到尾巴上，说明他比别的都小
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

PriorityQueue q;      //用于存储每段木头的长度的长度，并按照从小到大的顺序排好队，依次出队
int n = 0;            //用于存储需要的木头的总段数
int len=0;            //每一块木头的长度
int cost = 0;          //总的最小花费
char ch = 0;          //用于控制是否需要下一轮测试
//输入需要的值
void PutIn() {
	while (1) {
		cout << "请输入需要切的块数:" << endl;
		cin >> n;
		if (n <= 1) {
			cout << "块数太少不需要切！请重新输入需要切的块数！" << endl;
			continue;
		}
		else
			break;
	}
	cout << "请输入每一块需要切成的长度!" << endl;
	for (int i = 0; i < n; i++) {
		cin >> len;
		q.push(len);
	}
}
//计算花费最小值
void Caculate() {
	while (q.size() > 1) {
		//找到两个最小的
		int a = q.front();
		q.pop();
		int b = q.front();
		q.pop();
		q.push(a + b);
		cost += (a + b);
	}
}
//用于询问是否继续
int ToContinue(){
	cout << endl << "是否需要继续切木块？(Y/N)";
	while (1) {
		cin >> ch;
		if (ch != 'Y' && ch != 'N') {
			cout << "输入错误，请重新输入！" << endl;
			continue;
		}
		break;
	}
	if (ch == 'Y') {
		q.pop(); //清空最后剩下的节点，准备下一轮测试
		cost = 0; //清空cost，准备下一轮测试
		ch = 0;  //清空用于选择的变量ch
		return 1;
	}
	else {
		return 0;
	}

}
int main()
{
	while (1) {
		PutIn();      //输入需要切的块数以及每一块的长度
		Caculate();  //用于计算最小开销
		cout << cost << endl;  //输出结果
		if (ToContinue()) {   //询问是否继续下一轮
			continue;
		}
		else
			break;
	}

    return 0;
}