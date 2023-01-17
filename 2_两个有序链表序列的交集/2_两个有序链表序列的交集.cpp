#include<iostream>

using namespace std;

//表示链表的一个节点
struct Node {
	int data;         //表示每一个节点存的数据
	Node* next;       //表示指向下一个节点的指针
};
//建立链表
Node* CreateList() {
	int n = 0;         //后面要用来输入的变量

	//ptr:可以随便在链表中移动的指针
	//head:链表的头指针
	//last:链表的尾指针
	Node* ptr = NULL, * head = new(nothrow)Node, * last;
	if (head == NULL ) {
		cout << "申请内存失败！" << endl;
		return NULL;
	}
	//初始化头结点和尾结点
	head->data = 0;
	head->next = NULL;
	last = head;//让尾结点先指向头结点
	
	//当n不等于-1的时候就一直输入，当输入到-1的时候，说明这条链表的输入已经停止了
	while (1) {
		cin >> n;
		if (n == -1) {
			break; //一旦输入的是-1，就直接退出
		}
		//给当前的指针分配内存空间，创建新的节点
		ptr = new(nothrow)Node;         
		if (ptr == NULL) {
			cout << "申请内存失败！" << endl;
			break;
		}

	    //给创建出来的这个新节点赋值
		ptr->data = n;                
		ptr->next = NULL;

		//然后将这个新的节点接在链表的后面
		last->next = ptr;
		last = ptr;
	}
	return head;
}

//用于寻找两个链表相同的部分，然后组成新的链表
Node* FindTheSame(Node* head1, Node* head2) {
	//新建一个链表用来存链表相同的部分
	Node* head = new(nothrow)Node,
		  *ptr1=head1,*ptr2=head2;     //新建两个指针用来遍历两个链表
	if (head == NULL) {
		cout << "申请内存失败！" << endl;
		exit(0);
	}
	head->data = 0;
	head->next = NULL;
	Node* ptr3 = head;                 //再新建一个指针指向新链表的头指针

	if (head == NULL) {
		cout << "申请内存失败！" << endl;
		return NULL;
	}
	//有任何一个是空链表就输出NULL
	if (head1->next == NULL || head2->next == NULL) {
		return head;
	}
	else {
		//先全部让指针指到第一个节点
		ptr1 = ptr1->next;
		ptr2 = ptr2->next;
		while (ptr1 != NULL && ptr2 != NULL) {
			if (ptr1->data == ptr2->data) {             //找到了相同的数据
				ptr3->next = new(nothrow)Node;          //给下一个新节点分配空间
				if (ptr3->next == NULL) {
					cout << "申请内存失败！" << endl;
					return NULL;
				}
				ptr3 = ptr3->next;                      //指向下一个新节点
				ptr3->data = ptr1->data;                //给新节点赋值
				ptr3->next = NULL;
				ptr1 = ptr1->next;                      //把指针都往后移一个
				ptr2 = ptr2->next;
			}
			else if (ptr1->data < ptr2->data) {          //如果两个节点的大小不相等，哪一个小就哪一个往后移
				ptr1 = ptr1->next;                     
			}
			else if (ptr1->data > ptr2->data) {
				ptr2 = ptr2->next;
			}
		}
	}
	return head;
}

//销毁链表，将链表中申请的空间全部释放
void MakeEmpty(Node* head) {
	Node* ptr = head->next,*p;
	while (ptr != NULL) {
		p = ptr->next;
		delete ptr;
		ptr = p;
	}
}

//输出链表内容
void Print(Node* head) {
	Node* ptr = NULL;
	if (head->next == NULL) {
		cout << "NULL" << endl;
	}
	else {
		ptr = head->next;
		while (ptr != NULL) {
			cout << ptr->data;
			ptr = ptr->next;
			if (ptr == NULL) {        //结尾不输出多余空格
				break;
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
}

int main()
{
	Node* head1 = NULL, * head2 = NULL, * head = NULL;
	char choice = 0;
	while (1) {
		cout << "请分别输入两个单调不减的链表，以-1结尾" << endl;
		head1 = CreateList();                       //建立链表1
		head2 = CreateList();                       //建立链表2
		head = FindTheSame(head1, head2);           //找到链表1和链表2中间的相同部分，并保存在链表中
		Print(head);                                //打印结果
		MakeEmpty(head1);                           //置空链表1
		MakeEmpty(head2);                           //置空链表2
		MakeEmpty(head);                            //置空链表
		choice = getchar();                         //吸收掉上面输入留下的回车
		cout <<"按回车键进行下一轮，输入0退出!";    //进行下一轮
		choice=getchar();
		if (choice == '/n') {
			continue;
		}
		else if(choice=='0'){
			break;
		}
		cout << endl;
	}

	delete head1;                                   
	delete head2;
	delete head;
	return 0;
}