#include<iostream>
using namespace std;

//表示有向图的终点集合
struct Dest {
	int dest = 0;   //表示终点的节点序号
	int time = 0;  //表示从起点连接到这个点中间所需要的时间
	Dest* link = NULL;  //表示可以连接下一个与起点相连接的终点
};
//表示有向图的起始顶点
struct Node {
	int data = 0;        //记录这是哪一个顶点
	Dest* adj = NULL;   //连接与其相连的终点组成的链表
};

Node* NodeTable = NULL;   //邻接表(无序)
Node* NodeTableTopological = NULL;  //存放经过拓扑排序后的节点
int* inDegree = NULL;         //用于存放每个顶点的入度
int* Ve=NULL, * Vl=NULL;   //Ve表示事件最早可能开始的时间，是从源点到该点的最长路径长度
                                            //Vl表示事件最迟允许开始的时间
int e = 0, l = 0;                      //两者相等的时候表示关键活动
int n = 0,m=0;  //n是任务交接点的个数，m是子任务的数量
int start = 0, finish = 0, time = 0;//start是子任务开始的时间，end是该子任务结束的时间，time是完成该子任务需要的时间

//将起点为i，终点为j，权重为weight的边塞入邻接表中
void InserEdge(int i, int j, int w) {
	Dest* p = NULL;     //用于遍历，寻找链表的末尾
	//将输入的数据存入邻接表（出边表）中
	Dest* d = new Dest;
	d->dest = j;
	d->time = w;
	//将d放在插入到该项NodeTable的后面
	p = NodeTable[i].adj;
	if (p == NULL) {
		NodeTable[i].adj = d;
	}
	else {  //断开插入到后面
		d->link = p;
		NodeTable[i].adj = d;
	}
}
//输入
void Read() {
	while (1) {
		cin >> n >> m;          //输入交接点的个数和子任务的数量
		//判断n和m的合法性，如果输入不合法需要重新输入
		if (n * (n - 1) < m) {
			cout << "子任务个数大于可能的最大值！请重新输入交接点和子任务的数量！" << endl;
		}
		else
			break;
	}
	int num = n + 1;      //分配num个空间
	NodeTable = new Node[num];    //一共有n个顶点，所以给NodeTable分配n个节点的空间
	NodeTableTopological = new (nothrow)Node[num];
	inDegree = new(nothrow)int[num];
	Ve = new(nothrow) int[num];
	Vl = new(nothrow) int[num];
	if (!NodeTable || !NodeTableTopological || !inDegree || !Ve || !Vl) {
		cout << "动态内存申请失败！" << endl;
		exit(0);
	}
	fill(inDegree, inDegree + n+1, 0);   //给入度全部初始化为0
	//为了避免产生C8636的警告，所以用指针的方式赋值
	for (int i = 1; i <= n; i++) {
		(NodeTable+i)->data =i;   //该节点的编号
		*(inDegree+i) = 0;
		*(Ve+i) = 0;                            //初始化为0
	}
	for (int i = 0; i < m; i++) {      //根据子任务的数量依次输入每个子任务开始的节点，结束的节点和持续的时间
		cin >> start >> finish >> time;
		inDegree[finish]++;
		InserEdge(start, finish, time);    //将这条边加入到邻边图中
	}
}
//进行拓扑排序并计算Ve和Vl
int CaculateVeVl() {
	int top = -1;
	//先扫描初始状态下入度为0的顶点
	for (int i = 1; i <= n; i++) {
		if (inDegree[i] == 0) {
			inDegree[i] = top; 
			top = i;     //将栈顶指针指向这个入度为零的顶点
		}
	}
	int Max = 0;   //用来存Ve中的最大值
	int topo = 1;
	//进行拓扑排序，并计算出Ve以及最长路径
	for (int i = 1; i <= n; i++) {
		if (top == -1) {    //说明有有向环
			return 0;
		}
		else {   //否则将栈中元素输出
			int j = top;
			top = inDegree[top];   //退栈
			//cout << j << endl;      //输出
			NodeTableTopological[topo++] = NodeTable[j];  //按照拓扑排序的顺序存入拓扑排序后的数组
			//然后扫描该顶点的出边表，将出边表上的顶点入度-1，表示这条边没了
			//同时更新其连接的所有点的Ve
			Dest*p = NodeTable[j].adj;
			while (p) {
				int k = p->dest;      //记下终点节点的序号
				Ve[k] = max(Ve[k], Ve[j] + p->time);  //计算Ve的值
				Max = max(Max, Ve[k]);
				if (--inDegree[k] == 0) {   //将该顶点的入度减少1，并判断是否为0
					//如果是0，将该顶点入栈
					inDegree[k] = top;
					top = k;
				}
				p = p->link;
			}
		}
	}

	//接下来计算Vl，首先将Vl中的值全部赋值为最大值
	for (int i = 1; i <= n; i++) {
		Vl[i] = Max;
	}
	Dest* p = NULL; //用于遍历每一个节点的出边表
	int k = 0,s=0;        
	for (int i = n - 1; i >= 1; i--) {
		s = NodeTableTopological[i].data;
		p = NodeTableTopological[i].adj;
		while (p) {
			k = p->dest;    //利用k存储其连接的终点的序号
			Vl[s] = min(Vl[k] - p->time, Vl[s]);
			p = p->link;      //转向下一个连接的节点
		}
	}
	//返回Ve中的最大值，由于输入的网络中的终点未必是最后一个节点，所以不能草草返回
	/*for (int i = 1; i <= n; i++) {
		cout << Ve[i] << " " << Vl[i] << endl;
	}*/
	return Max;
}
//求关键路径
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
//释放申请的动态内存
void Clear() {
	if (NodeTable) {
		//将每一条边依次释放
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
	if (res) {   //输出最短时间
		cout << res << endl;
		CriticalPath();
	}
	else {      //有回路，不可行的方案调度
		cout << 0 << endl;
	}
	Clear();   //释放内存
	system("pause");
	return 0;
}