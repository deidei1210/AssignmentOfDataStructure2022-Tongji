#include<iostream>

using namespace std;

//表示一个家庭成员的节点
struct Node {
	string name = "";          //表示这个家庭成员的名字
	Node* parent = NULL; //表示指向该家庭成员父母节点的指针，如果是NULL表示是祖先，上面没有父母节点了
	Node* next = NULL;    //表示连接下一个成员的指针
	int ChildNum = 0;      //该家庭成员孩子的数量
	int Generation = 0;    //表示这是家庭中的第几代
};

class Family {
private:
	Node* member = NULL;    //用来存放成员链表（用链表的方式存储树)
	int gen = 0;//用来记录这个家谱现在一共有几代了
public:
	Family();       //构造函数
	~Family();    //析构函数
	void SetAncestor();   //创立一个祖先
	void SetFamily(string name);      //创建家庭
	void AddMember(string name);   //给家谱中的一个成员添加儿子或者女儿
	void BreakUpFamily(string name);//解散指定成员的家庭
	void ChangeName(string name);  //给家谱中的一位成员改名
	Node* Locate(string name);     //寻找家谱中指定成员的位置，并将其指针返回
	void PrintChild(string name,int generation);   //打印其中一个家庭成员的孩子们
	void CheckChild(string name);   //查看指定成员的子孙
};
//缺省初始化
Family::Family() {
	member = NULL;
	gen = 0;
}
void Family::PrintChild(string name,int generation) {
	Node* p = Locate(name);
	if (p == NULL) {
	//	cout << "家谱中没有" << name << endl;
		return;
	}
	Node*q=p->next;
	if (q!=NULL&&q->parent == p) {     //说明q是有孩子的
		cout << name << "的第一代子孙是：";
		while (q!=NULL&&q->Generation!=p->Generation) {
			if(q->Generation==p->Generation+generation)
			        cout << q->name << " ";
			q = q->next;
		}
	}
	else {      //说明q是没孩子的
		cout << name << "没有孩子！";
	}
	cout << endl;
}
//寻找家谱中指定成员的位置，并将其指针返回
Node* Family::Locate(string name) {
	Node* p = member;    //将p指向member
	while (p != NULL) {
		if (p->name == name)     //发现姓名相同，说明找到了我想找的成员，直接返回
			return p;
		p = p->next;
	}
	return NULL;      //如果说找了一圈都没找到，那就返回空指针
}
//创立祖先
void Family::SetAncestor() {
	cout << "请输入祖先的姓名：";
	member = new Node;
	cin >> member->name; //输入祖先姓名
	cout << "此家族的祖先是：" << member->name << endl;
	gen = 0;
}
//创建家庭
void Family::SetFamily(string name) {
	//首先先找到该成员
	Node* p = Locate(name),*temp=NULL,*pos=NULL;    //pos用来定位孩子插入的地方
	if (p == NULL) {
		cout << "家谱中没有" << name << endl;
		return;
	}
	if (p->ChildNum != 0) {
		cout << "已经有了孩子组建过家庭，如果要继续添加孩子，请执行B操作！" << endl;
		return;
	}
	cout << "请输入" << name << "的儿女个数：";
	int n = 0;
	cin >> n;
	if (n >= 1) {
		p->ChildNum += n;                         //name的孩子增加n个
		cout << "请依次输入" << name << "的儿女姓名：";
		//将pos移到name家庭成员的最后一个孩子的位置
		pos = p;
		//将pos移到当前父母节点的最后一个孩子的位置
		while ( pos->next!=NULL&&pos->next->parent == p) {
			pos = pos->next;
		}
		while (n--) {
			Node* q = new Node;        //创立新的节点
			cin >> q->name;                //输入新成员的姓名
			q->parent = p;                   //他们的父母都是建立家庭之人
			q->Generation = q->parent->Generation + 1;  //表示他们是他们父母的下一代
			if (pos->next == NULL) {             //如果pos后面一个就是空指针的话
				pos->next = q;                       //直接让pos接在后面
				pos = pos->next;        //下一次他的孩子插入的位置
			}
			else {                //pos后面没有指向空指针，是指在一个具体的节点上的话
				q->next = pos->next;     //那就将q插入在两者之间
				pos->next = q;
				pos = q;
			}
		}
	}
	else {
		cout << "输入的儿女个数小于1，不进行家庭组建！" << endl;
		return;
	}
	gen = max(gen, p->Generation + 1);     //此时取两者之间较大的那一个
	return;
}
//添加家庭成员
void Family::AddMember(string name) {
	Node* p = Locate(name);
	if (p == NULL) {
		cout << "家谱中不存在" << name << "！"<<endl;
		return;
	}
	cout << "请输入" << name << "新添加的儿子（或女儿）的姓名：";
	Node* q = new Node,*pos=p;
	cin >> q->name;
	q->parent = p;
	q->Generation = p->Generation + 1;  //表示他们是他们父母的下一代
	//将pos移动到其下一个同辈的前面插入
	while (pos->next != NULL && pos->next->parent == p) {
		pos = pos->next;
	}
	if (pos->next == NULL) {             //如果pos后面一个就是空指针的话
		pos->next = q;                       //直接让pos接在后面
		pos = pos->next;        //下一次他的孩子插入的位置
	}
	else {                //pos后面没有指向空指针，是指在一个具体的节点上的话
		q->next = pos->next;     //那就将q插入在两者之间
		pos->next = q;
		pos = q;
	}
	gen = max(gen, p->Generation + 1);     //此时取两者之间较大的那一个
	p->ChildNum += 1;             //name的孩子增加1
}
//解散家庭，解散以该成员为根的子树
void Family::BreakUpFamily(string name) {
	Node* p = Locate(name),*temp=p,*temp1=NULL,*tail=NULL;      //定位
	if (p == NULL) {
		cout << "家谱中没有" << name << endl;
		return;
	}
	cout << "要解散家庭的人是：" << name << endl;

	if (p->next != NULL && p->next->parent == p) {     //说明q是有孩子的
		string Gen[200] = {};        //分配这么多个空间用来存储每一代的孩子
		while (temp->next != NULL && temp->next->Generation != p->Generation) {    
			temp1 = temp->next->next;
			//将其加入对应代数的数组，然后删去
			Gen[temp->next->Generation - p->Generation] += temp->next->name+" ";
			//然后将这个节点在family中删除
			delete temp->next;
			temp->next = temp1;
		}
		for (int i = 0; i < gen + 1; i++) {
			if (Gen[i] != "") {
				cout << name << "的第" << i << "代是：";
				cout << Gen[i] << endl;
			}
		}
	}
	else {
		cout << name << "没有孩子可以解散！" << endl;
	}
	cout << endl;
	p->ChildNum = 0;   //全部被解放了
}
//给家庭成员中的一位成员改名
void Family::ChangeName(string name) {
	Node* p = Locate(name);
	if (p == NULL) {
		cout << "家谱中没有" << name << "！" << endl;
		return;
	}
	cout << "请输入更改后的姓名：";
	cin >> p->name;
	cout << name << "已更名为" << p->name << endl;
}
//查看一位成员的所有子孙
void Family::CheckChild(string name) {
	Node* p = Locate(name),*temp=p;
	if (p == NULL) {
		cout << "家谱中不存在" << name << "！" << endl;
		return;
	}
	if (p->next!=NULL&&p->next->Generation != p->Generation) {
		string Gen[200] = {};
		while (temp->next!=NULL&&temp->next->Generation != p->Generation) { //当还没有遇见同辈的时候，将名字一个一个按照辈分存入Gen中
			Gen[temp->next->Generation - p->Generation] += temp->next->name+" ";
			temp = temp->next;
		}
		for (int i = 1; i < gen + 1; i++) {
			if (Gen[i] != "") {
				cout << name << "的第" << i << "代子孙是：" << Gen[i] << endl;
			}
		}
	}
	else {
		cout << name << "没有子孙！" << endl;
	}
	return;
}
//析构函数
Family::~Family() {
	//释放member链表
	Node* p = member->next;
	while (p != NULL) {
		p = p->next;
		delete member->next;
		member->next = p;
	}
	delete member;
}

