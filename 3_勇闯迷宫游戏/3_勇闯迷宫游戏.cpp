#include<iostream>
#include <stdio.h>
#define N 100
using namespace std;
void dfs(int x, int y);

//���ڶ�������
struct Position {
	int x;
	int y;
};
//��ʾ�Թ��ϵĽڵ�

//��ʾ˫������
struct Node {
	int x;             //�Թ��ϵ�����
	int y;
	Node* next;       //��ʾ��һ���ڵ�
	Node* head;       //��ʾͨ���˴�����һ���ڵ�
};
Node* r=NULL, * r1=NULL, * r2=NULL;

//�ֹ������ͼ
char map[N][N] = {};
//��ʾ�ҵ��Թ������и���
int row = 0;
int col = 0;
//��ʾ�н����ĸ�����
const Position direction[4] = { {0,1},{0,-1},{-1,0},{1,0} };
//���ڵ�����
Position exitPos = {};
//�ж��Ƿ񵽴��յ�
int finish = 0;
//��¼�Ƿ��������
bool visited[N][N] = {};
bool flag = 1;
//�����������
void dfs(int x, int y) {
	//�ҵ����ڣ�����
	if (x == exitPos.x && y == exitPos.y) {
		finish = 1;
		return;
	}
	//��û�ҵ����ڣ������������з���
	for (int i = 0; i < 4; i++) {
		//�����������һ��ͨ·������û�з��ʹ��ģ��Ǿ�����
		if (map[x + direction[i].x][y + direction[i].y] == '0' &&visited[x + direction[i].x][y + direction[i].y] == 0) {
			//��¼�Ѿ����ʹ���
			visited[x + direction[i].x][y + direction[i].y] = 1;
			//������һ��λ�ã������µĽڵ�
			r2 = new(nothrow)Node;
			if (!r2) {
				cout << "�ڴ�����ʧ�ܣ�" << endl;
				exit(0);
			}
			r2->next = NULL;
			r2->x = x + direction[i].x;
			r2->y = y + direction[i].y;
			//ǰһ���ڵ����r1����һ���ڵ����r2
			r2->head = r1;
			r1->next = r2;
			r1 = r2;
			//��ֵ��֮���ô�ʱ��ǰһ���ڵ��ɵ�ǰ�ڵ㣬�Ӷ�����
			dfs(x + direction[i].x, y + direction[i].y);
			if (finish == 1) {
				return;
			}
		}
	}

	//��������һ����û��ִ�е���Ҳ����˵��ǰ�ڵ㲻���յ㣬��������·һ�����Ǿ�ִ����������
	if (r1->head) {//�����ǰ�ڵ���ǰһ���ڵ�
		r1 = r1->head;//�Ǿ�Ų��ǰһ���ڵ�

		//�Ƚ�����Ŀռ�ȫ�����ͷ�
		Node* ptr = r1->next,*p=ptr;
		while (ptr != NULL) {
			p = ptr;
			ptr = ptr->next;
			delete p;
		}

		r1->next = NULL;//Ȼ�󽫺���Ľڵ�ϵ�
		dfs(r1->x, r1->y);//�ڵ�ǰ�ڵ����¿�ʼ����
	}
	else {
		cout << "ERROR" << endl;
		finish = 1;
		flag = 0;
		return;
	}
	return;
}
//���ڴ�ӡ��ͼ
void printMapRoute()
{
	cout << "�Թ���ͼ��" << endl;
	//��·������Ҫ�ߵ��ĵط�ȫ����ֵΪx
	while (r) {
		map[r->x][r->y] = 'x';
		r = r->next;
	}
	//�Ƚ���ͷ��ӡ����
	for (int i = 0; i < col; i++){
		cout << '\t' << i << "��" << '\t';
	}
	cout << endl;
	//�ѱ�ͷ��ӡ��֮��һ�п�ʼ��ӡ����
	for (int i = 0; i < row; i++){
		cout << i << "��" << '\t';            //ÿ��һ�ж����������
		for (int j = 0; j < col; j++){
			cout << map[i][j] << "\t\t";       //Ȼ�������ͼ�е�����
		}
		cout << endl;
	}
}
//������ʾ��Ϣʾ��
void PutInHint() {
	cout << "�밴����������д�С�����Զ���ĵ�ͼ�͵�ͼ���յ㣡" << endl;
	cout << "     ����ʾ����row: 7" << endl;
	cout << "               col: 8" << endl;
	cout << "     ��ͼʾ����  # # # # # # # #" << endl;
	cout << "                 # 0 # # # # # #" << endl;
	cout << "                 # 0 0 0 0 0 # #" << endl;
	cout << "                 # # 0 # 0 # # #" << endl;
	cout << "                 # # 0 # 0 # # #" << endl;
	cout << "                 # # # # 0 0 # #" << endl;
	cout << "                 # # # # # # # #" << endl;
	cout << "˵������Ĭ�ϵ�ͼ������ǣ�1,1����" << endl;
	cout << "      ���ڵ�ͼ�С�#����ʾ��·��ͨ����0����ʾ����ͨ�С�" << endl;
	cout << "      ������ĵ�ͼĬ�����ܶ�Ϊ��#����" << endl;
}
int main() {	
	
	//����������ʾ
	PutInHint();
	
	//�����ͼ�����У���ͼ�Ļ�����Ϣ���Լ��յ������
	cout <<endl<< "�������ͼ�����У���С������100��:" << endl;
	cout << "row:"; cin >> row; 
	cout << "col:"; cin >> col; cout << endl;
	cout << endl;
	cout << "�밴������ʾ�������ͼ��" << endl;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cin >> map[i][j];
		}
	}
	cout << "�������յ��������꣺" << endl;
	cout << "row:"; cin >> exitPos.x;
	cout << "col:"; cin >> exitPos.y; cout << endl;
	
	//Ȼ�������ͼ�˶�
	cout << "������ĵ�ͼ�ǣ�" << endl;
	printMapRoute();
	cout << "�յ����꣺" << exitPos.x << "  " << exitPos.y << endl;
	cout << "��������ʼ����Թ�·�ߣ�" << endl << endl;
	system("pause");
	
	//�洢������ʻ·���������ʼ��
	r = new(nothrow)Node;
	if (r == NULL) {
		cout << "�ڴ�����ʧ�ܣ�" << endl;
		exit(0);
	}
	r->head = NULL;
	r->next = NULL;
	r->x = 1;       //ͷ����ʾ��㣬����ڣ�1,1��
	r->y = 1;
	r1 = r;         //r1��ʾ��ǰ�ڵ�

	//��������visitΪ1����ʾ���߹���
	visited[1][1] = 1;
	//�ԣ�1,1��Ϊ�����������������
	dfs(1, 1);
	r1 = r;

	//����ҵ��ˣ����Ҳ�����·
	if (finish == 1 && flag == 1) {
		map[exitPos.x][exitPos.y] = 'x';
		//��ӡ��Ǻ�·�ߵĵ�ͼ
		printMapRoute();
		r = r1;
		//�����洢·�ߵ�����������洢���������
		while (r->next) {
			cout << '<' << r->x << ',' << r->y << '>' << "--->";//��ӡ�������ڶ�������
			r = r->next;
		}
		//���һ����Ҫ������ӡ����Ϊ���һ�����治��Ҫ��ӡ��ͷ
		cout << '<' << exitPos.x << ',' << exitPos.y << '>' << endl;
	}

	//�ͷ��ڴ�
	Node* ptr = r,*p=ptr;
	while (ptr != NULL) {
		p = ptr;
		ptr = ptr->next;
		delete p;
	}

	system("pause");
	return 0;
}
