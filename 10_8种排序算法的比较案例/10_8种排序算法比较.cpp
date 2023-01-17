#include<iostream>
#include<iomanip>
#include<ctime>
#include<cstdlib>
using namespace std;
clock_t startTime, endTime;//用于记录开始排序的时间和排序完成的时间
int sum = 100000;//默认总数
long long TempTime[8] = {};//用于记录在排序过程中交换的总次数

void BubbleSort(int arr[], int len);  //冒泡排序
void SelectSort(int arr[], int len);  //选择排序
void InsertSort(int arr[], int k);   //直接插入排序
void ShellSort(int arr[], int length);//希尔排序
void QuickSort(int arr[], int begin, int end);//快速排序
void HeapSort(int arr[], int size);//堆排序
void MergeSort(int* arr, int x, int y, int* b);//归并排序
void sort_r(int data[], int n); //基数排序


//冒泡排序
void BubbleSort(int arr[], int len) {
	int i, j, temp;
	for (i = 0; i < len - 1; i++)
		for (j = 0; j < len - 1 - i; j++)
			//每一次比较相邻的两个元素，如果左边的大于右边的就交换，所以每一次排下来最大的都在每次排序的那一块的最右边
			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				TempTime[0]++;  //增加一次交换
			}
}

//用于交换两个数
void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

//输出比较小的那一个
int min(int a, int b) {
	return a < b ? a : b;
}

//辅助函数，求数据的最大位数
int maxbit(int data[], int n){
	int maxData = data[0];              ///< 最大数
	/// 先求出最大数，再求其位数，这样有原先依次每个数判断其位数，稍微优化点。
	for (int i = 1; i < n; ++i) {
		if (maxData < data[i])
			maxData = data[i];
	}
	int d = 1;
	int p = 10;
	while (maxData >= p) {
		maxData /= 10;
		++d;
	}
	return d;
}

//选择排序
void SelectSort(int arr[], int len) {
	int i, j;
	for (i = 0; i < len - 1; i++) {
		int min = i;     //每一次都先假设最小的是遍历到的第i的元素，也就是接下来待排序列的第一个元素
		for (j = i + 1; j < len; j++)     //遍历未排序的元素
			if (arr[j] < arr[min]) {    //找到未排序序列中目前最小值
				min = j;    //记录最小值
			}
		//如果发现此时最小的元素不是第i个了
		if (i != min) {
			//然后交换最小的元素和当前序列的第一个元素的位置
			swap(arr[i], arr[min]);
			TempTime[1]++;
		}
	}
}

//插入排序
void InsertSort(int arr[], int k) {
	int i, j, min = 0;
	//默认第一个元素是已经被排序的，所以循环从第二个元素开始
	for (i = 1; i < k; i++) {
		if (arr[i] < arr[i - 1]) {//如果发现了后面一个元素比当前元素小
			min = arr[i];    //那就暂存在min中
			//然后从这个元素开始往前遍历，直到找到一个比他小或者与其相等的数arr[j]
			for (j = i - 1; j >= 0 && arr[j] > min; j--) {
				arr[j + 1] = arr[j];    //将还没找到这个位置时遇见的元素都向后挪一个位置
				TempTime[2]++;   //每交换一次，就要增加一个次数
			}
			arr[j + 1] = min;//将min插入到找到的位置
			TempTime[2]++;//交换次数又增加1
		}
	}
}

//希尔排序
void ShellSort(int arr[], int n) {
	int gap = n;    //假设每一次都将数组中距离为gap的数分为一组
	while (gap > 1) {
		//每次对gap折半操作，使得距离越来越小
		gap = gap / 2;
		for (int i = 0; i < n - gap; ++i) {
			int end = i;
			int tem = arr[end + gap];//然后将距离为gap的两个元素大小进行比较
			while (end >= 0) {  //为的是将所有相距gap的元素都进行一遍插入排序相当于比如4,7,3,1,2,2,0,6,7，如果gap=3，那么所有相距3的元素都得是有序的
				if (tem < arr[end]) {  //如果后面的元素比前面的小
					arr[end + gap] = arr[end];
					TempTime[3]++;//此处进行了一次交换，所以加1
					end -= gap;  //将end减少gap看看前面是否还有大于tem的元素
				}
				else {
					break;
				}
			}
			arr[end + gap] = tem;  //插入到在这个序列中他此时该在的位置
			TempTime[3]++;//此处进行了一次交换，所以加1
		}
	}
}

