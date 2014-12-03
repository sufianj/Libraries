#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include "myfunction.h"
#include "booklist.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

class user
{
protected:
	char strname[20];//姓名
	char strnum[20];//编号
	char strpassword[7];//密码，统一是六位的
public:
	string get_name(){string str(strname); return str;}
	string get_num(){string str(strnum); return str;}
	string get_password(){string str(strpassword); return str;}
	void set_name()//设置用户名
	{
		cout << "请输入用户名" << endl;
		input_str(strname, 20);
		cout << endl;
		system("pause");
	}
	void set_num()//设置学号
	{
		cout << "请输入学号" << endl;
		input_str(strnum, 20);
		cout << endl;
		system("pause");
	}
	void set_password();//设置密码
	void set_info();//设置信息
	virtual void view_info(); //显示个人信息
	virtual void search_book();//查找图书
	void view_all_book()//查看所有图书
	{
		booklist bl("book.txt");
		bl.show_all();
	}
};
#endif