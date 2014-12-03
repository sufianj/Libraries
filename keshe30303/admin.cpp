#include "admin.h"
#include "readerlist.h"
#include "booklist.h"
#include "myfunction.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

admin::admin()
{
	strcpy(strname, "");
	strcpy(strpassword, "");
	strcpy(strnum, "");
}

admin::admin(int i)
{
	if (i == 1)
	{	
		set_name();
		set_password();
		set_num();
	}
	else
	{
		strncpy(strname, "unset", 20);
		strncpy(strpassword, "888888", 7);
		strncpy(strnum, "unset", 20);
	}
}

admin::admin(admin &a)
{
	strncpy(strname, a.get_name().c_str(), 20);
	strncpy(strpassword, a.get_password().c_str(), 7);
	strncpy(strnum,a.get_num().c_str(), 20);
}

void admin::borrow_book()
{
	unsigned int id(0);
	bool bflag(1);
	booklist bl("book.txt");
	readerlist rl("reader.txt");
	if (bl.get_isum() == 1)
	{
		cout << "尚未录入图书，请先添加图书！" << endl;
		system("pause");
		return;
	}
	if (rl.get_isum() == 1)
	{
		cout << "尚未录入读者图书，请先添加读者！" << endl;
		system("pause");
		return;
	}
	cout << "请输入要借书的同学的id : ";
	input_usint(id);
	rl.p_current = rl.p_head->p_next;
	while (rl.p_current->p_next != NULL)
	{
		if (id == rl.p_current->get_id())
		{
			cout << "该同学的信息为：" << endl;
			rl.p_current->view_info();
			bflag = 0;
			break;
		}
		else
			++rl;
	}
	if (bflag && id == rl.p_current->get_id())
	{
		cout << "该同学的信息为：" << endl;
		rl.p_current->view_info();
		bflag = 0;
	}
	if (bflag)
	{
		cout << "找不到这个同学！" << endl;
		system("pause");
		return;
	}
	else if (rl.p_current->forfeit ())
	{
		cout << "该生有欠款，不得借书！" << endl;
		system("pause");
		return;
	}
	else if (rl.p_current->get_nbook() == 3)
	{
		cout << "该生已借3本书，不得借书！" << endl;
		system("pause");
		return;
	}
	else 
	{	
		bflag = 1;
		cout << "请输入要借的书id : ";
		input_usint(id);
		bl.p_current = bl.p_head->p_next;
		while (bl.p_current->p_next != NULL)
		{
			if (id == bl.p_current->get_id())
			{
				bflag = 0;
				break;
			}
			else
				++bl;
		}
		if (id == bl.p_current->get_id())
		{
			bflag = 0;
		}
		if (bflag)
		{
			cout << "找不到这本书！" << endl;
			system("pause");
			return;
		}
		else
		{
			rl.p_current->add_book(id);
			bl.p_current->borrow_one();
			cout << "借书成功！" << endl;
			return;
		}
	}
}

void admin::return_book()
{
	unsigned int id(0);
	bool bflag(1);
	booklist bl("book.txt");
	readerlist rl("reader.txt");
	if (bl.get_isum() == 1)
	{
		cout << "尚未录入图书，请先添加图书！" << endl;
		system("pause");
		return;
	}
	if (rl.get_isum() == 1)
	{
		cout << "尚未录入读者图书，请先添加读者！" << endl;
		system("pause");
		return;
	}
	cout << "请输入要还书的同学的id : ";
	input_usint(id);
	rl.p_current = rl.p_head->p_next;
	while (rl.p_current->p_next != NULL)
	{
		if (id == rl.p_current->get_id())
		{
			cout << "该同学的信息为：" << endl;
			rl.p_current->view_info();
			bflag = 0;
			break;
		}
		else
			++rl;
	}
	if (bflag && id == rl.p_current->get_id())
	{
		cout << "该同学的信息为：" << endl;
		rl.p_current->view_info();
		bflag = 0;
	}

	if (bflag)
	{
		cout << "找不到这个同学！" << endl;
		system("pause");
		return;
	}
	else if (rl.p_current->get_nbook() == 0)
	{
		cout << "该生未曾借书" << endl;
		system("pause");
		return;
	}
	else 
	{
		bflag = 1;
		cout << "请输入要还的书id : ";
		input_usint(id);
		if (! rl.p_current->check_book(id))
		{
			cout << "该生未借此书" << endl;
			system("pause");
			return;
		}
		bl.p_current = bl.p_head->p_next;
		bflag = 1;
		while (bl.p_current->p_next != NULL)
		{
			if (id == bl.p_current->get_id())
			{
				bflag = 0;
				break;
			}
			else
				++bl;
		}
		if (id == bl.p_current->get_id())
		{
			bflag = 0;
		}
		if (bflag)
		{
			cout << "找不到这本书！" << endl;
			system("pause");
			return;
		}
		else
		{
			rl.p_current->delete_book(id);
			bl.p_current->return_one();
			cout << "借书成功！" << endl;
			return;
		}
	}
}

