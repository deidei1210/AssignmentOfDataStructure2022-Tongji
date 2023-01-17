#define ISDIGIT   1                //������
#define ISOPERATOR 2               //�������
#define FROUNT 3                   //��ǰ����
#define BACK 4                     //�Ǻ�����

#include<iostream>
#include<sstream>                   //ʹ��getline
using namespace std;

//��ĿҪ�����֧�ֶ�λ���룬����֧��С�����룬���ֻ��һ��һ�����룬һ��һ���ж�

string Input;          //�����洢���������
string Item[21];       //������ű��ʽ�е���
int space = 0;      //��ʾItem���±꣬ͬʱҲ����ո������
int c = 0;        //���ڼ�����Ҫ������������
const char* front = "��";
const char* back = "��";

//�ڵ�
struct Node {
	char data;
	Node* next;   //ָ�������һ���ڵ�
	Node* pre;     //ָ����ǰ��һ���ڵ�
};
//дһ�������ջ����
class Stack {
private:
	Node* Top;         //ջ��ָ�룬ʼ��ָ��ջ��
	int s;
public:
	Stack();          //���캯����Ĭ�ϳ�ʼ��
	Stack(char ch); //���캯������һ��ջ��Ԫ�س�ʼ��
	void push(char ch);//��һ�����������ջ��      
	char pop();       //��������Ԫ�أ�������ֵ�Ĵ�С����
	char top();       //����ջ����Ԫ��
	int size();       //����ջ�Ĵ�С
	int empty();      //�ж�ջ�Ƿ�Ϊ�գ��վͷ���1���ǿշ���0
	void MakeEmpty(); //ʹջ��ɿյ�
	~Stack();         //��������
};
//������Stack�еĺ���
Stack::Stack() {
	Top = NULL;       //��ˣ�Top��Nullʱ��ʾ��ջ
	s = 0;
}
Stack::Stack(char ch) {
	Node* node = new Node;    //�����ڵ㣬ʹ���Ϊ��һ��Ԫ��
	node->data = ch;
	node->next = NULL;
	node->pre = NULL;
	Top = node;               //��Top���ڵ�һ���ڵ�
	s = 1;
	s++;
}
void Stack::push(char ch) {
	//���ȴ���һ���ڵ�
	Node* node = new Node;
	//���ڵ㸳ֵ
	node->data = ch;
	//������Ǹ���ջ���൱����һ��Ԫ�ظ�ջ��ʼ��
	if (Top == NULL) {
		Node* node = new Node;    //�����ڵ㣬ʹ���Ϊ��һ��Ԫ��
		node->data = ch;
		node->next = NULL;
		node->pre = NULL;
		Top = node;               //��Top���ڵ�һ���ڵ�
	}
	else {     //����ⲻ��һ����ջ����ôֻ��Ҫ����������Top����
		node->pre = Top;
		node->next = NULL;
		Top = node;
	}
	s++;
}
char Stack::pop() {
	//����ջ��Ԫ�أ������أ�Ȼ��ɾ������ڵ�
	//������ջ�ǿյ�
	if (Top == NULL) {
		return 0;
	}
	else {    //������ջ���ǿյ�
		char c = Top->data;         //�ݴ�ջ������
		Node* node = Top;           //��һ���ڵ����Top
		Top = Top->pre;             //��TopŲ��ǰһ��Ԫ��
		delete node;                //ɾ�������ڵ�
	}
	s--;
	return c;                       //���ض����ڵ������
}
char Stack::top(){
	if (Top == NULL) {
		return 0;
	}
	return Top->data;
}
int Stack::size() {
	return s;
}
int Stack::empty() {
	if (Top == NULL)
		return 1;
	return 0;
}
void Stack::MakeEmpty() {
	Node* node = Top;
	while (Top != NULL) {
		node = Top;
		Top = Top->pre;
		delete node;
	}
	s = 0;
}
Stack::~Stack() {
	Node* node = Top;
	while (Top != NULL) {
		node = Top;
		Top = Top->pre;
		delete node;
	}
}

Stack op;    //�����ջ

//���ڼ���Ƿ������������
int Check(int i) {

	if (Input[i]==front[0]|| Input[i] == front[1]|| Input[i] == back[0]|| Input[i] == back[1]) {
		return 0;
	}
}

//�������룬��û�������
void putin() {
	while (1) {
		//��������ո��һ����
		getline(cin, Input);             //getline���Զ���ո������س�������
		//���ڲ�����20���ַ�������Input�����19���ո������ڼ����ʱ��Ҫע��
		int len = Input.length();
		//��Item��ֵ��������볬��20������������
		int flag = 1;
		
		while (1) {
			for (int i = 0; i < len; i++) {
				if (Input[i] != ' ') {
					//����Ƿ������ķ��ţ�����У���������
					flag=Check(i);
					if (!flag) {
						cout << "�����ʽ�Ӻ������ķ��ţ���ر��������뷨,�������룡" << endl;
						break;
					}
					//û�����ķ��ţ��ͼ�������Item��
					Item[space] += Input[i];
					//��������󲻱������
					if (Input[i] == '(' || Input[i] == ')') {
						c++;
					}
				}
				else {
					space++;
					//˵�����볬��20���Ҫ��������
					if (space >= 20) {
						cout << "������ַ�����20������޶����������!" << endl;
						break;
					}
				}
			}
			break;
		}

		//���볬��20��Ԫ�أ������������ķ��ţ����֮ǰ�����룬��������
		if (space >= 20||!flag) {
			Input.clear();
			space = 0;
			for (int i = 0; i <= 19; i++) {
				Item[i].clear();
			}
		}
		else {
			break;
		}
	}
	//�������Ҫ�����Ԫ�ظ�������Ԫ�ظ�����ȥ���ŵĸ���
	c = space+1 - c;
}

