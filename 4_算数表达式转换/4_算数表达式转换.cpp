#define ISDIGIT   1                //是数字
#define ISOPERATOR 2               //是运算符
#define FROUNT 3                   //是前括号
#define BACK 4                     //是后括号

#include<iostream>
#include<sstream>                   //使用getline
using namespace std;

//题目要求既能支持多位输入，又能支持小数输入，因此只能一个一个输入，一个一个判断

string Input;          //用来存储最初的输入
string Item[21];       //用来存放表达式中的项
int space = 0;      //表示Item的下标，同时也代表空格的数量
int c = 0;        //用于计算需要输出的项的数量
const char* front = "（";
const char* back = "）";

//节点
struct Node {
	char data;
	Node* next;   //指向其后面一个节点
	Node* pre;     //指向其前面一个节点
};
//写一个运算符栈的类
class Stack {
private:
	Node* Top;         //栈顶指针，始终指向栈顶
	int s;
public:
	Stack();          //构造函数，默认初始化
	Stack(char ch); //构造函数，用一个栈底元素初始化
	void push(char ch);//将一个运算符塞进栈中      
	char pop();       //弹出顶部元素，并将其值的大小返回
	char top();       //返回栈顶的元素
	int size();       //返回栈的大小
	int empty();      //判断栈是否为空，空就返回1，非空返回0
	void MakeEmpty(); //使栈变成空的
	~Stack();         //析构函数
};
//下面是Stack中的函数
Stack::Stack() {
	Top = NULL;       //因此，Top是Null时表示空栈
	s = 0;
}
Stack::Stack(char ch) {
	Node* node = new Node;    //创建节点，使其成为第一个元素
	node->data = ch;
	node->next = NULL;
	node->pre = NULL;
	Top = node;               //让Top等于第一个节点
	s = 1;
	s++;
}
void Stack::push(char ch) {
	//首先创建一个节点
	Node* node = new Node;
	//给节点赋值
	node->data = ch;
	//如果这是个空栈，相当于用一个元素给栈初始化
	if (Top == NULL) {
		Node* node = new Node;    //创建节点，使其成为第一个元素
		node->data = ch;
		node->next = NULL;
		node->pre = NULL;
		Top = node;               //让Top等于第一个节点
	}
	else {     //如果这不是一个空栈，那么只需要将他连接在Top后面
		node->pre = Top;
		node->next = NULL;
		Top = node;
	}
	s++;
}
char Stack::pop() {
	//弹出栈顶元素，并返回，然后删除这个节点
	//如果这个栈是空的
	if (Top == NULL) {
		return 0;
	}
	else {    //如果这个栈不是空的
		char c = Top->data;         //暂存栈顶数据
		Node* node = Top;           //用一个节点代替Top
		Top = Top->pre;             //将Top挪到前一个元素
		delete node;                //删除顶部节点
	}
	s--;
	return c;                       //返回顶部节点的数据
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

Stack op;    //运算符栈

//用于检查是否存在中文括号
int Check(int i) {

	if (Input[i]==front[0]|| Input[i] == front[1]|| Input[i] == back[0]|| Input[i] == back[1]) {
		return 0;
	}
}

//用于输入，获得基础数据
void putin() {
	while (1) {
		//先输入带空格的一整行
		getline(cin, Input);             //getline可以读入空格，遇到回车键结束
		//由于不超过20个字符，所以Input中最多19个空格，下面在计算的时候要注意
		int len = Input.length();
		//给Item赋值，如果输入超过20个就重新输入
		int flag = 1;
		
		while (1) {
			for (int i = 0; i < len; i++) {
				if (Input[i] != ' ') {
					//检查是否有中文符号，如果有，重新输入
					flag=Check(i);
					if (!flag) {
						cout << "输入的式子含有中文符号，请关闭中文输入法,重新输入！" << endl;
						break;
					}
					//没有中文符号，就继续存入Item中
					Item[space] += Input[i];
					//括号是最后不被输出的
					if (Input[i] == '(' || Input[i] == ')') {
						c++;
					}
				}
				else {
					space++;
					//说明输入超过20项，需要重新输入
					if (space >= 20) {
						cout << "输入的字符超过20项最大限额，请重新输入!" << endl;
						break;
					}
				}
			}
			break;
		}

		//输入超过20个元素，或者输入中文符号，清空之前的输入，重新输入
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
	//计算出需要输出的元素个数：总元素个数减去括号的个数
	c = space+1 - c;
}

//用于判断输入的Input是数还是运算符
int Judge(string& Input) {
	int len = Input.length();
	//如果输入的字符串长度大于1，那么一定是数字
	if (len > 1) {
		//如果第一项是符号位需要处理一下
		if (Input[0] == '+') {
			Input.erase(0, 1);                //如果是加号，那就删除第一个字符
		}
		return ISDIGIT;
	}
	else if(Input[0]>='0'&&Input[0]<='9'){ return ISDIGIT; }    //如果只有一个长度，并且这个字符在0到9之间，那么就是数字
	else if (Input[0] == '(') {return FROUNT;}
	else if (Input[0] == ')') {return BACK;}
	else {return ISOPERATOR;}
}

//用于返回运算符的优先级
int Priority(char operation) {
	switch (operation) {
		case '+':return 1;
		case '-':return 1;    //加号和减号是同级的运算符
		case '*': return 2;
		case  '/': return 2;   //乘号和除号是同级的运算符
	}
}

//用于按照顺序输出后缀表达式
void postfix() {
	for (int i = 0; i <= space; i++) {
		int judge = Judge(Item[i]);
		//先判断这一项是数字还是字符
		if (judge == ISDIGIT) {       //如果这一项是数字
			if (space == 0)          //如果是单项的数字，那么只要输出数字不要空格
				cout << Item[i];
			else
				cout << Item[i] << " ";      //否则要输出空格，反正最后一位一定是符号之类的
		}
		else if (judge == ISOPERATOR) {                  //如果这一项是运算符+ - * /
			//如果栈是空的，那就直接入栈，或者栈顶元素是左括号
			if (op.empty() || op.top() == '(') {
				op.push(Item[i][0]);
			}
			else {        //如果栈不是空的，且前面不是左括号，那就和栈顶的元素比较优先级
				//如果栈顶的符号优先级低于此时的符号，那么就入栈
				if (Priority(op.top()) < Priority(Item[i][0])) {
					op.push(Item[i][0]);
				}
				else {  //否则的话,在没有遇见左括号且栈没有空的情况下，就一直输出，直到遇见优先级比其低的运算符。总之，要保证栈中运算符优先级逐个递增的状态
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
		else if (judge == FROUNT) {                  //如果这一项是前括号，那就直接入栈
			op.push(Item[i][0]);
		}
		else if (judge == BACK) {                     //如果这一项是后括号，那就将前括号后的符号全部输出，并且将前括号弹出
			while (op.top() != '(') {
				cout << op.top() << " ";
				op.pop();
			}
			op.pop();//将左括号弹出
		}
	}

	int count = op.size();
	//把最后残留在栈中的运算符输出
	while (!op.empty()) {
		if (count == 1) {    //最后一个不输出空格
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

//用于清零，为下一个循环做准备
void Clear() {
	//Input清零
	Input.clear();
	//给Item清零
	for (int i = 0; i < 20; i++) {
		Item[i].clear();
	}
	//给space清零
	space = 0;
	c = 0;
    
}

int main()
{
		cout << "请输入一个中缀表达式（要求仅包含+,-,*,/,(,)），不超过20个字符。(注：所涉及的算数运算符均为英文符号，且每两个不同字符之间加一个空格)：" << endl;
		//输入表达式
		putin();
	while (1) {
		//得到表达式和Item之后就可以开始输出后缀表达式了
		postfix();
		
		//询问是否需要继续
		char choice = 0;
		cout << endl << "是否需要进入下一轮？(Y继续,N结束):"; cin >> choice;
		if (choice == 'Y') {
			//清零，为下一次做准备
			Clear();
			int m = 0;
			m=getchar();     //吸收回车，以免影响下一次输入表达式。
			
			cout << endl<<"请输入一个中缀表达式（要求仅包含+,-,*,/,(,)），不超过20个字符。(注：所涉及的算数运算符均为英文符号，且每两个不同字符之间加一个空格)：" << endl;
			//输入表达式
			putin();

		}
		else if(choice=='N'){
			break;
		}
	}
	return 0;
}