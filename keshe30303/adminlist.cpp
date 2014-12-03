#include "adminlist.h"
#include "admin.h"
#include "booklist.h"
#include "readerlist.h"

void adminlist::newone(int i)
{	
	admin *p_one;
	p_one = new admin(i);
	p_one->p_next = p_current->p_next;
	p_one->p_last = p_current;
	p_current->p_next = p_one;
	p_current = p_one;
	++isum;
}

void adminlist::menu()
{
	system("color 5a");//管理员界面是紫底绿字
	unsigned int ichoice(0);
	while (ichoice != 14)
	{
		system("cls");
		cout << "   欢迎进入小江的图书管理系统" << endl;
		cout << PURFLE << endl;
		cout << "  请输入操作序号" << endl;
		cout << "   1--->  修改个人信息  6--->  修改图书信息" << endl;
		cout << "   2--->  查看个人信息  7--->  办理借书" << endl;
		cout << "   3--->  查找图书      8--->  办理还书" << endl;
		cout << "   4--->  查看所有图书  9--->  查看所有读者" << endl;
		cout << "   5--->  修改读者信息  10-->  删除图书" << endl;
		cout << "   11-->  删除读者      12-->  增加图书" << endl;
		cout << "   13-->  增加读者      14-->  返回上级菜单" << endl;
		input_usint(ichoice);
		switch(ichoice)
		{
		case 1:
			p_current->set_info();break;
		case 2:
			p_current->view_info(); system("pause"); break;
		case 3:
			p_current->search_book();break;
		case 4:
			p_current->view_all_book(); system("pause"); break;
		case 5:
			p_current->modify_reader_info(); break;
		case 6:
			p_current->modify_book_info(); break;
		case 7:
			p_current->borrow_book(); break;
		case 8:
			p_current->return_book(); break;
		case 9:
			p_current->view_all_reader(); system("pause"); break;
		case 10:
			p_current->delete_book(); break;
		case 11:
			p_current->delete_reader(); break;
		case 12:
			p_current->add_book(); break;
		case 13:
			p_current->add_reader(); break;
		case 14:
			break;
		default :
			cout << "此功能尚未开通！" << endl;
			system("pause");
			break;
		}
	}
}

