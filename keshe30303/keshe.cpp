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

void type_password(char *p_str)//输入密码显示小星星
{
	for(int i(0); i != 6; ++i)//待改善：未解决用户输入超过6位引起的错误。
	{
		p_str[i] = getch();
		cout << "*";
	}
	p_str[6] = '\0';
}

void input_usint(unsigned int &i)//输入无符号整型数
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
			cout << "输入错误！请重新输入一个正整数:" << endl;
	}
}

void input_str(char *str, int i)//输入长度不超过i的字符串
{
	string str1;
	bool flag(1);
	while(flag)
	{
		cin >> str1;
		if (str1.length() < i)
			flag = 0;
		else 
			cout << "字数太多！请重新输入：" << endl;
	}
	strncpy(str, str1.c_str(), i);
}

ostream & operator <<(ostream &os, const mytime &mt)
{
	os << mt.t->tm_year + 1900 << " 年 " << mt.t->tm_mon + 1 << " 月 " 
		<< mt.t->tm_mday << " 日";
	return os;
}

void login()
{
	unsigned int ichoice(0);
	bool bflag;
	while (ichoice != 4)
	{
		bflag = 1;//bflag = 1的意思是需要继续查找。
		system("color 8e");//初始界面是灰底黄字
		system("cls");
		cout << "欢迎进入小江的图书管理系统！" << endl;
		cout << PURFLE << endl;
		cout << "  请输入操作代号： " << endl
			<< "  1--> 读者登陆" << endl
			<< "  2--> 管理员登陆" << endl
			<< "  3--> 系统管理员登陆"<< endl
			<< "  4--> 退出系统" << endl;
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
			cout << "此操作尚未开发！" << endl;
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
		cout << "   欢迎您，老大！" << endl
			<< PURFLE << endl
			<< "   请输出操作代码 : " << endl
			<< "   1--> 一键初始化系统" << endl
			<< "   2--> 看看管理员的信息" << endl
			<< "   3--> 退出系统返回上级菜单 " << endl;
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
			cout << "好像还没开通这个功能啊！" << endl;
		}
	}
}

void view_admin()
{
	adminlist al("admin.txt");
	al.show_all();
	system("pause");
}
void initialize()//以下是初始化整个系统时运行的代码，由系统管理员在第一次启用系统时调用
{
	unsigned int i(0);
	ofstream output;
	output.open("id.txt", ios::binary);
	if (output.fail())
	{
		cout << "打开文件id.txt失败" << endl;
		system("pause");
		return;
	}
	output.write((const char *)&i, sizeof(i));
	output.close();
	output.clear();
	output.open("id2.txt", ios::binary);
	if (output.fail())
	{
		cout << "打开文件id2.txt失败" << endl;
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
	cout << "系统初始化完毕，以下是全部的图书信息读者信息管理员信息" << endl;
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
		cout << "尚未登记读者用户，请先联系管理员或系统管理员初始化系统！" << endl;
		system("pause");
		return;
	}
	rl.p_current = rl.p_head->p_next;
	cout << "请输入用户id : ";
	input_usint(id);
	cout << "请输入6位数的密码 : ";
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
		cout << "用户不存在或密码错误，请重新输入！" << endl;
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
		cout << "尚未设置管理员，请先联系系统管理员初始化系统！" << endl;
		system("pause");
		return;
	}
	al.p_current = al.p_head->p_next;
	cout << "请输入用户名 : ";
	input_str(strname, 20);
	cout << "请输入6位数的密码 : ";
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
		cout << "用户不存在或密码错误，请重新输入！";
		system("pause");
		return;
	}
	else
		al.menu();
}

void senior_admin_login()
{	
	char strpw[7];
	cout << "请输入系统管理员的6位密码 : " << endl;
	type_password(strpw);
	if (strcmp (strpw, "lalala") != 0)
	{
		cout << "密码错了！" << endl;
		system("pause");
		return;
	}
	senior_admin_menu();
}