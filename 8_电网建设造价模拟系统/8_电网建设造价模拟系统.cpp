#define MAX 0x3f3f3f3f
#include<iostream>

using namespace std;

struct Cost {
	int cost = MAX;  //��ʾ���루��ʼֵ�����������ֵ��
	int a = 0;       //��ʾ�����һ�����
	int b = 0;       //��ʾ�������һ�����
};

int NodeNum = 0;//��ʾ�����ж�����ܸ���
char* NodeName = NULL;//����һ���ַ����飬�����洢�ַ�������
int** SideCost=NULL;    //����һ����ά�������ڴ洢����ָ���ڵ�֮���������Ļ���
int* vis=NULL;  //�����жϸõ��Ƿ��Ѿ������ʹ�
Cost* NodeMinCost=NULL;  //�����浱ǰ�ڵ�֮����µ���С����
Cost* method=NULL;       //һ�������洢��С����������������
long long sum = 0;         //��С��������Ȩֵ֮��

void menu() {
	cout << "**           �������ģ��ϵͳ          **" << endl;
	cout << "=========================================" << endl;
	cout << "**          ��ѡ��Ҫִ�еĲ���         **" << endl;
	cout << "**          A---������������           **" << endl;
	cout << "**          B---��ӵ����ı�           **" << endl;
	cout << "**          C---������С������         **" << endl;
	cout << "**          D---��ʾ��С������         **" << endl;
	cout << "**          E---�˳�����               **" << endl;
	cout << "=========================================" << endl;
}
//���������ڵ�
void CreateMatrixNode() {
	cout << "�����붥��ĸ���:";
	while (1) {
		cin >> NodeNum;
		if (NodeNum <= 1) {
			cout << "����̫�٣������Թ��ɵ��������������룡" << endl;
		}
		else
			break;
	}
	NodeName = new char[NodeNum];    //���洢�ڵ��ָ�밴�����洢�������ƵĿռ�	
	cout << "��������������������:" << endl;
	for (int i = 0; i < NodeNum; i++) {
		cin >> NodeName[i];
	}
}
//��λһ���ַ��Ƿ���������Ķ��㣬��������λ��
int Location(char c) {
	for (int i = 0; i < NodeNum; i++) {
		if (c == NodeName[i]) {
			return i;
		}
	}
	return -1;
}
//��ÿ������֮��Ļ��Ѵ���SideCost����֮��
int  SaveToArray(char node1, char node2, int cost) {
	int n1 = -1,n2 = -1;   //n1��ʾnode1��NodeName�е�n1�����㣬n2��ʾnode2��NodeName�е�n2������
	int flag = 0;           //������¼�Ƿ��Ѿ��ҵ����������ڵ�
	for (int i = 0; i < NodeNum; i++) {
		if (node1 == NodeName[i]) {
			n1 = i;
		}
		if (node2 == NodeName[i]) {
			n2 = i;
		}
		if (n1!=-1 && n2!=-1) { 
			flag = 1;
			break;
		}//����������ҵ��ˣ��Ǿ��˳�
	}
	if (flag) {
		if (n1 == n2)
			return 2;
		SideCost[n1][n2] = min(SideCost[n1][n2], cost);       //ȡ��Сֵ
		SideCost[n2][n1] = min(SideCost[n2][n1], cost);
	}
	//cout << "��ʱn1Ϊ" << n1 << ",n2Ϊ" << n2 << endl;
	return flag;
}
//��ӵ����ı�
void AddMatrixSide() {
	if (NodeNum == 0) {
		cout << "���ȹ������㣡" << endl;
		return;
	}
	//�����ʱSideCost��δ����ռ�
	if (SideCost == NULL) {
		//���洢������֮������·�߼���������軨�ѵĶ�άָ�밴������ڴ�
		SideCost = new int* [NodeNum];
		for (int i = 0; i < NodeNum; i++) {
			SideCost[i] = new int[NodeNum];
			//�������ά���鸳ֵ������ȫ��Ϊ���ֵ
			for (int j = 0; j < NodeNum; j++) {
				SideCost[i][j] = MAX;
			}
		}
	}
	else {    //����Ѿ�������ռ䣬��ôֻ��Ҫֱ�Ӱ�ÿһ��ع��ʼ�Ĵ�С���ɣ�Ȼ��������������
		for (int i = 0; i < NodeNum; i++) {
			//�������ά���鸳ֵ������ȫ��Ϊ���ֵ
			for (int j = 0; j < NodeNum; j++) {
				SideCost[i][j] = MAX;
			}
		}
	}
	//���֮ǰִ�й�������С�������Ĳ�������ô��Щ��Ҫȫ�����㣬��Ϊһ�����е���߾���Ҫ����֮ǰ����Ľڵ������������бߵ�Ȩ��Ȼ�󹹳��µ���С������
	if (vis && method && NodeMinCost) {
			delete[]vis;
			vis = NULL;
			delete[]NodeMinCost;
			NodeMinCost = NULL;
			delete[]method;
			method = NULL;
			sum = 0;
	}
	int MaxSideNum = NodeNum * (NodeNum - 1) / 2;  //�ߵ����������������ӵı������ܳ����������
	char node1, node2; //��ʾ����������ڵ�
	int count = 0;//���ڼ�¼����ı���
	int cost = 0;  //��ʾ����Ҫ�����������֮���������ķ���
	int flag = 0; //���ڼ�¼������ַ��Ƿ��ǽڵ�
	cout << "�������������㼰������֮���������ķ���(�������node1����node2��һ�����ǵ����еĽڵ��ֹͣ����):" << endl;
	while (1) {
		cin >> node1 >> node2 >> cost;
		flag=SaveToArray(node1, node2, cost);     //������Ľڵ�ͻ��Ѵ������飨��Ҫ��Ҫ���ڵ�ת���������±꣩
		if (!flag) {     //˵�������ߵĹ��̽���
			if (count >= NodeNum - 1) {
				cout << "���б��������!" << endl;
				break;
			}
			else {
				cout << "����ıߵĸ���̫�٣�������ʹ�����ж�����ͨ����������룡" << endl;
			}
		}
		else if(flag==1){
			count++;//˵�������߳ɹ�������һ����
			if (count >= MaxSideNum) {   //����Ѿ�����������
				cout << "�Ѿ���������������������б�������ϣ�" << endl;
				break;
			}
		}
		else {
			cout << "���������������ͬ�����������룡" << endl;
		}
	 }
}
//������С������
void Prim(){
	if (NodeNum == 0) {
		cout << "���ȹ������㣡" << endl;
		return;
	}
	if (SideCost == NULL) {
		cout << "����������������֮���޽������Ļ��ѣ�" << endl;
		return;
	}
	sum = 0;
	char start = 0;
	int LocationStart = 0;
	vis = new int[NodeNum];
	for (int i = 0; i < NodeNum; i++) {
		vis[i] = 0;
	}
	NodeMinCost = new Cost[NodeNum];
	method = new Cost[NodeNum * (NodeNum - 1) / 2];
	int c = 0;
	while (1) {
		cout << "��������ʼ����:";
		cin >> start;      //������ʼ����
		//���start�Ƿ���NodeName�еĶ��㣬����λ�����ǵڼ����ڵ�
		LocationStart = Location(start);
		if (LocationStart == -1) {//˵��û�ҵ�
			cout << "�������ʼ����ǵ����еĶ��㣡���������룡" << endl;
		}
		else
			break;
	}
	//��������ʼ����Prim������С������
	NodeMinCost[LocationStart].cost = 0;
	// һ���� n ����,����Ҫ ���� n ��,ÿ��Ѱ��һ��Ȩֵ��С�ĵ�,��¼���±�
	for (int i = 0; i < NodeNum; i++) {
		int cur = -1;
		for (int j = 0; j < NodeNum; j++) {
			//�����ǰ����㻹û�б����ʹ�������cur��δָ���κ�һ���ڵ���ߵ���ǰָ��Ľڵ�ľ��벻���½ڵ㻨�Ѹ���
			if (!vis[j] && (cur == -1 || NodeMinCost[j].cost < NodeMinCost[cur].cost)) {
				cur = j;     //��ô���õ�ǰ��i���ڵ�ָ���j���ڵ㣬Ҳ���ǰ�Ҫ���ӵ��Ǹ���cur���j
			}
		}
		// ����������������˵���޷�������С����������Ϊ�����ͼ����Ͳ�����ʹ�����еĵ���ͨ��·��
		if (cur != -1 && NodeMinCost[cur].cost >= MAX) {
			if (vis && method && NodeMinCost) {
				delete[]vis;
				vis = NULL;
				delete[]NodeMinCost;
				NodeMinCost = NULL;
				delete[]method;
				method = NULL;
				sum = 0;
			}
			cout << "�޷�������С���������뷵��Bѡ��ʹ�������ͼ��ʹ�����е���ͨ��" << endl;
			return;
		}
		if (cur != -1) {
			//���ܻ����ϼ��ϵ�ǰɸѡ���Ļ�����Сֵ
			sum += NodeMinCost[cur].cost;
			//������������=�Ѿ�������ʹ���(��ֹһ���ڵ㱻ͬʱ����������Ϊ�˱������ɻ�)
			vis[cur] = 1;
			if (i != 0) {
				//�洢��ʱ�ķ���
				method[c++] = NodeMinCost[cur]; 
			}
		}
		// ֻ���»�û���ҵ�����СȨֵ
		for (int k = 0; k < NodeNum; k++) {
			if (!vis[k] && cur != -1) {
				//���´ӵ�ǰ���ڵ�����㵽�����Ѿ��߹��ĵ����С����
				//dist[k].length = min(dist[k].length, a[cur][k]);
				if (NodeMinCost[k].cost > SideCost[cur][k]) {
					NodeMinCost[k].cost = SideCost[cur][k];
					NodeMinCost[k].a = cur;
					NodeMinCost[k].b = k;
				}
			}
		}
	}
	cout << "����Prim��С��������" << endl;
}
//��ʾ��С������
void Print() {
	if (NodeNum == 0) {
		cout << "���ȹ������㣡" << endl;
		return;
	}
	if (SideCost == NULL) {
		cout << "����������������֮���޽������Ļ��ѣ�" << endl;
		return;
	}
	if (method == NULL) {
		cout << "����������С��������" << endl;
		return;
	}

	cout << "��С�������Ķ��㼰��Ϊ��" << endl << endl;
	//��ӡmethod
	//method��NodeNum-1����
	for (int i = 0; i < NodeNum-2; i++) {
		cout << NodeName[method[i].a] << "-(" << method[i].cost << ")->" << NodeName[method[i].b]<<"        ";
	}
	//���һ���ߵ�������Ӷ���������ж���Ŀո�
	cout << NodeName[method[NodeNum - 2].a] << "-(" << method[NodeNum - 2].cost << ")->" << NodeName[method[NodeNum - 2].b]<<endl;
	//�����С����
	cout << "������Ϊ��" << sum << endl;
	return;
}
//�����ͷŷ�����ڴ�������㣬�Ӷ�Ϊ��һ����׼��
void Clear() {
	if (NodeName) {
		delete[]NodeName; //�ͷŴ洢�������Ƶ�һάָ��
		NodeName = NULL;
	}
	for (int i = 0; i < NodeNum; i++) {
		delete[]SideCost[i];
		SideCost[i] = NULL;
	}
	if (SideCost) {
		delete[]SideCost;
		SideCost = NULL;
	}
	if (vis) {
		delete[]vis;
		vis = NULL;
	}
	if (NodeMinCost) {
		delete[]NodeMinCost;
		NodeMinCost = NULL;
	}
	if (method) {
		delete[]method;
		method = NULL;
	}
	NodeNum = 0;   //ʹ�õ����ж�����ܸ�������
	sum = 0;
}
char choice = 0;  //�����洢�û���ѡ��
int main() {
	menu();  //����˵�

	while (1) {
		cout << endl << "��ѡ�����:";     //ÿһ�����û�ѡ������Ҫ���еĲ���
		cin >> choice;

		if (choice == 'A'||choice=='a') {       //���������ڵ�
			Clear();        //ÿһ�δ����µĵ���ʱ��Ҫ�������һ�ε�����
			CreateMatrixNode();
		}
		else if (choice == 'B'||choice=='b') {//��ӵ����ı�
			AddMatrixSide();
		}
		else if (choice == 'C'||choice=='c') {//������С������
			Prim();
		}
		else if (choice == 'D'||choice=='d') {//��ʾ��С������
			Print();
		}
		else if (choice == 'E'||choice=='e') {  //�˳�����
			cout << "��ӭ�´�ʹ�ã�" << endl;
			Clear();        //�ͷ�������ڴ�֮�����˳�����
			break;
		}
		else {     //�������
			cout << "���벻����Ҫ��û��" << choice << "��ѡ����������룡" << endl;
			continue;
		}
	}
	return 0;
}