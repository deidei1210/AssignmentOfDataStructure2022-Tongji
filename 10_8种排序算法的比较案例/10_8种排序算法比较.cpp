#include<iostream>
#include<iomanip>
#include<ctime>
#include<cstdlib>
using namespace std;
clock_t startTime, endTime;//���ڼ�¼��ʼ�����ʱ���������ɵ�ʱ��
int sum = 100000;//Ĭ������
long long TempTime[8] = {};//���ڼ�¼����������н������ܴ���

void BubbleSort(int arr[], int len);  //ð������
void SelectSort(int arr[], int len);  //ѡ������
void InsertSort(int arr[], int k);   //ֱ�Ӳ�������
void ShellSort(int arr[], int length);//ϣ������
void QuickSort(int arr[], int begin, int end);//��������
void HeapSort(int arr[], int size);//������
void MergeSort(int* arr, int x, int y, int* b);//�鲢����
void sort_r(int data[], int n); //��������


//ð������
void BubbleSort(int arr[], int len) {
	int i, j, temp;
	for (i = 0; i < len - 1; i++)
		for (j = 0; j < len - 1 - i; j++)
			//ÿһ�αȽ����ڵ�����Ԫ�أ������ߵĴ����ұߵľͽ���������ÿһ�����������Ķ���ÿ���������һ������ұ�
			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				TempTime[0]++;  //����һ�ν���
			}
}

//���ڽ���������
void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

//����Ƚ�С����һ��
int min(int a, int b) {
	return a < b ? a : b;
}

