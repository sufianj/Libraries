#include "book.h"
#include "myfunction.h"
#include <string.h>
book::book()
{
	strcpy(strauthor, "");
	strcpy(strisbn, "");
	strcpy(strname, "");
}

book::book(book &b)
{
	cout << "&call!" << endl;
	strncpy(strauthor, b.get_author().c_str(), 20);
	strncpy(strisbn, b.get_isbn().c_str(), 20);
	strncpy(strname, b.get_name().c_str(), 20);
	id = b.get_id();
	iavailable = b.get_available ();
	isum = b.get_sum();
}

book::book(int i)
{
	if (i == 1)
	{
		set_author();
		set_name();
		set_isbn();
		set_sum();
		set_available();
	}
	else 
	{
		strncpy(strauthor, "unset", 20);
		strncpy(strname, "unset", 20);
		strncpy(strisbn, "unset", 20);
		isum = 5;
		iavailable = 5;
	}
}

void book::set_isbn()//����isbn
{
	cout << "������isbn" << endl;
	input_str(strisbn, 20);
	cout << endl;
	system("pause");
}

void book::set_name()//�����������
{
	cout << "����������" << endl;
	input_str(strname, 30);
	cout << endl;
	system("pause");
}

void book::set_author()//�����������
{
	cout << "�������������:" << endl;
	input_str(strauthor, 20);
	cout << endl;
	system("pause");
}

void book::set_sum()//������Ĳ���
{
	cout << "�������Ȿ��Ĳ���:" << endl;
	input_usint(isum);
	system("pause");
}

void book::set_available()//��������ڹ�����
{
	cout << "�������ڹ�����:" << endl;
	input_usint(iavailable);
	system("pause");
}

void book::view_info()
{
	cout << PURFLE << endl;
	cout << " ����   : " << strname << endl
		<< " id     : " << id << endl
		<< " isbn   : " << strisbn << endl
		<< " ����   : " << strauthor << endl
		<< " �ڹ��� : " << iavailable << endl
		<< " ����   : " << isum << endl;
}

void book::set_info()
{
	unsigned int ichoice(0);
	while (ichoice != 5)
	{
		system("cls");
		cout << " ����������ţ�" << endl
			<< "  1--> �޸�����" << endl
			<< "  2--> �޸�isbn��" << endl
			<< "  3--> �޸�����" << endl
			<< "  4--> �޸��ܲ���"<< endl
			<< "  5--> ����" << endl;
		input_usint(ichoice);
		switch (ichoice)
		{
		case 1:
			set_name(); break;
		case 2:
			set_isbn(); break;
		case 3:
			set_author(); break;
		case 4:
			set_sum(); break;
		case 5:
			return;
		default:
			cout << "���������û��ͨ�ɣ�" << endl;
			system("pause");
			break;
		}
	}
}