//�����ж������Input�������������
int Judge(string& Input) {
	int len = Input.length();
	//���������ַ������ȴ���1����ôһ��������
	if (len > 1) {
		//�����һ���Ƿ���λ��Ҫ����һ��
		if (Input[0] == '+') {
			Input.erase(0, 1);                //����ǼӺţ��Ǿ�ɾ����һ���ַ�
		}
		return ISDIGIT;
	}
	else if(Input[0]>='0'&&Input[0]<='9'){ return ISDIGIT; }    //���ֻ��һ�����ȣ���������ַ���0��9֮�䣬��ô��������
	else if (Input[0] == '(') {return FROUNT;}
	else if (Input[0] == ')') {return BACK;}
	else {return ISOPERATOR;}
}

//���ڷ�������������ȼ�
int Priority(char operation) {
	switch (operation) {
		case '+':return 1;
		case '-':return 1;    //�Ӻźͼ�����ͬ���������
		case '*': return 2;
		case  '/': return 2;   //�˺źͳ�����ͬ���������
	}
}

//���ڰ���˳�������׺���ʽ
void postfix() {
	for (int i = 0; i <= space; i++) {
		int judge = Judge(Item[i]);
		//���ж���һ�������ֻ����ַ�
		if (judge == ISDIGIT) {       //�����һ��������
			if (space == 0)          //����ǵ�������֣���ôֻҪ������ֲ�Ҫ�ո�
				cout << Item[i];
			else
				cout << Item[i] << " ";      //����Ҫ����ո񣬷������һλһ���Ƿ���֮���
		}
		else if (judge == ISOPERATOR) {                  //�����һ���������+ - * /
			//���ջ�ǿյģ��Ǿ�ֱ����ջ������ջ��Ԫ����������
			if (op.empty() || op.top() == '(') {
				op.push(Item[i][0]);
			}
			else {        //���ջ���ǿյģ���ǰ�治�������ţ��Ǿͺ�ջ����Ԫ�رȽ����ȼ�
				//���ջ���ķ������ȼ����ڴ�ʱ�ķ��ţ���ô����ջ
				if (Priority(op.top()) < Priority(Item[i][0])) {
					op.push(Item[i][0]);
				}
				else {  //����Ļ�,��û��������������ջû�пյ�����£���һֱ�����ֱ���������ȼ�����͵����������֮��Ҫ��֤ջ����������ȼ����������״̬
					while (!op.empty() && op.top() != '(') {
						if (Priority(op.top()) > Priority(Item[i][0]) || Priority(op.top()) == Priority(Item[i][0])) {
							cout << op.top() << " ";
							op.pop();
						}
						else
							break;
					}
					op.push(Item[i][0]);
				}
			}
		}
		else if (judge == FROUNT) {                  //�����һ����ǰ���ţ��Ǿ�ֱ����ջ
			op.push(Item[i][0]);
		}
		else if (judge == BACK) {                     //�����һ���Ǻ����ţ��Ǿͽ�ǰ���ź�ķ���ȫ����������ҽ�ǰ���ŵ���
			while (op.top() != '(') {
				cout << op.top() << " ";
				op.pop();
			}
			op.pop();//�������ŵ���
		}
	}

	int count = op.size();
	//����������ջ�е���������
	while (!op.empty()) {
		if (count == 1) {    //���һ��������ո�
			cout << op.top();
			op.pop();
		}
		else {
			cout << op.top() << " ";
			op.pop();
		}
		count--;
	}
}

//�������㣬Ϊ��һ��ѭ����׼��
void Clear() {
	//Input����
	Input.clear();
	//��Item����
	for (int i = 0; i < 20; i++) {
		Item[i].clear();
	}
	//��space����
	space = 0;
	c = 0;
    
}

int main()
{
		cout << "������һ����׺���ʽ��Ҫ�������+,-,*,/,(,)����������20���ַ���(ע�����漰�������������ΪӢ�ķ��ţ���ÿ������ͬ�ַ�֮���һ���ո�)��" << endl;
		//������ʽ
		putin();
	while (1) {
		//�õ����ʽ��Item֮��Ϳ��Կ�ʼ�����׺���ʽ��
		postfix();
		
		//ѯ���Ƿ���Ҫ����
		char choice = 0;
		cout << endl << "�Ƿ���Ҫ������һ�֣�(Y����,N����):"; cin >> choice;
		if (choice == 'Y') {
			//���㣬Ϊ��һ����׼��
			Clear();
			int m = 0;
			m=getchar();     //���ջس�������Ӱ����һ��������ʽ��
			
			cout << endl<<"������һ����׺���ʽ��Ҫ�������+,-,*,/,(,)����������20���ַ���(ע�����漰�������������ΪӢ�ķ��ţ���ÿ������ͬ�ַ�֮���һ���ո�)��" << endl;
			//������ʽ
			putin();

		}
		else if(choice=='N'){
			break;
		}
	}
	return 0;
}