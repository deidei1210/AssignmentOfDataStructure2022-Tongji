#include<iostream>

using namespace std;

//��ʾһ����ͥ��Ա�Ľڵ�
struct Node {
	string name = "";          //��ʾ�����ͥ��Ա������
	Node* parent = NULL; //��ʾָ��ü�ͥ��Ա��ĸ�ڵ��ָ�룬�����NULL��ʾ�����ȣ�����û�и�ĸ�ڵ���
	Node* next = NULL;    //��ʾ������һ����Ա��ָ��
	int ChildNum = 0;      //�ü�ͥ��Ա���ӵ�����
	int Generation = 0;    //��ʾ���Ǽ�ͥ�еĵڼ���
};

class Family {
private:
	Node* member = NULL;    //������ų�Ա����������ķ�ʽ�洢��)
	int gen = 0;//������¼�����������һ���м�����
public:
	Family();       //���캯��
	~Family();    //��������
	void SetAncestor();   //����һ������
	void SetFamily(string name);      //������ͥ
	void AddMember(string name);   //�������е�һ����Ա��Ӷ��ӻ���Ů��
	void BreakUpFamily(string name);//��ɢָ����Ա�ļ�ͥ
	void ChangeName(string name);  //�������е�һλ��Ա����
	Node* Locate(string name);     //Ѱ�Ҽ�����ָ����Ա��λ�ã�������ָ�뷵��
	void PrintChild(string name,int generation);   //��ӡ����һ����ͥ��Ա�ĺ�����
	void CheckChild(string name);   //�鿴ָ����Ա������
};
//ȱʡ��ʼ��
Family::Family() {
	member = NULL;
	gen = 0;
}
void Family::PrintChild(string name,int generation) {
	Node* p = Locate(name);
	if (p == NULL) {
	//	cout << "������û��" << name << endl;
		return;
	}
	Node*q=p->next;
	if (q!=NULL&&q->parent == p) {     //˵��q���к��ӵ�
		cout << name << "�ĵ�һ�������ǣ�";
		while (q!=NULL&&q->Generation!=p->Generation) {
			if(q->Generation==p->Generation+generation)
			        cout << q->name << " ";
			q = q->next;
		}
	}
	else {      //˵��q��û���ӵ�
		cout << name << "û�к��ӣ�";
	}
	cout << endl;
}
//Ѱ�Ҽ�����ָ����Ա��λ�ã�������ָ�뷵��
Node* Family::Locate(string name) {
	Node* p = member;    //��pָ��member
	while (p != NULL) {
		if (p->name == name)     //����������ͬ��˵���ҵ��������ҵĳ�Ա��ֱ�ӷ���
			return p;
		p = p->next;
	}
	return NULL;      //���˵����һȦ��û�ҵ����Ǿͷ��ؿ�ָ��
}
//��������
void Family::SetAncestor() {
	cout << "���������ȵ�������";
	member = new Node;
	cin >> member->name; //������������
	cout << "�˼���������ǣ�" << member->name << endl;
	gen = 0;
}
//������ͥ
void Family::SetFamily(string name) {
	//�������ҵ��ó�Ա
	Node* p = Locate(name),*temp=NULL,*pos=NULL;    //pos������λ���Ӳ���ĵط�
	if (p == NULL) {
		cout << "������û��" << name << endl;
		return;
	}
	if (p->ChildNum != 0) {
		cout << "�Ѿ����˺����齨����ͥ�����Ҫ������Ӻ��ӣ���ִ��B������" << endl;
		return;
	}
	cout << "������" << name << "�Ķ�Ů������";
	int n = 0;
	cin >> n;
	if (n >= 1) {
		p->ChildNum += n;                         //name�ĺ�������n��
		cout << "����������" << name << "�Ķ�Ů������";
		//��pos�Ƶ�name��ͥ��Ա�����һ�����ӵ�λ��
		pos = p;
		//��pos�Ƶ���ǰ��ĸ�ڵ�����һ�����ӵ�λ��
		while ( pos->next!=NULL&&pos->next->parent == p) {
			pos = pos->next;
		}
		while (n--) {
			Node* q = new Node;        //�����µĽڵ�
			cin >> q->name;                //�����³�Ա������
			q->parent = p;                   //���ǵĸ�ĸ���ǽ�����֮ͥ��
			q->Generation = q->parent->Generation + 1;  //��ʾ���������Ǹ�ĸ����һ��
			if (pos->next == NULL) {             //���pos����һ�����ǿ�ָ��Ļ�
				pos->next = q;                       //ֱ����pos���ں���
				pos = pos->next;        //��һ�����ĺ��Ӳ����λ��
			}
			else {                //pos����û��ָ���ָ�룬��ָ��һ������Ľڵ��ϵĻ�
				q->next = pos->next;     //�Ǿͽ�q����������֮��
				pos->next = q;
				pos = q;
			}
		}
	}
	else {
		cout << "����Ķ�Ů����С��1�������м�ͥ�齨��" << endl;
		return;
	}
	gen = max(gen, p->Generation + 1);     //��ʱȡ����֮��ϴ����һ��
	return;
}
//��Ӽ�ͥ��Ա
void Family::AddMember(string name) {
	Node* p = Locate(name);
	if (p == NULL) {
		cout << "�����в�����" << name << "��"<<endl;
		return;
	}
	cout << "������" << name << "����ӵĶ��ӣ���Ů������������";
	Node* q = new Node,*pos=p;
	cin >> q->name;
	q->parent = p;
	q->Generation = p->Generation + 1;  //��ʾ���������Ǹ�ĸ����һ��
	//��pos�ƶ�������һ��ͬ����ǰ�����
	while (pos->next != NULL && pos->next->parent == p) {
		pos = pos->next;
	}
	if (pos->next == NULL) {             //���pos����һ�����ǿ�ָ��Ļ�
		pos->next = q;                       //ֱ����pos���ں���
		pos = pos->next;        //��һ�����ĺ��Ӳ����λ��
	}
	else {                //pos����û��ָ���ָ�룬��ָ��һ������Ľڵ��ϵĻ�
		q->next = pos->next;     //�Ǿͽ�q����������֮��
		pos->next = q;
		pos = q;
	}
	gen = max(gen, p->Generation + 1);     //��ʱȡ����֮��ϴ����һ��
	p->ChildNum += 1;             //name�ĺ�������1
}
//��ɢ��ͥ����ɢ�Ըó�ԱΪ��������
void Family::BreakUpFamily(string name) {
	Node* p = Locate(name),*temp=p,*temp1=NULL,*tail=NULL;      //��λ
	if (p == NULL) {
		cout << "������û��" << name << endl;
		return;
	}
	cout << "Ҫ��ɢ��ͥ�����ǣ�" << name << endl;

	if (p->next != NULL && p->next->parent == p) {     //˵��q���к��ӵ�
		string Gen[200] = {};        //������ô����ռ������洢ÿһ���ĺ���
		while (temp->next != NULL && temp->next->Generation != p->Generation) {    
			temp1 = temp->next->next;
			//��������Ӧ���������飬Ȼ��ɾȥ
			Gen[temp->next->Generation - p->Generation] += temp->next->name+" ";
			//Ȼ������ڵ���family��ɾ��
			delete temp->next;
			temp->next = temp1;
		}
		for (int i = 0; i < gen + 1; i++) {
			if (Gen[i] != "") {
				cout << name << "�ĵ�" << i << "���ǣ�";
				cout << Gen[i] << endl;
			}
		}
	}
	else {
		cout << name << "û�к��ӿ��Խ�ɢ��" << endl;
	}
	cout << endl;
	p->ChildNum = 0;   //ȫ���������
}
//����ͥ��Ա�е�һλ��Ա����
void Family::ChangeName(string name) {
	Node* p = Locate(name);
	if (p == NULL) {
		cout << "������û��" << name << "��" << endl;
		return;
	}
	cout << "��������ĺ��������";
	cin >> p->name;
	cout << name << "�Ѹ���Ϊ" << p->name << endl;
}
//�鿴һλ��Ա����������
void Family::CheckChild(string name) {
	Node* p = Locate(name),*temp=p;
	if (p == NULL) {
		cout << "�����в�����" << name << "��" << endl;
		return;
	}
	if (p->next!=NULL&&p->next->Generation != p->Generation) {
		string Gen[200] = {};
		while (temp->next!=NULL&&temp->next->Generation != p->Generation) { //����û������ͬ����ʱ�򣬽�����һ��һ�����ձ��ִ���Gen��
			Gen[temp->next->Generation - p->Generation] += temp->next->name+" ";
			temp = temp->next;
		}
		for (int i = 1; i < gen + 1; i++) {
			if (Gen[i] != "") {
				cout << name << "�ĵ�" << i << "�������ǣ�" << Gen[i] << endl;
			}
		}
	}
	else {
		cout << name << "û�����" << endl;
	}
	return;
}
//��������
Family::~Family() {
	//�ͷ�member����
	Node* p = member->next;
	while (p != NULL) {
		p = p->next;
		delete member->next;
		member->next = p;
	}
	delete member;
}

