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
			cout << "ǰ��������Ĳ�һ�������������룺 ";
		else
			cout << "������6λ���룺 ";
		type_password(str1);
		cout << endl << "������һ��6λ���룺 ";
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
		cout << " ����������ţ�" << endl
			<< "  1--> �޸�����" << endl
			<< "  2--> �޸�����" << endl
			<< "  3--> �޸ı��" << endl
			<< "  4--> ����" << endl;
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
			cout << "���������û��ͨ�ɣ�" << endl;
			system("pause");
			break;
		}
	}
}

void user::view_info()
{
	cout << PURFLE << endl;
	cout << "������ " << strname 
		<< " ��ţ� " << strnum << " ���룺 " << strpassword << endl;
}

void user::search_book()
{
	unsigned int ichoice(0);
	booklist bl("book.txt");
	if (bl.get_isum() == 1)
	{
		cout << "��δ¼��ͼ�飡" << endl;
		system("pause");
		return;
	}
	char str[30];
	while (ichoice != 3)
	{
		system("cls");
		cout << "�����������ţ�" << endl;
		cout << "1--> ����������" << endl;
		cout << "2--> �����߲���" << endl;
		cout << "3--> �����ϼ��˵�" << endl;
		input_usint(ichoice);
		switch (ichoice)
		{
		case 1:
			cout << "����������: " << endl;
			input_str(str, 30);
			bl.p_current  = bl.p_head->p_next;
			cout << "�����Ƿ��ϵ����������" << endl;
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
			cout << "����������: " << endl;
			input_str(str, 20);
			bl.p_current  = bl.p_head->p_next;
			cout << "�����Ƿ��ϵ����������" << endl;
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
			cout << "����û��ͨ�����������" << endl;
			system("pause");
			break;
		}
	}
}