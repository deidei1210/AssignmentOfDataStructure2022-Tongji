#define NEEDPAUSE 1
#define NONEEDPAUSE 0

#include<iostream>
#include<string>
#include<iomanip>
#include "StudentNode.h"
#include "StudentList.h"

using namespace std;

//Hint��ʾ��������֮ǰ����ʾ��
//a��ʾҪ���������
//choice��ʾ�Ƿ���Ҫpause
template<typename T>
void PutIn(string Hint,bool choice,T& a) {
	if (choice==NEEDPAUSE) {
		//����������֮ǰ����ͣ��һ��
		char m = 0;
		while(m!='\n')
	    	m = getchar();
	}
	//�������ʾ��
	cout << Hint;
	cin >> a;
	return;
}

//Hint��ʾ��������֮ǰ����ʾ��
//a��ʾҪ���������
//choice��ʾ�Ƿ���Ҫpause
//range_a��ʾ���ޣ�range_b��ʾ���ޣ������������ѡ��˵������������ݻ��з�Χ��Ҫ��һ�������������������ʱ��
void PutIn(string Hint, bool choice, int& a,int range_a,int range_b) {
	if (choice == NEEDPAUSE) {
		//����������֮ǰ����ͣ��һ��
		char m = 0;
		while (m != '\n')
			m = getchar();
	}
	//�������ʾ��
	cout << Hint;
	cin >> a;
	while (a<range_a || a>range_b) {
		cout << "��������ݲ��ںϷ���Χ�ڣ����������룡" << endl;
		cin >> a;
	}

	return;
}

//�����ʾ�ֱ����a�Լ���
void ToContinue(string Hint, const char a) {
	cout << endl << Hint ;
	char m = 0;
	while (m != a) {
		m = getchar();
	}
}

//�˵���ʾ������ɹ�ѡ��Ĳ���ѡ��
void menu() {
	cout << "1��������п�����Ϣ        2����ѯָ��������Ϣ" << endl;
	cout << "3����ӿ�����Ϣ            4���޸Ŀ�����Ϣ" << endl;
	cout << "5��ɾ��ָ��������Ϣ        6���˳�ϵͳ" << endl;
	cout << "0���鿴�˵�" << endl;
}

int main()
{
	cout << "�����뽨��������Ϣϵͳ!(����س��Լ�������������Ϣϵͳ)";
	
	//����ѧ����������
	int StudentNum = 0;
	PutIn("�����뿼��������",NEEDPAUSE, StudentNum);

	//�ȳ�ʼ��һ������
	StudentList Stu;
	//Ȼ����ѧ����������������
	Stu.CreateList(StudentNum);
	char m = getchar();

	//���س���ӡ���ոս���������
	ToContinue("��ϲ�㣡������Ϣ¼����ɣ����س��˶�¼����Ϣ��",'\n');

	Stu.PrintList();

	ToContinue("������Ϣ��ʾ��ϣ����س�����......", '\n');
	menu();

	int choice = 0;                                        //��ʾѡ��Ĳ���
	int num = 0;                                           //���ڱ�ʾ�����ı��
	string name = "";                                      //���ڱ�ʾ����������
	StudentNode* result;
	while (1) {
		PutIn("��ѡ����Ҫ���еĲ���:",NONEEDPAUSE, choice,0,6);
		if (choice == 1) {                                 //��ӡȫ�忼������Ϣ
			cout << "ȫ�忼����Ϣ���£�" << endl;
			Stu.PrintList();
		}
		else if (choice == 2) {		                                              
			int c = 0;                                     //��ѯָ����������Ϣ����ͨ������Ҳ����ͨ������
			PutIn("���� 1 ���и��ݿ��Ų��ҿ��������� 2 ���и����������ҿ�����",NONEEDPAUSE, c,1,2);			
			switch (c) {
				case 1:                                   //���ݿ��Ų���
					PutIn("������ѧ���Ŀ��ţ�", NONEEDPAUSE, num);
				    result = Stu.Find(num);
					if (result != NULL) {
						cout << "����        ����        �Ա�        ����        �������" << endl;
						result->PrintNode();              //������ǿ�ָ��Ļ�˵���ҵ�������������ǾͿ���ֱ������ڵ���Ϣ
					}
					break;
				case 2:                                   //������������
					PutIn("������ѧ����������", NONEEDPAUSE, name);
					result = Stu.Find(name);
					if (result != NULL) {
						cout << "����        ����        �Ա�        ����        �������" << endl;
						result->PrintNode();              //������ǿ�ָ��Ļ�˵���ҵ�������������ǾͿ���ֱ������ڵ���Ϣ
					}
					break;
				default:
					break;
			}
		}
		else if (choice == 3) {                            //��ӿ�������Ϣ
			Stu.Insert();
			cout << endl << "����������£�" << endl;
			Stu.PrintList();
		}
		else if (choice == 4) {                    //�޸Ŀ�����Ϣ
			Stu.Modify();
			Stu.PrintList();
		}
		else if (choice == 5) {                             //����ɾ��ָ���Ŀ�����Ϣ
			int c = 0;
			int num = 0;
			string name = "";
			PutIn("��ѧ�Ų��ҿ�����ɾ��ѡ��1�����������ҿ�����ɾ���밴2��", NONEEDPAUSE, c, 1, 2);
			switch (c) {
				case 1:
					PutIn("������Ҫɾ���Ŀ�����ѧ�ţ�", NONEEDPAUSE, num);
					Stu.Remove(num);
					Stu.PrintList();
					break;
				case 2:
					PutIn("������Ҫɾ���Ŀ�����������", NONEEDPAUSE, name);
					Stu.Remove(name);
					Stu.PrintList();
					break;
				default:
					break;
			}
		}
		else if (choice == 6) {
			break;
		}
		else if (choice == 0) {
			cout << endl;
			menu();
		}
		cout << endl;
	}
	return 0;
}