#define MAX 0x3f3f3f3f
#include<iostream>

using namespace std;

struct Cost {
	int cost = MAX;  //表示距离（初始值都给的是最大值）
	int a = 0;       //表示距离的一个起点
	int b = 0;       //表示距离的另一个起点
};

int NodeNum = 0;//表示电网中顶点的总个数
char* NodeName = NULL;//定义一个字符数组，用来存储字符的名称
int** SideCost=NULL;    //定义一个二维数组用于存储两个指定节点之间架设电网的花费
int* vis=NULL;  //用于判断该点是否已经被访问过
Cost* NodeMinCost=NULL;  //用来存当前节点之后更新的最小距离
Cost* method=NULL;       //一个用来存储最小生成树方案的链表
long long sum = 0;         //最小生成树的权值之和

void menu() {
	cout << "**           电网造价模拟系统          **" << endl;
	cout << "=========================================" << endl;
	cout << "**          请选择要执行的操作         **" << endl;
	cout << "**          A---创建电网顶点           **" << endl;
	cout << "**          B---添加电网的边           **" << endl;
	cout << "**          C---构建最小生成树         **" << endl;
	cout << "**          D---显示最小生成树         **" << endl;
	cout << "**          E---退出程序               **" << endl;
	cout << "=========================================" << endl;
}
//创建电网节点
void CreateMatrixNode() {
	cout << "请输入顶点的个数:";
	while (1) {
		cin >> NodeNum;
		if (NodeNum <= 1) {
			cout << "顶点太少，不足以构成电网！请重新输入！" << endl;
		}
		else
			break;
	}
	NodeName = new char[NodeNum];    //给存储节点的指针按需分配存储顶点名称的空间	
	cout << "请依次输入各顶点的名称:" << endl;
	for (int i = 0; i < NodeNum; i++) {
		cin >> NodeName[i];
	}
}
//定位一个字符是否是我输入的顶点，并返回其位置
int Location(char c) {
	for (int i = 0; i < NodeNum; i++) {
		if (c == NodeName[i]) {
			return i;
		}
	}
	return -1;
}
//将每两个点之间的花费存入SideCost数组之中
int  SaveToArray(char node1, char node2, int cost) {
	int n1 = -1,n2 = -1;   //n1表示node1是NodeName中第n1个顶点，n2表示node2是NodeName中第n2个顶点
	int flag = 0;           //用来记录是否已经找到了这两个节点
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
		}//如果两个都找到了，那就退出
	}
	if (flag) {
		if (n1 == n2)
			return 2;
		SideCost[n1][n2] = min(SideCost[n1][n2], cost);       //取最小值
		SideCost[n2][n1] = min(SideCost[n2][n1], cost);
	}
	//cout << "此时n1为" << n1 << ",n2为" << n2 << endl;
	return flag;
}
//添加电网的边
void AddMatrixSide() {
	if (NodeNum == 0) {
		cout << "请先构建顶点！" << endl;
		return;
	}
	//如果此时SideCost还未分配空间
	if (SideCost == NULL) {
		//给存储两顶点之间所连路线架设电网所需花费的二维指针按需分配内存
		SideCost = new int* [NodeNum];
		for (int i = 0; i < NodeNum; i++) {
			SideCost[i] = new int[NodeNum];
			//给这个二维数组赋值，暂且全部为最大值
			for (int j = 0; j < NodeNum; j++) {
				SideCost[i][j] = MAX;
			}
		}
	}
	else {    //如果已经分配过空间，那么只需要直接把每一项都回归初始的大小即可，然后下面重新输入
		for (int i = 0; i < NodeNum; i++) {
			//给这个二维数组赋值，暂且全部为最大值
			for (int j = 0; j < NodeNum; j++) {
				SideCost[i][j] = MAX;
			}
		}
	}
	//如果之前执行过生成最小生成树的操作，那么这些需要全部清零，因为一旦进行到这边就是要按照之前输入的节点重新输入所有边的权重然后构成新的最小生成树
	if (vis && method && NodeMinCost) {
			delete[]vis;
			vis = NULL;
			delete[]NodeMinCost;
			NodeMinCost = NULL;
			delete[]method;
			method = NULL;
			sum = 0;
	}
	int MaxSideNum = NodeNum * (NodeNum - 1) / 2;  //边的最大条数，下面添加的边数不能超过这个数量
	char node1, node2; //表示输入的两个节点
	int count = 0;//用于记录输入的边数
	int cost = 0;  //表示下面要输入的这两点之间架设电网的费用
	int flag = 0; //用于记录输入的字符是否都是节点
	cout << "请输入两个顶点及该两点之间架设电网的费用(如果输入node1或者node2有一个不是电网中的节点就停止输入):" << endl;
	while (1) {
		cin >> node1 >> node2 >> cost;
		flag=SaveToArray(node1, node2, cost);     //将输入的节点和花费存入数组（主要是要将节点转换成数组下标）
		if (!flag) {     //说明建立边的过程结束
			if (count >= NodeNum - 1) {
				cout << "所有边输入完毕!" << endl;
				break;
			}
			else {
				cout << "输入的边的个数太少，不足以使得所有顶点连通！请继续输入！" << endl;
			}
		}
		else if(flag==1){
			count++;//说明建立边成功，增加一条边
			if (count >= MaxSideNum) {   //如果已经到达最大边数
				cout << "已经到达最大可输入边数！所有边输入完毕！" << endl;
				break;
			}
		}
		else {
			cout << "输入的两个顶点相同！请重新输入！" << endl;
		}
	 }
}
//构建最小生成树
void Prim(){
	if (NodeNum == 0) {
		cout << "请先构建顶点！" << endl;
		return;
	}
	if (SideCost == NULL) {
		cout << "请先输入两个顶点之间修建电网的花费！" << endl;
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
		cout << "请输入起始顶点:";
		cin >> start;      //输入起始顶点
		//检查start是否是NodeName中的顶点，并定位出他是第几个节点
		LocationStart = Location(start);
		if (LocationStart == -1) {//说明没找到
			cout << "输入的起始顶点非电网中的顶点！请重新输入！" << endl;
		}
		else
			break;
	}
	//接下来开始利用Prim生成最小生成树
	NodeMinCost[LocationStart].cost = 0;
	// 一共有 n 个点,就需要 遍历 n 次,每次寻找一个权值最小的点,记录其下标
	for (int i = 0; i < NodeNum; i++) {
		int cur = -1;
		for (int j = 0; j < NodeNum; j++) {
			//如果当前这个点还没有被访问过，并且cur还未指向任何一个节点或者到当前指向的节点的距离不如新节点花费更少
			if (!vis[j] && (cur == -1 || NodeMinCost[j].cost < NodeMinCost[cur].cost)) {
				cur = j;     //那么就让当前第i个节点指向第j个节点，也就是把要连接的那个点cur变成j
			}
		}
		// 如果出现这种情况，说明无法构成最小生成树，因为输入的图本身就不存在使得所有的点连通的路线
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
			cout << "无法生成最小生成树！请返回B选项使得输入的图能使得所有点连通！" << endl;
			return;
		}
		if (cur != -1) {
			//在总花费上加上当前筛选出的花费最小值
			sum += NodeMinCost[cur].cost;
			//标记上这个点以=已经到达访问过了(防止一个节点被同时访问两次是为了避免生成环)
			vis[cur] = 1;
			if (i != 0) {
				//存储此时的方案
				method[c++] = NodeMinCost[cur]; 
			}
		}
		// 只更新还没有找到的最小权值
		for (int k = 0; k < NodeNum; k++) {
			if (!vis[k] && cur != -1) {
				//更新从当前所在的这个点到所有已经走过的点的最小距离
				//dist[k].length = min(dist[k].length, a[cur][k]);
				if (NodeMinCost[k].cost > SideCost[cur][k]) {
					NodeMinCost[k].cost = SideCost[cur][k];
					NodeMinCost[k].a = cur;
					NodeMinCost[k].b = k;
				}
			}
		}
	}
	cout << "生成Prim最小生成树！" << endl;
}
//显示最小生成树
void Print() {
	if (NodeNum == 0) {
		cout << "请先构建顶点！" << endl;
		return;
	}
	if (SideCost == NULL) {
		cout << "请先输入两个顶点之间修建电网的花费！" << endl;
		return;
	}
	if (method == NULL) {
		cout << "请先生成最小二叉树！" << endl;
		return;
	}

	cout << "最小生成树的顶点及边为：" << endl << endl;
	//打印method
	//method有NodeNum-1条边
	for (int i = 0; i < NodeNum-2; i++) {
		cout << NodeName[method[i].a] << "-(" << method[i].cost << ")->" << NodeName[method[i].b]<<"        ";
	}
	//最后一条边单独输出从而避免最后有多余的空格
	cout << NodeName[method[NodeNum - 2].a] << "-(" << method[NodeNum - 2].cost << ")->" << NodeName[method[NodeNum - 2].b]<<endl;
	//输出最小花费
	cout << "最低造价为：" << sum << endl;
	return;
}
//用于释放分配的内存或者清零，从而为下一轮做准备
void Clear() {
	if (NodeName) {
		delete[]NodeName; //释放存储顶点名称的一维指针
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
	NodeNum = 0;   //使得电网中顶点的总个数清零
	sum = 0;
}
char choice = 0;  //用来存储用户的选择
int main() {
	menu();  //输出菜单

	while (1) {
		cout << endl << "请选择操作:";     //每一次由用户选择其想要进行的操作
		cin >> choice;

		if (choice == 'A'||choice=='a') {       //创建电网节点
			Clear();        //每一次创建新的电网时都要先清空上一次的数据
			CreateMatrixNode();
		}
		else if (choice == 'B'||choice=='b') {//添加电网的边
			AddMatrixSide();
		}
		else if (choice == 'C'||choice=='c') {//构建最小生成树
			Prim();
		}
		else if (choice == 'D'||choice=='d') {//显示最小生成树
			Print();
		}
		else if (choice == 'E'||choice=='e') {  //退出程序
			cout << "欢迎下次使用！" << endl;
			Clear();        //释放申请的内存之后再退出程序
			break;
		}
		else {     //输入错误
			cout << "输入不符合要求，没有" << choice << "的选项！请重新输入！" << endl;
			continue;
		}
	}
	return 0;
}