char choice = 0;             //�����洢�û���ÿһ��ѡ��
Family family;                //����һ��������

//�˵�
void menu() {
	cout << "**              ���׹���ϵͳ               **" << endl;
	cout << "=============================================" << endl;
	cout << "**           ��ѡ��Ҫִ�еĲ�����          **" << endl;
	cout << "**            A --- ���Ƽ���               **" << endl;
	cout << "**            B --- ��Ӽ�ͥ��Ա           **" << endl;
	cout << "**            C --- ��ɢ�ֲ���ͥ           **" << endl;
	cout << "**            D --- ���ļ�ͥ��Ա����       **" << endl;
	cout << "**            E ---�鿴ָ����Ա������      **" << endl;
	cout << "**            F --- �˳�����               **" << endl;
	cout << "=============================================" << endl;
}


int main() {
	menu();     //����˵�
	//�Ƚ���һ�����ף��������ȵ�����
	cout << "���Ƚ���һ������!" << endl;
	family.SetAncestor();
	//��ʼ����Լ��׵�һϵ�в���
	while (1) {
		cout << endl << "��ѡ��Ҫִ�еĲ�����";
		cin >> choice;
		if (choice == 'A' || choice == 'a') {          //���Ƽ���
			string name;
			cout << "������Ҫ������ͥ���˵�������";
			cin >> name;
			family.SetFamily(name);
			family.PrintChild(name,1);
		}
		else if (choice == 'B' || choice == 'b') {       //��Ӽ�ͥ��Ա
			cout << "������Ҫ��Ӷ��ӣ���Ů�������˵�������";
			string name;
			cin >> name;
			family.AddMember(name);
			family.PrintChild(name,1);
		}
		else if (choice == 'C' || choice == 'c') {        //��ɢ�ֲ���ͥ
			cout << "������Ҫ��ɢ��ͥ���˵�������";
			string name;
			cin >> name;
			family.BreakUpFamily(name);
		}
		else if (choice == 'D' || choice == 'd') {       //���ļ�ͥ��Ա����
			cout << "������Ҫ������������Ŀǰ�ڼ����е�������";
			string name;
			cin >> name;
			family.ChangeName(name);
		}
		else if (choice == 'E' || choice == 'e') {      //�鿴ָ����Ա������
			cout << "��������鿴����ĳ�Ա��";
			string name;
			cin >> name;
			family.CheckChild(name);
		}
		else if (choice == 'F' || choice == 'f') {         //˵���˳�����
			cout << "��ӭ�´�ʹ�ã�" << endl;
			break;
		}
		else {
			cout << "û��" << choice << "�Ĳ�������ִ�У�������ѡ��" << endl;
		}
	}

	return 0;
}
