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

void book::set_isbn()//设置isbn
{
	cout << "请输入isbn" << endl;
	input_str(strisbn, 20);
	cout << endl;
	system("pause");
}

void book::set_name()//设置书的名字
{
	cout << "请输入书名" << endl;
	input_str(strname, 30);
	cout << endl;
	system("pause");
}

void book::set_author()//设置书的作者
{
	cout << "请输入书的作者:" << endl;
	input_str(strauthor, 20);
	cout << endl;
	system("pause");
}

void book::set_sum()//设置书的册数
{
	cout << "请输入这本书的册数:" << endl;
	input_usint(isum);
	system("pause");
}

void book::set_available()//设置书的在馆总数
{
	cout << "请输入在馆总数:" << endl;
	input_usint(iavailable);
	system("pause");
}

void book::view_info()
{
	cout << PURFLE << endl;
	cout << " 书名   : " << strname << endl
		<< " id     : " << id << endl
		<< " isbn   : " << strisbn << endl
		<< " 作者   : " << strauthor << endl
		<< " 在馆数 : " << iavailable << endl
		<< " 总数   : " << isum << endl;
}

void book::set_info()
{
	unsigned int ichoice(0);
	while (ichoice != 5)
	{
		system("cls");
		cout << " 请输入操作号：" << endl
			<< "  1--> 修改书名" << endl
			<< "  2--> 修改isbn码" << endl
			<< "  3--> 修改作者" << endl
			<< "  4--> 修改总册数"<< endl
			<< "  5--> 返回" << endl;
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
			cout << "这个操作还没开通吧？" << endl;
			system("pause");
			break;
		}
	}
}