//���������������ݵ����λ��
int maxbit(int data[], int n){
	int maxData = data[0];              ///< �����
	/// ������������������λ����������ԭ������ÿ�����ж���λ������΢�Ż��㡣
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

//ѡ������
void SelectSort(int arr[], int len) {
	int i, j;
	for (i = 0; i < len - 1; i++) {
		int min = i;     //ÿһ�ζ��ȼ�����С���Ǳ������ĵ�i��Ԫ�أ�Ҳ���ǽ������������еĵ�һ��Ԫ��
		for (j = i + 1; j < len; j++)     //����δ�����Ԫ��
			if (arr[j] < arr[min]) {    //�ҵ�δ����������Ŀǰ��Сֵ
				min = j;    //��¼��Сֵ
			}
		//������ִ�ʱ��С��Ԫ�ز��ǵ�i����
		if (i != min) {
			//Ȼ�󽻻���С��Ԫ�غ͵�ǰ���еĵ�һ��Ԫ�ص�λ��
			swap(arr[i], arr[min]);
			TempTime[1]++;
		}
	}
}

//��������
void InsertSort(int arr[], int k) {
	int i, j, min = 0;
	//Ĭ�ϵ�һ��Ԫ�����Ѿ�������ģ�����ѭ���ӵڶ���Ԫ�ؿ�ʼ
	for (i = 1; i < k; i++) {
		if (arr[i] < arr[i - 1]) {//��������˺���һ��Ԫ�رȵ�ǰԪ��С
			min = arr[i];    //�Ǿ��ݴ���min��
			//Ȼ������Ԫ�ؿ�ʼ��ǰ������ֱ���ҵ�һ������С����������ȵ���arr[j]
			for (j = i - 1; j >= 0 && arr[j] > min; j--) {
				arr[j + 1] = arr[j];    //����û�ҵ����λ��ʱ������Ԫ�ض����Ųһ��λ��
				TempTime[2]++;   //ÿ����һ�Σ���Ҫ����һ������
			}
			arr[j + 1] = min;//��min���뵽�ҵ���λ��
			TempTime[2]++;//��������������1
		}
	}
}

//ϣ������
void ShellSort(int arr[], int n) {
	int gap = n;    //����ÿһ�ζ��������о���Ϊgap������Ϊһ��
	while (gap > 1) {
		//ÿ�ζ�gap�۰������ʹ�þ���Խ��ԽС
		gap = gap / 2;
		for (int i = 0; i < n - gap; ++i) {
			int end = i;
			int tem = arr[end + gap];//Ȼ�󽫾���Ϊgap������Ԫ�ش�С���бȽ�
			while (end >= 0) {  //Ϊ���ǽ��������gap��Ԫ�ض�����һ����������൱�ڱ���4,7,3,1,2,2,0,6,7�����gap=3����ô�������3��Ԫ�ض����������
				if (tem < arr[end]) {  //��������Ԫ�ر�ǰ���С
					arr[end + gap] = arr[end];
					TempTime[3]++;//�˴�������һ�ν��������Լ�1
					end -= gap;  //��end����gap����ǰ���Ƿ��д���tem��Ԫ��
				}
				else {
					break;
				}
			}
			arr[end + gap] = tem;  //���뵽���������������ʱ���ڵ�λ��
			TempTime[3]++;//�˴�������һ�ν��������Լ�1
		}
	}
}

//��������
void QuickSort(int arr[], int begin, int end) {
	if (begin > end)
		return;
	int tmp = arr[begin];      //ÿ�ζ�����һ��Ԫ��������׼��
	int i = begin;             //��ʾ�ڱ�iһ��ʼλ�ڿ�ʼ��λ��
	int j = end;               //��ʾ�ڱ�jһ��ʼλ�ڽ�β��λ��
	while (i != j) {           //�����ǻ�û��������ʱ��
		while (arr[j] >= tmp && j > i)  //��������ұߵ������ڻ�׼�������ڱ�j�������ڱ�i���ұ�
			j--;                         //��ô�ڱ�j������ǰ��
		while (arr[i] <= tmp && j > i)  //���������ߵ���С�ڻ�׼�������ڱ�j�������ڱ�i���ұ�
			i++;                        //��ô�ڱ�i�ͼ��������
		if (j > i) {                   //��Ȼ�����ڱ�j���ڱ�i�ұߵ�ǰ����
			int t = arr[i];            //һ�����������쳣��Ԫ�ؾͽ���λ��
			arr[i] = arr[j];
			arr[j] = t;
			TempTime[4]++;
		}
	}
	arr[begin] = arr[i];             //����һ���ڱ�i���ڱ�j�������Ǿͽ���ʱ��Ԫ�ر�ɵ�i��Ԫ��
	arr[i] = tmp;                    //��i��Ԫ�ر�ɻ�׼��
	TempTime[4]++;
									 //��˱�ʹ�û�׼����߶���С�ڻ�׼���������ұ߶��Ǵ��ڻ�׼������
	QuickSort(arr, begin, i - 1);   //�����߽��иò���
	QuickSort(arr, i + 1, end);    //�Ұ��Ҳ���˲���
}


/*void MaxHeapify(int arr[], int start, int end) {
	// �������ڵ�ָ����ӽڵ�ָ��
	int dad = start;
	int son = dad * 2 + 1;
	while (son <= end) { // ��ֹԽ��
		if (son + 1 <= end && arr[son] < arr[son + 1]) // �ȱȽ������ӽڵ��С
			son++;//�������һ���ӽڵ�����Ǿ���son��һȡ����һ�����ӽڵ�
		if (arr[dad] > arr[son]) // ������ڵ�����ӽڵ���������ϣ�ֱ����������
			return;
		else { // ���򽻻����������ټ����ӽڵ����ڵ�Ƚ�
			swap(arr[dad], arr[son]);
			TempTime[5]++;
			dad = son;
			son = dad * 2 + 1;//�ҵ����ӽڵ�
		}
	}
}

//������
void HeapSort(int arr[], int len){
	//�ڽ��ж������ʱ�����Ƚ�Ҫ���������������һ����ȫ����������ʽ
	// ��ʼ����i�Ӹ��ڵ㿪ʼ����
	for (int i = len / 2 - 1; i >= 0; i--)
		MaxHeapify(arr, i, len - 1);
	// �Ƚ���һ��Ԫ�غ��Ѿ��źõ�Ԫ��ǰһλ���������ٴ��µ���(�յ�����Ԫ��֮ǰ��Ԫ��)��ֱ���������
	for (int i = len - 1; i > 0; i--) {
		swap(arr[0], arr[i]);
		TempTime[5]++;
		MaxHeapify(arr, 0, i - 1);
	}
}*/
//�����Ǹ���������������������ϴ�Ľڵ㻻�����ڵ���
void Down(int arr[], int i, int n) { // ��������Ǵ󶥶�
	int parent = i;                    // ���ڵ��±�
	int child = 2 * i + 1;            // �ӽڵ��±�
	while (child < n) {
		if (child + 1 < n && arr[child] < arr[child + 1]) { // �ж��ӽڵ��Ǹ��󣬴���븸�ڵ�Ƚ�
			child++;
		}
		if (arr[parent] < arr[child]) { // �жϸ��ڵ��Ƿ�С���ӽڵ�
			int key = arr[parent];
			arr[parent] = arr[child];
			arr[child] = key;
			TempTime[5]++;           //ִ����һ�ν���
			parent = child;                 // �ӽڵ��±� ���� ���ڵ��±�
		}
		child = child * 2 + 1; // ���У��Ƚ�����ĸ��ڵ���ӽڵ�
	}
}
//������
void HeapSort(int arr[], int size) {
	//��ʼ���󶥶�
	for (int i = size / 2 - 1; i >= 0; i--) { // �����ڶ��ſ�ʼ, �����󶥶ѣ�����������ϱȽ�
		Down(arr, i, size);                 // �����еĲ����ϴ󶥶Ѷ���
	}
	for (int i = size - 1; i > 0; i--) {
		int key = arr[0];
		arr[0] = arr[i];
		arr[i] = key;	// ��Ϊֻ��array[0]�ı䣬���������ϴ󶥶ѵĶ��壬���Կ��Դ����������½���
		TempTime[5]++;     //ִ����һ�ν���
		Down(arr, 0, i); // ���½����󶥶�
	}
}


//�鲢���򣨷��ε�˼�룩
void merge(int* arr, int low, int mid, int high, int* b) {
	int i = low, j = mid + 1, k = low;
	while (i <= mid && j <= high) {//�൱���ǽ�������м�ֳ����룬�ֳ���������
		//ÿ�δ�����������ѡ��Ƚ�С�Ĳ��뵽b�����У�Ȼ��ָ����һλ
		b[k++] = arr[j] < arr[i] ? arr[j++] : arr[i++];
		TempTime[6]++;
	}
	//������Ĳ��ּӽ�b��
	while (i <= mid) {
		b[k++] = arr[i++];
	}
	while (j <= high) {
		b[k++] = arr[j++];
	}
	for (int i = low; i <= high; i++)
		arr[i] = b[i];
}
void MergeSort(int* arr, int x, int y, int* b) {   //���ڷָ�
	if (x >= y)
		return;
	int mid = (x + y) / 2;
	MergeSort(arr, x, mid, b);
	MergeSort(arr, mid + 1, y, b);
	merge(arr, x, mid, y, b);
}

//��������
void sort_r(int data[], int n)
{
	int d = maxbit(data, n);
	int* tmp = new int[n];
	int* count = new int[10]; //������
	int i, j, k;
	int radix = 1;
	for (i = 1; i <= d; i++) { //����d������
		for (j = 0; j < 10; j++)
			count[j] = 0; //ÿ�η���ǰ��ռ�����
		for (j = 0; j < n; j++) {
			k = (data[j] / radix) % 10; //ͳ��ÿ��Ͱ�еļ�¼��
			count[k]++;
		}
		for (j = 1; j < 10; j++)
			count[j] = count[j - 1] + count[j]; //��tmp�е�λ�����η����ÿ��Ͱ
		for (j = n - 1; j >= 0; j--) { //������Ͱ�м�¼�����ռ���tmp��
			k = (data[j] / radix) % 10;
			tmp[count[k] - 1] = data[j];
			count[k]--;
		}
		for (j = 0; j < n; j++) //����ʱ��������ݸ��Ƶ�data��
			data[j] = tmp[j];
		radix = radix * 10;
	}
	delete[]tmp;
	delete[]count;
}



//�˵�
void menu() {
	cout << "**                �����㷨�Ƚ�              **" << endl;
	cout << "==============================================" << endl;
	cout << "**                1--ð������               **" << endl;
	cout << "**                2--ѡ������               **" << endl;
	cout << "**                3--ֱ�Ӳ�������           **" << endl;
	cout << "**                4--ϣ������               **" << endl;
	cout << "**                5--��������               **" << endl;
	cout << "**                6--������                 **" << endl;
	cout << "**                7--�鲢����               **" << endl;
	cout << "**                8--��������               **" << endl;
	cout << "**                9--�˳�                   **" << endl;
	cout << "==============================================" << endl;
	cout << endl;
	cout << "������Ҫ������������ĸ���:";
	cin >> sum;
}

//�������������sum����
void show_rand(int* arr) {
	for (int i = 0; i < sum; i++) {
		arr[i] = rand() % 10000;
	}
}

int arr[100001] = {}, a[100001] = {};

int main() {
	//��ʾ�˵�����������sum��ֵ
	menu();
	//int arr[100001], a[100001];
	srand((unsigned)time(NULL));//��ϵͳʱ��������������
	show_rand(a);    //�������sum�������洢��a������
	double time[8] = { 0 }; //���ڼ�¼ÿһ��������������Ҫ��ʱ��
	int c = 0;
	while (1) {
		for (int i = 0; i < sum; i++) {
			arr[i] = a[i];
		}
		cout << endl << "��ѡ�����򷽷���";
		cin >> c;

		if (c == 1) {
			//��������ɵ�δ���������ԭ�ⲻ����ֵ��arr�Դ�����
			startTime = clock();
			BubbleSort(arr, sum);
			endTime = clock();
			time[0] = (double)endTime - (double)startTime;
			cout << "ð����������ʱ�䣺" << time[0] << endl;
			cout << "ð���������ý���������" << TempTime[0] << endl;
		}
		else if (c == 2) {
			startTime = clock();
			SelectSort(arr, sum);
			endTime = clock();
			time[1] = (double)endTime - (double)startTime;
			cout << "ѡ����������ʱ�䣺" << time[1] << endl;
			cout << "ѡ���������ý���������" << TempTime[1] << endl;
		}
		else if (c == 3) {
			startTime = clock();
			InsertSort(arr, sum);
			endTime = clock();
			time[2] = (double)endTime - (double)startTime;
			cout << "ֱ�Ӳ�����������ʱ�䣺" << time[2] << endl;
			cout << "ֱ�Ӳ����������ý���������" << TempTime[2] << endl;
		}
		else if (c == 4) {
			startTime = clock();
			ShellSort(arr, sum);
			endTime = clock();
			time[3] = (double)endTime - (double)startTime;
			cout << "ϣ����������ʱ�䣺" << time[3] << endl;
			cout << "ϣ���������ý���������" << TempTime[3] << endl;
		}
		else if (c == 5) {
			startTime = clock();
			QuickSort(arr, 0, sum - 1);
			endTime = clock();
			time[4] = (double)endTime - (double)startTime;
			cout << "������������ʱ�䣺" << time[4] << endl;
			cout << "�����������ý���������" << TempTime[4] << endl;
		}
		else if (c == 6) {
			startTime = clock();
			HeapSort(arr, sum);
			endTime = clock();
			time[5] = (double)endTime - (double)startTime;
			cout << "����������ʱ�䣺" << time[5] << endl;
			cout << "���������ý���������" << TempTime[5] << endl;
		}
		else if (c == 7) {
			startTime = clock();
			int* b = new int[sum];   //�ڹ鲢��������Ҫһ��b���������м���
			MergeSort(arr, 0, sum - 1, b);
			endTime = clock();
			time[6] = (double)endTime - (double)startTime;
			cout << "�鲢��������ʱ�䣺" << time[6] << endl;
			cout << "�鲢�������ñȽϴ�����" << TempTime[6] << endl;
			delete[]b;
		}
		else if (c == 8) {
			startTime = clock();
			sort_r(arr, sum);
			endTime = clock();
			time[7] = (double)endTime - (double)startTime;
			cout << "������������ʱ�䣺" << time[7] << endl;
			cout << "�����������ý���������" << TempTime[7] << endl;
		}
		else if (c == 9) {
			break;
		}
		else {
			cout << "����������������룡" << endl;
		}
	}
	return 0;

}