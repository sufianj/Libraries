#ifndef ADMIN_H
#define ADMIN_H
#include "user.h"
#include "readerlist.h"
class admin: public user//��ͨ����Ա��
{
public:
	admin *p_next;
	admin *p_last;
	admin();//����Ա���Ĭ�Ϲ��찼����
	admin(int);//����Ա��Ĺ��캯��
	admin(admin &);//����Ա��Ŀ������캯��
	void view_all_reader()//�鿴���ж���
	{
		readerlist rl("reader.txt");
		rl.show_all();
		system("pause");
	}
	void modify_reader_info();
	void modify_book_info();
	void borrow_book();
	void return_book();
	void delete_book();
	void add_book();
	void add_reader();
	void delete_reader();
};
#endif