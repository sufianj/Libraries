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
	system("color 5a");//����Ա�������ϵ�����
	unsigned int ichoice(0);
	while (ichoice != 14)
	{
		system("cls");
		cout << "   ��ӭ����С����ͼ�����ϵͳ" << endl;
		cout << PURFLE << endl;
		cout << "  ������������" << endl;
		cout << "   1--->  �޸ĸ�����Ϣ  6--->  �޸�ͼ����Ϣ" << endl;
		cout << "   2--->  �鿴������Ϣ  7--->  �������" << endl;
		cout << "   3--->  ����ͼ��      8--->  ������" << endl;
		cout << "   4--->  �鿴����ͼ��  9--->  �鿴���ж���" << endl;
		cout << "   5--->  �޸Ķ�����Ϣ  10-->  ɾ��ͼ��" << endl;
		cout << "   11-->  ɾ������      12-->  ����ͼ��" << endl;
		cout << "   13-->  ���Ӷ���      14-->  �����ϼ��˵�" << endl;
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
			cout << "�˹�����δ��ͨ��" << endl;
			system("pause");
			break;
		}
	}
}

