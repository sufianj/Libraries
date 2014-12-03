#include "user.h"
#include "myfunction.h"
#include "booklist.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>

using std::cin;
using std::cout;
using std::endl; 

void user::set_password()
{
	char str1[7], str2[7];
	int flag(1);
	while ( flag )
	{
		if (flag > 1)
			cout << "前后两次输的不一样！请重新输入： ";
		else
			cout << "请输入6位密码： ";
		type_password(str1);
		cout << endl << "请再输一次6位密码： ";
		type_password(str2);
		cout << endl;
		if (strcmp(str1, str2) == 0)
			flag = 0;
		else
			++flag;
	}
	strcpy(strpassword, str2);
	system("pause");
}

void user::set_info()
{
	unsigned int ichoice(0);
	while (ichoice != 4)
	{
		system("cls");
		cout << " 请输入操作号：" << endl
			<< "  1--> 修改姓名" << endl
			<< "  2--> 修改密码" << endl
			<< "  3--> 修改编号" << endl
			<< "  4--> 返回" << endl;
		input_usint(ichoice);
		switch (ichoice)
		{
		case 1:
			set_name(); break;
		case 2:
			set_password(); break;
		case 3:
			set_num(); break;
		case 4:
			return;
		default:
			cout << "这个操作还没开通吧？" << endl;
			system("pause");
			break;
		}
	}
}

void user::view_info()
{
	cout << PURFLE << endl;
	cout << "姓名： " << strname 
		<< " 编号： " << strnum << " 密码： " << strpassword << endl;
}

void user::search_book()
{
	unsigned int ichoice(0);
	booklist bl("book.txt");
	if (bl.get_isum() == 1)
	{
		cout << "尚未录入图书！" << endl;
		system("pause");
		return;
	}
	char str[30];
	while (ichoice != 3)
	{
		system("cls");
		cout << "请输入操作序号：" << endl;
		cout << "1--> 按书名查找" << endl;
		cout << "2--> 按作者查找" << endl;
		cout << "3--> 返回上级菜单" << endl;
		input_usint(ichoice);
		switch (ichoice)
		{
		case 1:
			cout << "请输入书名: " << endl;
			input_str(str, 30);
			bl.p_current  = bl.p_head->p_next;
			cout << "以下是符合的搜索结果：" << endl;
			while (bl.p_current->p_next != NULL)
			{
				if (strcmp(str, bl.p_current->get_name().c_str()) == 0)
					bl.p_current->view_info();
				++bl;
			}
			if (strcmp(str, bl.p_current->get_name().c_str()) == 0)
				bl.p_current->view_info();
			system("pause");
			break;
		case 2:
			cout << "请输入作者: " << endl;
			input_str(str, 20);
			bl.p_current  = bl.p_head->p_next;
			cout << "以下是符合的搜索结果：" << endl;
			while (bl.p_current->p_next != NULL)
			{
				if (strcmp(str, bl.p_current->get_author().c_str()) == 0)
					bl.p_current->view_info();
				++bl;
			}
			if (strcmp(str, bl.p_current->get_author().c_str()) == 0)
				bl.p_current->view_info();
			system("pause");
			break;
		case 3:
			break;
		default:
			cout << "好像没开通这个操作啊？" << endl;
			system("pause");
			break;
		}
	}
}