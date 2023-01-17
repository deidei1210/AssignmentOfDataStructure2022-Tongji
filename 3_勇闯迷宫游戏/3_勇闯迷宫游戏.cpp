#include<iostream>
#include <stdio.h>
#define N 100
using namespace std;
void dfs(int x, int y);

//用于定义坐标
struct Position {
	int x;
	int y;
};
//表示迷宫上的节点

//表示双向链表
struct Node {
	int x;             //迷宫上的坐标
	int y;
	Node* next;       //表示下一个节点
	Node* head;       //表示通往此处的上一个节点
};
Node* r=NULL, * r1=NULL, * r2=NULL;

//手工定义地图
char map[N][N] = {};
//表示我的迷宫的行列个数
int row = 0;
int col = 0;
//表示行进的四个方向
const Position direction[4] = { {0,1},{0,-1},{-1,0},{1,0} };
//出口的坐标
Position exitPos = {};
//判断是否到达终点
int finish = 0;
//记录是否遍历过了
bool visited[N][N] = {};
bool flag = 1;
//深度优先搜索
void dfs(int x, int y) {
	//找到出口，返回
	if (x == exitPos.x && y == exitPos.y) {
		finish = 1;
		return;
	}
	//还没找到出口，继续遍历所有方向
	for (int i = 0; i < 4; i++) {
		//如果这个点既是一条通路，又是没有访问过的，那就走他
		if (map[x + direction[i].x][y + direction[i].y] == '0' &&visited[x + direction[i].x][y + direction[i].y] == 0) {
			//记录已经访问过了
			visited[x + direction[i].x][y + direction[i].y] = 1;
			//到达下一个位置，建立新的节点
			r2 = new(nothrow)Node;
			if (!r2) {
				cout << "内存申请失败！" << endl;
				exit(0);
			}
			r2->next = NULL;
			r2->x = x + direction[i].x;
			r2->y = y + direction[i].y;
			//前一个节点记做r1，后一个节点记做r2
			r2->head = r1;
			r1->next = r2;
			r1 = r2;
			//赋值完之后，让此时的前一个节点变成当前节点，从而继续
			dfs(x + direction[i].x, y + direction[i].y);
			if (finish == 1) {
				return;
			}
		}
	}

	//如果上面的一个都没有执行到，也就是说当前节点不是终点，而且是死路一条，那就执行下面的语句
	if (r1->head) {//如果当前节点有前一个节点
		r1 = r1->head;//那就挪到前一个节点

		//先将后面的空间全部都释放
		Node* ptr = r1->next,*p=ptr;
		while (ptr != NULL) {
			p = ptr;
			ptr = ptr->next;
			delete p;
		}

		r1->next = NULL;//然后将后面的节点断掉
		dfs(r1->x, r1->y);//在当前节点重新开始遍历
	}
	else {
		cout << "ERROR" << endl;
		finish = 1;
		flag = 0;
		return;
	}
	return;
}
//用于打印地图
void printMapRoute()
{
	cout << "迷宫地图：" << endl;
	//给路径上需要走到的地方全部赋值为x
	while (r) {
		map[r->x][r->y] = 'x';
		r = r->next;
	}
	//先将表头打印出来
	for (int i = 0; i < col; i++){
		cout << '\t' << i << "列" << '\t';
	}
	cout << endl;
	//把表头打印完之后换一行开始打印数据
	for (int i = 0; i < row; i++){
		cout << i << "行" << '\t';            //每换一行都先输出行数
		for (int j = 0; j < col; j++){
			cout << map[i][j] << "\t\t";       //然后输出地图中的内容
		}
		cout << endl;
	}
}
//输入提示信息示范
void PutInHint() {
	cout << "请按照输入的行列大小输入自定义的地图和地图的终点！" << endl;
	cout << "     输入示例：row: 7" << endl;
	cout << "               col: 8" << endl;
	cout << "     地图示例：  # # # # # # # #" << endl;
	cout << "                 # 0 # # # # # #" << endl;
	cout << "                 # 0 0 0 0 0 # #" << endl;
	cout << "                 # # 0 # 0 # # #" << endl;
	cout << "                 # # 0 # 0 # # #" << endl;
	cout << "                 # # # # 0 0 # #" << endl;
	cout << "                 # # # # # # # #" << endl;
	cout << "说明：①默认地图的起点是（1,1）。" << endl;
	cout << "      ②在地图中“#”表示此路不通，“0”表示可以通行。" << endl;
	cout << "      ③输入的地图默认四周都为“#”。" << endl;
}
int main() {	
	
	//给出输入提示
	PutInHint();
	
	//输入地图的行列，地图的基本信息，以及终点的坐标
	cout <<endl<< "请输入地图的行列（大小不超过100）:" << endl;
	cout << "row:"; cin >> row; 
	cout << "col:"; cin >> col; cout << endl;
	cout << endl;
	cout << "请按照输入示例输入地图：" << endl;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cin >> map[i][j];
		}
	}
	cout << "请输入终点行列坐标：" << endl;
	cout << "row:"; cin >> exitPos.x;
	cout << "col:"; cin >> exitPos.y; cout << endl;
	
	//然后输出地图核对
	cout << "您输入的地图是：" << endl;
	printMapRoute();
	cout << "终点坐标：" << exitPos.x << "  " << exitPos.y << endl;
	cout << "接下来开始输出迷宫路线！" << endl << endl;
	system("pause");
	
	//存储整个行驶路径的链表初始化
	r = new(nothrow)Node;
	if (r == NULL) {
		cout << "内存申请失败！" << endl;
		exit(0);
	}
	r->head = NULL;
	r->next = NULL;
	r->x = 1;       //头结点表示起点，起点在（1,1）
	r->y = 1;
	r1 = r;         //r1表示当前节点

	//先令起点的visit为1，表示其走过了
	visited[1][1] = 1;
	//以（1,1）为起点进行深度优先搜索
	dfs(1, 1);
	r1 = r;

	//如果找到了，并且不是死路
	if (finish == 1 && flag == 1) {
		map[exitPos.x][exitPos.y] = 'x';
		//打印标记好路线的地图
		printMapRoute();
		r = r1;
		//遍历存储路线的链表，并将其存储的坐标输出
		while (r->next) {
			cout << '<' << r->x << ',' << r->y << '>' << "--->";//打印到倒数第二个即可
			r = r->next;
		}
		//最后一个需要单独打印，因为最后一个后面不需要打印箭头
		cout << '<' << exitPos.x << ',' << exitPos.y << '>' << endl;
	}

	//释放内存
	Node* ptr = r,*p=ptr;
	while (ptr != NULL) {
		p = ptr;
		ptr = ptr->next;
		delete p;
	}

	system("pause");
	return 0;
}
