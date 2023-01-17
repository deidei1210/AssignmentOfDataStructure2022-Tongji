#include<iostream>
using namespace std;

//��ʾ����ͼ���յ㼯��
struct Dest {
	int dest = 0;   //��ʾ�յ�Ľڵ����
	int time = 0;  //��ʾ��������ӵ�������м�����Ҫ��ʱ��
	Dest* link = NULL;  //��ʾ����������һ������������ӵ��յ�
};
//��ʾ����ͼ����ʼ����
struct Node {
	int data = 0;        //��¼������һ������
	Dest* adj = NULL;   //���������������յ���ɵ�����
};

Node* NodeTable = NULL;   //�ڽӱ�(����)
Node* NodeTableTopological = NULL;  //��ž������������Ľڵ�
int* inDegree = NULL;         //���ڴ��ÿ����������
int* Ve=NULL, * Vl=NULL;   //Ve��ʾ�¼�������ܿ�ʼ��ʱ�䣬�Ǵ�Դ�㵽�õ���·������
                                            //Vl��ʾ�¼��������ʼ��ʱ��
int e = 0, l = 0;                      //������ȵ�ʱ���ʾ�ؼ��
int n = 0,m=0;  //n�����񽻽ӵ�ĸ�����m�������������
int start = 0, finish = 0, time = 0;//start��������ʼ��ʱ�䣬end�Ǹ������������ʱ�䣬time����ɸ���������Ҫ��ʱ��

