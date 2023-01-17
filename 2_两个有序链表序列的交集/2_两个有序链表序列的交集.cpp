#include<iostream>

using namespace std;

//��ʾ�����һ���ڵ�
struct Node {
	int data;         //��ʾÿһ���ڵ�������
	Node* next;       //��ʾָ����һ���ڵ��ָ��
};
//��������
Node* CreateList() {
	int n = 0;         //����Ҫ��������ı���

	//ptr:����������������ƶ���ָ��
	//head:�����ͷָ��
	//last:�����βָ��
	Node* ptr = NULL, * head = new(nothrow)Node, * last;
	if (head == NULL ) {
		cout << "�����ڴ�ʧ�ܣ�" << endl;
		return NULL;
	}
	//��ʼ��ͷ����β���
	head->data = 0;
	head->next = NULL;
	last = head;//��β�����ָ��ͷ���
	
	//��n������-1��ʱ���һֱ���룬�����뵽-1��ʱ��˵����������������Ѿ�ֹͣ��
	while (1) {
		cin >> n;
		if (n == -1) {
			break; //һ���������-1����ֱ���˳�
		}
		//����ǰ��ָ������ڴ�ռ䣬�����µĽڵ�
		ptr = new(nothrow)Node;         
		if (ptr == NULL) {
			cout << "�����ڴ�ʧ�ܣ�" << endl;
			break;
		}

	    //����������������½ڵ㸳ֵ
		ptr->data = n;                
		ptr->next = NULL;

		//Ȼ������µĽڵ��������ĺ���
		last->next = ptr;
		last = ptr;
	}
	return head;
}

//����Ѱ������������ͬ�Ĳ��֣�Ȼ������µ�����
Node* FindTheSame(Node* head1, Node* head2) {
	//�½�һ������������������ͬ�Ĳ���
	Node* head = new(nothrow)Node,
		  *ptr1=head1,*ptr2=head2;     //�½�����ָ������������������
	if (head == NULL) {
		cout << "�����ڴ�ʧ�ܣ�" << endl;
		exit(0);
	}
	head->data = 0;
	head->next = NULL;
	Node* ptr3 = head;                 //���½�һ��ָ��ָ���������ͷָ��

	if (head == NULL) {
		cout << "�����ڴ�ʧ�ܣ�" << endl;
		return NULL;
	}
	//���κ�һ���ǿ���������NULL
	if (head1->next == NULL || head2->next == NULL) {
		return head;
	}
	else {
		//��ȫ����ָ��ָ����һ���ڵ�
		ptr1 = ptr1->next;
		ptr2 = ptr2->next;
		while (ptr1 != NULL && ptr2 != NULL) {
			if (ptr1->data == ptr2->data) {             //�ҵ�����ͬ������
				ptr3->next = new(nothrow)Node;          //����һ���½ڵ����ռ�
				if (ptr3->next == NULL) {
					cout << "�����ڴ�ʧ�ܣ�" << endl;
					return NULL;
				}
				ptr3 = ptr3->next;                      //ָ����һ���½ڵ�
				ptr3->data = ptr1->data;                //���½ڵ㸳ֵ
				ptr3->next = NULL;
				ptr1 = ptr1->next;                      //��ָ�붼������һ��
				ptr2 = ptr2->next;
			}
			else if (ptr1->data < ptr2->data) {          //��������ڵ�Ĵ�С����ȣ���һ��С����һ��������
				ptr1 = ptr1->next;                     
			}
			else if (ptr1->data > ptr2->data) {
				ptr2 = ptr2->next;
			}
		}
	}
	return head;
}

//��������������������Ŀռ�ȫ���ͷ�
void MakeEmpty(Node* head) {
	Node* ptr = head->next,*p;
	while (ptr != NULL) {
		p = ptr->next;
		delete ptr;
		ptr = p;
	}
}

//�����������
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
			if (ptr == NULL) {        //��β���������ո�
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
		cout << "��ֱ�������������������������-1��β" << endl;
		head1 = CreateList();                       //��������1
		head2 = CreateList();                       //��������2
		head = FindTheSame(head1, head2);           //�ҵ�����1������2�м����ͬ���֣���������������
		Print(head);                                //��ӡ���
		MakeEmpty(head1);                           //�ÿ�����1
		MakeEmpty(head2);                           //�ÿ�����2
		MakeEmpty(head);                            //�ÿ�����
		choice = getchar();                         //���յ������������µĻس�
		cout <<"���س���������һ�֣�����0�˳�!";    //������һ��
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