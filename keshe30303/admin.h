#ifndef ADMIN_H
#define ADMIN_H
#include "user.h"
#include "readerlist.h"
class admin: public user//普通管理员类
{
public:
	admin *p_next;
	admin *p_last;
	admin();//管理员类的默认构造凹函数
	admin(int);//管理员类的构造函数
	admin(admin &);//管理员类的拷贝构造函数
	void view_all_reader()//查看所有读者
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