char choice = 0;             //用来存储用户的每一次选择
Family family;                //定义一个家谱类

//菜单
void menu() {
	cout << "**              家谱管理系统               **" << endl;
	cout << "=============================================" << endl;
	cout << "**           请选择要执行的操作：          **" << endl;
	cout << "**            A --- 完善家谱               **" << endl;
	cout << "**            B --- 添加家庭成员           **" << endl;
	cout << "**            C --- 解散局部家庭           **" << endl;
	cout << "**            D --- 更改家庭成员姓名       **" << endl;
	cout << "**            E ---查看指定成员的子孙      **" << endl;
	cout << "**            F --- 退出程序               **" << endl;
	cout << "=============================================" << endl;
}


int main() {
	menu();     //输出菜单
	//先建立一个家谱，输入祖先的姓名
	cout << "首先建立一个家谱!" << endl;
	family.SetAncestor();
	//开始下面对家谱的一系列操作
	while (1) {
		cout << endl << "请选择要执行的操作：";
		cin >> choice;
		if (choice == 'A' || choice == 'a') {          //完善家谱
			string name;
			cout << "请输入要建立家庭的人的姓名：";
			cin >> name;
			family.SetFamily(name);
			family.PrintChild(name,1);
		}
		else if (choice == 'B' || choice == 'b') {       //添加家庭成员
			cout << "请输入要添加儿子（或女儿）的人的姓名：";
			string name;
			cin >> name;
			family.AddMember(name);
			family.PrintChild(name,1);
		}
		else if (choice == 'C' || choice == 'c') {        //解散局部家庭
			cout << "请输入要解散家庭的人的姓名：";
			string name;
			cin >> name;
			family.BreakUpFamily(name);
		}
		else if (choice == 'D' || choice == 'd') {       //更改家庭成员姓名
			cout << "请输入要更改姓名的人目前在家谱中的姓名：";
			string name;
			cin >> name;
			family.ChangeName(name);
		}
		else if (choice == 'E' || choice == 'e') {      //查看指定成员的子孙
			cout << "请输入想查看子孙的成员：";
			string name;
			cin >> name;
			family.CheckChild(name);
		}
		else if (choice == 'F' || choice == 'f') {         //说明退出程序
			cout << "欢迎下次使用！" << endl;
			break;
		}
		else {
			cout << "没有" << choice << "的操作可以执行，请重新选择！" << endl;
		}
	}

	return 0;
}
