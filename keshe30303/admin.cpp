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
		cout << "��δ¼��ͼ�飬�������ͼ�飡" << endl;
		system("pause");
		return;
	}
	if (rl.get_isum() == 1)
	{
		cout << "��δ¼�����ͼ�飬������Ӷ��ߣ�" << endl;
		system("pause");
		return;
	}
	cout << "������Ҫ�����ͬѧ��id : ";
	input_usint(id);
	rl.p_current = rl.p_head->p_next;
	while (rl.p_current->p_next != NULL)
	{
		if (id == rl.p_current->get_id())
		{
			cout << "��ͬѧ����ϢΪ��" << endl;
			rl.p_current->view_info();
			bflag = 0;
			break;
		}
		else
			++rl;
	}
	if (bflag && id == rl.p_current->get_id())
	{
		cout << "��ͬѧ����ϢΪ��" << endl;
		rl.p_current->view_info();
		bflag = 0;
	}
	if (bflag)
	{
		cout << "�Ҳ������ͬѧ��" << endl;
		system("pause");
		return;
	}
	else if (rl.p_current->forfeit ())
	{
		cout << "������Ƿ����ý��飡" << endl;
		system("pause");
		return;
	}
	else if (rl.p_current->get_nbook() == 3)
	{
		cout << "�����ѽ�3���飬���ý��飡" << endl;
		system("pause");
		return;
	}
	else 
	{	
		bflag = 1;
		cout << "������Ҫ�����id : ";
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
			cout << "�Ҳ����Ȿ�飡" << endl;
			system("pause");
			return;
		}
		else
		{
			rl.p_current->add_book(id);
			bl.p_current->borrow_one();
			cout << "����ɹ���" << endl;
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
		cout << "��δ¼��ͼ�飬�������ͼ�飡" << endl;
		system("pause");
		return;
	}
	if (rl.get_isum() == 1)
	{
		cout << "��δ¼�����ͼ�飬������Ӷ��ߣ�" << endl;
		system("pause");
		return;
	}
	cout << "������Ҫ�����ͬѧ��id : ";
	input_usint(id);
	rl.p_current = rl.p_head->p_next;
	while (rl.p_current->p_next != NULL)
	{
		if (id == rl.p_current->get_id())
		{
			cout << "��ͬѧ����ϢΪ��" << endl;
			rl.p_current->view_info();
			bflag = 0;
			break;
		}
		else
			++rl;
	}
	if (bflag && id == rl.p_current->get_id())
	{
		cout << "��ͬѧ����ϢΪ��" << endl;
		rl.p_current->view_info();
		bflag = 0;
	}

	if (bflag)
	{
		cout << "�Ҳ������ͬѧ��" << endl;
		system("pause");
		return;
	}
	else if (rl.p_current->get_nbook() == 0)
	{
		cout << "����δ������" << endl;
		system("pause");
		return;
	}
	else 
	{
		bflag = 1;
		cout << "������Ҫ������id : ";
		input_usint(id);
		if (! rl.p_current->check_book(id))
		{
			cout << "����δ�����" << endl;
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
			cout << "�Ҳ����Ȿ�飡" << endl;
			system("pause");
			return;
		}
		else
		{
			rl.p_current->delete_book(id);
			bl.p_current->return_one();
			cout << "����ɹ���" << endl;
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
		cout << "��δ¼��ͼ�飬�������ͼ�飡" << endl;
		system("pause");
		return;
	}
	bool bflag(1);
	cout << "��������Ҫ�޸ĵ����id : " ;
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
		cout << "�Ҳ����Ȿ��" << endl;
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
		cout << "��δ¼����ߣ�������Ӷ��ߣ�" << endl;
		system("pause");
		return;
	}
	bool bflag(1);
	cout << "��������Ҫ�޸ĵĶ��ߵ�id : " ;
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
		cout << "�Ҳ��������" << endl;
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
		cout << "��δ¼����ߣ�������Ӷ��ߣ�" << endl;
		system("pause");
		return;
	}
	bool bflag(1);
	cout << "��������Ҫɾ���Ķ��ߵ�id : " ;
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
		cout << "�Ҳ��������" << endl;
		system("pause");
		return;
	}
	if (rl.p_current->get_nbook())
	{
		cout << "������δ��ͼ�飬����ɾ��" << endl;
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
		cout << "��δ¼��ͼ�飬�������ͼ�飡" << endl;
		system("pause");
		return;
	}
	bool bflag(1);
	cout << "��������Ҫɾ����ͼ���id : " ;
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
		cout << "�Ҳ����Ȿ��" << endl;
		system("pause");
		return;
	}
	if (bl.p_current->get_sum() != bl.p_current->get_available())
	{
		cout << "��������δ��ͼ�飬����ɾ��" << endl;
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