void admin::modify_book_info()
{
	unsigned int id;
	booklist bl("book.txt");
	if (bl.get_isum() == 1)
	{
		cout << "尚未录入图书，请先添加图书！" << endl;
		system("pause");
		return;
	}
	bool bflag(1);
	cout << "请输入你要修改的书的id : " ;
	input_usint(id);
	bl.p_current = bl.p_head->p_next;
	while (bl.p_current->p_next != NULL)
	{
		if (bl.p_current->get_id() == id)
		{
			bflag = 0;
			break;
		}
		else
			++bl;
	}
	if (bl.p_current->get_id() == id)
	{
		bflag = 0;
	}
	if (bflag)
	{
		cout << "找不到这本书" << endl;
		system("pause");
		return;
	}
	bl.p_current->set_info();
}

void admin::modify_reader_info()
{
	unsigned int id;
	readerlist rl("reader.txt");
	if (rl.get_isum() == 1)
	{
		cout << "尚未录入读者，请先添加读者！" << endl;
		system("pause");
		return;
	}
	bool bflag(1);
	cout << "请输入你要修改的读者的id : " ;
	input_usint(id);
	rl.p_current = rl.p_head->p_next;
	while (rl.p_current->p_next != NULL)
	{
		if (rl.p_current->get_id() == id)
		{
			bflag = 0;
			break;
		}
		else
			++rl;
	}
	if (rl.p_current->get_id() == id)
	{
		bflag = 0;
	}
	if (bflag)
	{
		cout << "找不到这个人" << endl;
		system("pause");
		return;
	}
	rl.p_current->set_info();
}

void admin::delete_reader()
{
	unsigned int id;
	readerlist rl("reader.txt");
	if (rl.get_isum() == 1)
	{
		cout << "尚未录入读者，请先添加读者！" << endl;
		system("pause");
		return;
	}
	bool bflag(1);
	cout << "请输入你要删除的读者的id : " ;
	input_usint(id);
	rl.p_current = rl.p_head->p_next;
	while (rl.p_current->p_next != NULL)
	{
		if (rl.p_current->get_id() == id)
		{
			bflag = 0;
			break;
		}
		else
			++rl;
	}
	if (rl.p_current->get_id() == id)
	{
		bflag = 0;
	}
	if (bflag)
	{
		cout << "找不到这个人" << endl;
		system("pause");
		return;
	}
	if (rl.p_current->get_nbook())
	{
		cout << "此人有未还图书，不能删除" << endl;
		system("pause");
		return;
	}
	rl.delete_current();
}

void admin::delete_book()
{
	unsigned int id;
	booklist bl("book.txt");
	if (bl.get_isum() == 1)
	{
		cout << "尚未录入图书，请先添加图书！" << endl;
		system("pause");
		return;
	}
	bool bflag(1);
	cout << "请输入你要删除的图书的id : " ;
	input_usint(id);
	bl.p_current = bl.p_head->p_next;
	while (bl.p_current->p_next != NULL)
	{
		if (bl.p_current->get_id() == id)
		{
			bflag = 0;
			break;
		}
		else
			++bl;
	}
	if (bl.p_current->get_id() == id)
	{
		bflag = 0;
	}
	if (bflag)
	{
		cout << "找不到这本书" << endl;
		system("pause");
		return;
	}
	if (bl.p_current->get_sum() != bl.p_current->get_available())
	{
		cout << "此类书有未还图书，不能删除" << endl;
		system("pause");
		return;
	}
	bl.delete_current();
}

void admin::add_book()
{
	booklist bl("book.txt");
	bl.newone(1);
}

void admin::add_reader()
{
	readerlist rl("reader.txt");
	rl.newone(1);
}