//快速排序
void QuickSort(int arr[], int begin, int end) {
	if (begin > end)
		return;
	int tmp = arr[begin];      //每次都将第一个元素视作基准数
	int i = begin;             //表示哨兵i一开始位于开始的位置
	int j = end;               //表示哨兵j一开始位于结尾的位置
	while (i != j) {           //当他们还没有相遇的时候
		while (arr[j] >= tmp && j > i)  //如果满足右边的数大于基准数，且哨兵j依旧在哨兵i的右边
			j--;                         //那么哨兵j继续向前走
		while (arr[i] <= tmp && j > i)  //如果满足左边的数小于基准数，且哨兵j依旧在哨兵i的右边
			i++;                        //那么哨兵i就继续向后走
		if (j > i) {                   //依然是在哨兵j在哨兵i右边的前提下
			int t = arr[i];            //一旦发现两个异常的元素就交换位置
			arr[i] = arr[j];
			arr[j] = t;
			TempTime[4]++;
		}
	}
	arr[begin] = arr[i];             //否则一旦哨兵i和哨兵j相遇，那就将此时首元素变成第i个元素
	arr[i] = tmp;                    //第i个元素变成基准数
	TempTime[4]++;
									 //如此便使得基准数左边都是小于基准数的数，右边都是大于基准数的数
	QuickSort(arr, begin, i - 1);   //对左半边进行该操作
	QuickSort(arr, i + 1, end);    //右半边也作此操作
}


/*void MaxHeapify(int arr[], int start, int end) {
	// 建立父节点指标和子节点指标
	int dad = start;
	int son = dad * 2 + 1;
	while (son <= end) { // 防止越界
		if (son + 1 <= end && arr[son] < arr[son + 1]) // 先比较两个子节点大小
			son++;//如果后面一个子节点更大，那就让son加一取后面一个孩子节点
		if (arr[dad] > arr[son]) // 如果父节点大于子节点代表调整完毕，直接跳出函数
			return;
		else { // 否则交换父子内容再继续子节点和孙节点比较
			swap(arr[dad], arr[son]);
			TempTime[5]++;
			dad = son;
			son = dad * 2 + 1;//找到孙子节点
		}
	}
}

//堆排序
void HeapSort(int arr[], int len){
	//在进行堆排序的时候，首先将要排序的数组视作是一个完全二叉树的形式
	// 初始化，i从根节点开始调整
	for (int i = len / 2 - 1; i >= 0; i--)
		MaxHeapify(arr, i, len - 1);
	// 先将第一个元素和已经排好的元素前一位做交换，再从新调整(刚调整的元素之前的元素)，直到排序完毕
	for (int i = len - 1; i > 0; i--) {
		swap(arr[0], arr[i]);
		TempTime[5]++;
		MaxHeapify(arr, 0, i - 1);
	}
}*/
//作用是辅助堆排序的主函数，将较大的节点换到父节点上
void Down(int arr[], int i, int n) { // 最后结果就是大顶堆
	int parent = i;                    // 父节点下标
	int child = 2 * i + 1;            // 子节点下标
	while (child < n) {
		if (child + 1 < n && arr[child] < arr[child + 1]) { // 判断子节点那个大，大的与父节点比较
			child++;
		}
		if (arr[parent] < arr[child]) { // 判断父节点是否小于子节点
			int key = arr[parent];
			arr[parent] = arr[child];
			arr[child] = key;
			TempTime[5]++;           //执行了一次交换
			parent = child;                 // 子节点下标 赋给 父节点下标
		}
		child = child * 2 + 1; // 换行，比较下面的父节点和子节点
	}
}
//堆排序
void HeapSort(int arr[], int size) {
	//初始化大顶堆
	for (int i = size / 2 - 1; i >= 0; i--) { // 倒数第二排开始, 创建大顶堆，必须从下往上比较
		Down(arr, i, size);                 // 否则有的不符合大顶堆定义
	}
	for (int i = size - 1; i > 0; i--) {
		int key = arr[0];
		arr[0] = arr[i];
		arr[i] = key;	// 因为只有array[0]改变，其它都符合大顶堆的定义，所以可以从上往下重新建立
		TempTime[5]++;     //执行了一次交换
		Down(arr, 0, i); // 重新建立大顶堆
	}
}


//归并排序（分治的思想）
void merge(int* arr, int low, int mid, int high, int* b) {
	int i = low, j = mid + 1, k = low;
	while (i <= mid && j <= high) {//相当于是将数组从中间分成两半，分成两个部分
		//每次从两个数列中选择比较小的插入到b数组中，然后指向下一位
		b[k++] = arr[j] < arr[i] ? arr[j++] : arr[i++];
		TempTime[6]++;
	}
	//将多余的部分加进b中
	while (i <= mid) {
		b[k++] = arr[i++];
	}
	while (j <= high) {
		b[k++] = arr[j++];
	}
	for (int i = low; i <= high; i++)
		arr[i] = b[i];
}
void MergeSort(int* arr, int x, int y, int* b) {   //用于分割
	if (x >= y)
		return;
	int mid = (x + y) / 2;
	MergeSort(arr, x, mid, b);
	MergeSort(arr, mid + 1, y, b);
	merge(arr, x, mid, y, b);
}

