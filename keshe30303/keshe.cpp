#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <stdlib.h>
#include "myfunction.h"
#include "mytime.h"
#include "readerlist.h"
#include "adminlist.h"
#include "booklist.h"

using std::string;
using std::ios;
using std::ofstream;
using std::cin;
using std::cout;
using std::endl;

int main()
{
	login();
	return 0;
}

void type_password(char *p_str)//����������ʾС����
{
	for(int i(0); i != 6; ++i)//�����ƣ�δ����û����볬��6λ����Ĵ���
	{
		p_str[i] = getch();
		cout << "*";
	}
	p_str[6] = '\0';
}

void input_usint(unsigned int &i)//�����޷���������
{
	bool flag(1);
	string str;
	unsigned int temp;
	int ii;
	while(flag)
	{
		cin >> str;
		temp = 0;
		for(ii = 0; ii != str.length(); ++ii)
		{
			if (str[ii] <= '9' && str[ii] >= '0')
				temp += (str[ii]-'0') * pow(10, (str.length() - 1 - ii));
			else
				break;
		}
		if ( ii == str.length() && temp <= 65534)
		{
			flag = 0;
			i = temp;
		}
		else
			cout << "�����������������һ��������:" << endl;
	}
}

void input_str(char *str, int i)//���볤�Ȳ�����i���ַ���
{
	string str1;
	bool flag(1);
	while(flag)
	{
		cin >> str1;
		if (str1.length() < i)
			flag = 0;
		else 
			cout << "����̫�࣡���������룺" << endl;
	}
	strncpy(str, str1.c_str(), i);
}

ostream & operator <<(ostream &os, const mytime &mt)
{
	os << mt.t->tm_year + 1900 << " �� " << mt.t->tm_mon + 1 << " �� " 
		<< mt.t->tm_mday << " ��";
	return os;
}

void login()
{
	unsigned int ichoice(0);
	bool bflag;
	while (ichoice != 4)
	{
		bflag = 1;//bflag = 1����˼����Ҫ�������ҡ�
		system("color 8e");//��ʼ�����ǻҵ׻���
		system("cls");
		cout << "��ӭ����С����ͼ�����ϵͳ��" << endl;
		cout << PURFLE << endl;
		cout << "  ������������ţ� " << endl
			<< "  1--> ���ߵ�½" << endl
			<< "  2--> ����Ա��½" << endl
			<< "  3--> ϵͳ����Ա��½"<< endl
			<< "  4--> �˳�ϵͳ" << endl;
		input_usint(ichoice);
		switch (ichoice)
		{
		case 1:
			reader_login();
			break;
		case 2:
			admin_login();
			break;
		case 3:
			senior_admin_login();
			break;
		case 4:
			break;
		default:
			cout << "�˲�����δ������" << endl;
			system("pause");
			break;
		}
	}
}

void senior_admin_menu()
{
	unsigned int ichoice(0);
	while(ichoice != 3)
	{
		system("cls");
		cout << "   ��ӭ�����ϴ�" << endl
			<< PURFLE << endl
			<< "   ������������� : " << endl
			<< "   1--> һ����ʼ��ϵͳ" << endl
			<< "   2--> ��������Ա����Ϣ" << endl
			<< "   3--> �˳�ϵͳ�����ϼ��˵� " << endl;
		input_usint(ichoice);
		switch (ichoice)
		{
		case 1:
			initialize();
			system("pause");
			break;
		case 2:
			view_admin();
			system("pause");
			break;
		case 3:
			break;
		default :
			cout << "����û��ͨ������ܰ���" << endl;
		}
	}
}

void view_admin()
{
	adminlist al("admin.txt");
	al.show_all();
	system("pause");
}
void initialize()//�����ǳ�ʼ������ϵͳʱ���еĴ��룬��ϵͳ����Ա�ڵ�һ������ϵͳʱ����
{
	unsigned int i(0);
	ofstream output;
	output.open("id.txt", ios::binary);
	if (output.fail())
	{
		cout << "���ļ�id.txtʧ��" << endl;
		system("pause");
		return;
	}
	output.write((const char *)&i, sizeof(i));
	output.close();
	output.clear();
	output.open("id2.txt", ios::binary);
	if (output.fail())
	{
		cout << "���ļ�id2.txtʧ��" << endl;
		system("pause");
		return;
	}
	output.write((const char *)&i, sizeof(i));
	output.close();
	output.open("book.txt", ios::binary);
	output.close();
	output.open("reader.txt", ios::binary);
	output.close();
	output.open("admin.txt", ios::binary);
	output.close();
	booklist bl("book.txt");
	for (i = 0; i != 5; ++i)
		bl.newone(2);
	readerlist rl("reader.txt");
	for (i = 0; i != 5; ++i)
		rl.newone(2);
	adminlist al("admin.txt");
	for (i = 0; i != 5; ++i)
		al.newone(2);
	cout << "ϵͳ��ʼ����ϣ�������ȫ����ͼ����Ϣ������Ϣ����Ա��Ϣ" << endl;
	bl.show_all();
	al.show_all();
	rl.show_all();
}

void reader_login()
{	
	bool bflag(1);
	char strpw[7];
	unsigned int id(0);
	readerlist rl("reader.txt");
	if (rl.get_isum () == 1)
	{
		cout << "��δ�ǼǶ����û���������ϵ����Ա��ϵͳ����Ա��ʼ��ϵͳ��" << endl;
		system("pause");
		return;
	}
	rl.p_current = rl.p_head->p_next;
	cout << "�������û�id : ";
	input_usint(id);
	cout << "������6λ�������� : ";
	type_password(strpw);
	while (rl.p_current->p_next != NULL && bflag)
	{
		if (id == rl.p_current->get_id() && \
			strncmp (strpw, rl.p_current->get_password().c_str(), 6) == 0)
		{
			bflag = 0;
			break;
		}
		else
			++rl;	
	}
	if (bflag && id == rl.p_current->get_id() && \
		strncmp (strpw, rl.p_current->get_password().c_str(), 6) == 0)
	{
		bflag = 0;
	}
	if (bflag)
	{
		cout << "�û������ڻ�����������������룡" << endl;
		system("pause");
		return;
	}
	else
		rl.menu();
}

void admin_login()
{
	bool bflag(1);
	char strname[20];
	char strpw[7];
	adminlist al("admin.txt");
	if (al.get_isum () == 1)
	{
		cout << "��δ���ù���Ա��������ϵϵͳ����Ա��ʼ��ϵͳ��" << endl;
		system("pause");
		return;
	}
	al.p_current = al.p_head->p_next;
	cout << "�������û��� : ";
	input_str(strname, 20);
	cout << "������6λ�������� : ";
	type_password(strpw);
	while (al.p_current->p_next != NULL && bflag)
	{
		if (strcmp (strname, al.p_current->get_name().c_str()) == 0 && \
			strncmp (strpw, al.p_current->get_password().c_str(), 6) == 0)
		{
			bflag = 0;
			break;
		}
		else
			++al;	
	}
	if (strcmp (strname, al.p_current->get_name().c_str()) == 0 && \
		strncmp (strpw, al.p_current->get_password().c_str(), 6) == 0)
		bflag = 0;

	if (bflag)
	{
		cout << "�û������ڻ�����������������룡";
		system("pause");
		return;
	}
	else
		al.menu();
}

void senior_admin_login()
{	
	char strpw[7];
	cout << "������ϵͳ����Ա��6λ���� : " << endl;
	type_password(strpw);
	if (strcmp (strpw, "lalala") != 0)
	{
		cout << "������ˣ�" << endl;
		system("pause");
		return;
	}
	senior_admin_menu();
}