//�����Ϊi���յ�Ϊj��Ȩ��Ϊweight�ı������ڽӱ���
void InserEdge(int i, int j, int w) {
	Dest* p = NULL;     //���ڱ�����Ѱ�������ĩβ
	//����������ݴ����ڽӱ����߱���
	Dest* d = new Dest;
	d->dest = j;
	d->time = w;
	//��d���ڲ��뵽����NodeTable�ĺ���
	p = NodeTable[i].adj;
	if (p == NULL) {
		NodeTable[i].adj = d;
	}
	else {  //�Ͽ����뵽����
		d->link = p;
		NodeTable[i].adj = d;
	}
}
//����
void Read() {
	while (1) {
		cin >> n >> m;          //���뽻�ӵ�ĸ����������������
		//�ж�n��m�ĺϷ��ԣ�������벻�Ϸ���Ҫ��������
		if (n * (n - 1) < m) {
			cout << "������������ڿ��ܵ����ֵ�����������뽻�ӵ���������������" << endl;
		}
		else
			break;
	}
	int num = n + 1;      //����num���ռ�
	NodeTable = new Node[num];    //һ����n�����㣬���Ը�NodeTable����n���ڵ�Ŀռ�
	NodeTableTopological = new (nothrow)Node[num];
	inDegree = new(nothrow)int[num];
	Ve = new(nothrow) int[num];
	Vl = new(nothrow) int[num];
	if (!NodeTable || !NodeTableTopological || !inDegree || !Ve || !Vl) {
		cout << "��̬�ڴ�����ʧ�ܣ�" << endl;
		exit(0);
	}
	fill(inDegree, inDegree + n+1, 0);   //�����ȫ����ʼ��Ϊ0
	//Ϊ�˱������C8636�ľ��棬������ָ��ķ�ʽ��ֵ
	for (int i = 1; i <= n; i++) {
		(NodeTable+i)->data =i;   //�ýڵ�ı��
		*(inDegree+i) = 0;
		*(Ve+i) = 0;                            //��ʼ��Ϊ0
	}
	for (int i = 0; i < m; i++) {      //�����������������������ÿ��������ʼ�Ľڵ㣬�����Ľڵ�ͳ�����ʱ��
		cin >> start >> finish >> time;
		inDegree[finish]++;
		InserEdge(start, finish, time);    //�������߼��뵽�ڱ�ͼ��
	}
}
//�����������򲢼���Ve��Vl
int CaculateVeVl() {
	int top = -1;
	//��ɨ���ʼ״̬�����Ϊ0�Ķ���
	for (int i = 1; i <= n; i++) {
		if (inDegree[i] == 0) {
			inDegree[i] = top; 
			top = i;     //��ջ��ָ��ָ��������Ϊ��Ķ���
		}
	}
	int Max = 0;   //������Ve�е����ֵ
	int topo = 1;
	//�����������򣬲������Ve�Լ��·��
	for (int i = 1; i <= n; i++) {
		if (top == -1) {    //˵��������
			return 0;
		}
		else {   //����ջ��Ԫ�����
			int j = top;
			top = inDegree[top];   //��ջ
			//cout << j << endl;      //���
			NodeTableTopological[topo++] = NodeTable[j];  //�������������˳�������������������
			//Ȼ��ɨ��ö���ĳ��߱������߱��ϵĶ������-1����ʾ������û��
			//ͬʱ���������ӵ����е��Ve
			Dest*p = NodeTable[j].adj;
			while (p) {
				int k = p->dest;      //�����յ�ڵ�����
				Ve[k] = max(Ve[k], Ve[j] + p->time);  //����Ve��ֵ
				Max = max(Max, Ve[k]);
				if (--inDegree[k] == 0) {   //���ö������ȼ���1�����ж��Ƿ�Ϊ0
					//�����0�����ö�����ջ
					inDegree[k] = top;
					top = k;
				}
				p = p->link;
			}
		}
	}

	//����������Vl�����Ƚ�Vl�е�ֵȫ����ֵΪ���ֵ
	for (int i = 1; i <= n; i++) {
		Vl[i] = Max;
	}
	Dest* p = NULL; //���ڱ���ÿһ���ڵ�ĳ��߱�
	int k = 0,s=0;        
	for (int i = n - 1; i >= 1; i--) {
		s = NodeTableTopological[i].data;
		p = NodeTableTopological[i].adj;
		while (p) {
			k = p->dest;    //����k�洢�����ӵ��յ�����
			Vl[s] = min(Vl[k] - p->time, Vl[s]);
			p = p->link;      //ת����һ�����ӵĽڵ�
		}
	}
	//����Ve�е����ֵ����������������е��յ�δ�������һ���ڵ㣬���Բ��ܲݲݷ���
	/*for (int i = 1; i <= n; i++) {
		cout << Ve[i] << " " << Vl[i] << endl;
	}*/
	return Max;
}
//��ؼ�·��
void CriticalPath() {
	Dest* p = NULL;
	int k = 0;
	int s = 0;
	for (int i = 1; i <= n; i++) {
		s = i;
		p = NodeTable[i].adj;
		while (p != NULL) {
			k = p->dest;
			e = Ve[s];
			l = Vl[k] - p->time;
			if (l == e)        
				cout << s << "->" << k << endl;
			p = p->link;
		}
	}
}
//�ͷ�����Ķ�̬�ڴ�
void Clear() {
	if (NodeTable) {
		//��ÿһ���������ͷ�
		Dest* p=NULL;
		for (int i = 0; i <= n; i++) {
			p = NodeTable[i].adj;
			while (p) {
				p = p->link;
				delete NodeTable[i].adj;
				NodeTable[i].adj = p;
			}
		}
		delete[]NodeTable;
	}
	if (NodeTableTopological) {
		delete[]NodeTableTopological;
	}
	if (inDegree) {
		delete[]inDegree;
	}
	if (Ve) {
		delete[]Ve;
	}
	if (Vl) {
		delete[]Vl;
	}
}
int main() {
	Read();
	int res=CaculateVeVl();
	if (res) {   //������ʱ��
		cout << res << endl;
		CriticalPath();
	}
	else {      //�л�·�������еķ�������
		cout << 0 << endl;
	}
	Clear();   //�ͷ��ڴ�
	system("pause");
	return 0;
}