//基数排序
void sort_r(int data[], int n)
{
	int d = maxbit(data, n);
	int* tmp = new int[n];
	int* count = new int[10]; //计数器
	int i, j, k;
	int radix = 1;
	for (i = 1; i <= d; i++) { //进行d次排序
		for (j = 0; j < 10; j++)
			count[j] = 0; //每次分配前清空计数器
		for (j = 0; j < n; j++) {
			k = (data[j] / radix) % 10; //统计每个桶中的记录数
			count[k]++;
		}
		for (j = 1; j < 10; j++)
			count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶
		for (j = n - 1; j >= 0; j--) { //将所有桶中记录依次收集到tmp中
			k = (data[j] / radix) % 10;
			tmp[count[k] - 1] = data[j];
			count[k]--;
		}
		for (j = 0; j < n; j++) //将临时数组的内容复制到data中
			data[j] = tmp[j];
		radix = radix * 10;
	}
	delete[]tmp;
	delete[]count;
}



//菜单
void menu() {
	cout << "**                排序算法比较              **" << endl;
	cout << "==============================================" << endl;
	cout << "**                1--冒泡排序               **" << endl;
	cout << "**                2--选择排序               **" << endl;
	cout << "**                3--直接插入排序           **" << endl;
	cout << "**                4--希尔排序               **" << endl;
	cout << "**                5--快速排序               **" << endl;
	cout << "**                6--堆排序                 **" << endl;
	cout << "**                7--归并排序               **" << endl;
	cout << "**                8--基数排序               **" << endl;
	cout << "**                9--退出                   **" << endl;
	cout << "==============================================" << endl;
	cout << endl;
	cout << "请输入要产生的随机数的个数:";
	cin >> sum;
}

//让数组随机产生sum个数
void show_rand(int* arr) {
	for (int i = 0; i < sum; i++) {
		arr[i] = rand() % 10000;
	}
}

int arr[100001] = {}, a[100001] = {};

int main() {
	//显示菜单，并且输入sum的值
	menu();
	//int arr[100001], a[100001];
	srand((unsigned)time(NULL));//用系统时间产生随机数种子
	show_rand(a);    //随机生成sum个数，存储在a数组中
	double time[8] = { 0 }; //用于记录每一次运行排序所需要的时间
	int c = 0;
	while (1) {
		for (int i = 0; i < sum; i++) {
			arr[i] = a[i];
		}
		cout << endl << "请选择排序方法：";
		cin >> c;

		if (c == 1) {
			//将随机生成的未排序的数组原封不动赋值给arr以待排序
			startTime = clock();
			BubbleSort(arr, sum);
			endTime = clock();
			time[0] = (double)endTime - (double)startTime;
			cout << "冒泡排序所需时间：" << time[0] << endl;
			cout << "冒泡排序所用交换次数：" << TempTime[0] << endl;
		}
		else if (c == 2) {
			startTime = clock();
			SelectSort(arr, sum);
			endTime = clock();
			time[1] = (double)endTime - (double)startTime;
			cout << "选择排序所需时间：" << time[1] << endl;
			cout << "选择排序所用交换次数：" << TempTime[1] << endl;
		}
		else if (c == 3) {
			startTime = clock();
			InsertSort(arr, sum);
			endTime = clock();
			time[2] = (double)endTime - (double)startTime;
			cout << "直接插入排序所需时间：" << time[2] << endl;
			cout << "直接插入排序所用交换次数：" << TempTime[2] << endl;
		}
		else if (c == 4) {
			startTime = clock();
			ShellSort(arr, sum);
			endTime = clock();
			time[3] = (double)endTime - (double)startTime;
			cout << "希尔排序所需时间：" << time[3] << endl;
			cout << "希尔排序所用交换次数：" << TempTime[3] << endl;
		}
		else if (c == 5) {
			startTime = clock();
			QuickSort(arr, 0, sum - 1);
			endTime = clock();
			time[4] = (double)endTime - (double)startTime;
			cout << "快速排序所需时间：" << time[4] << endl;
			cout << "快速排序所用交换次数：" << TempTime[4] << endl;
		}
		else if (c == 6) {
			startTime = clock();
			HeapSort(arr, sum);
			endTime = clock();
			time[5] = (double)endTime - (double)startTime;
			cout << "堆排序所需时间：" << time[5] << endl;
			cout << "堆排序所用交换次数：" << TempTime[5] << endl;
		}
		else if (c == 7) {
			startTime = clock();
			int* b = new int[sum];   //在归并排序中需要一个b数组来当中间量
			MergeSort(arr, 0, sum - 1, b);
			endTime = clock();
			time[6] = (double)endTime - (double)startTime;
			cout << "归并排序所需时间：" << time[6] << endl;
			cout << "归并排序所用比较次数：" << TempTime[6] << endl;
			delete[]b;
		}
		else if (c == 8) {
			startTime = clock();
			sort_r(arr, sum);
			endTime = clock();
			time[7] = (double)endTime - (double)startTime;
			cout << "基数排序所需时间：" << time[7] << endl;
			cout << "基数排序所用交换次数：" << TempTime[7] << endl;
		}
		else if (c == 9) {
			break;
		}
		else {
			cout << "输入错误，请重新输入！" << endl;
		}
	}
	return 0;

}