#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include "myfunction.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

class book
{
protected:
	char strisbn[20];//书的isbn
	char strname[30];//书的名字
	char strauthor[20];//书的作者
	unsigned int isum;//这本书的总数
	unsigned int iavailable;//在馆数目
	unsigned int id;//书的内部编号，相当于数据表里的主键，是唯一的
public:
	book *p_next;
	book *p_last;
	book();//图书类的默认构造函数
	book(int);//图书类的构造函数
	book(book &);//图书类的拷贝构造函数
	string get_isbn(){string str(strisbn); return str;}//返回isbn
	string get_name(){string str(strname); return str;}
	string get_author(){string str(strauthor); return str;}
	unsigned int get_available(){return iavailable;}//返回书的在馆册数
	unsigned int get_sum(){return isum;}//返回书的总数
	unsigned int get_id(){return id;}//返回书的内部编号
	void set_isbn();//设置isbn
	void set_name();//设置书的名字
	void set_author();//设置书的作者
	void set_sum();//设置书的册数
	void set_available();//设置书的在馆总数
	void set_id(unsigned int i){id = i;}//设置书的内部编号
	void view_info();//输出这种图书的信息
	void borrow_one(){--iavailable;}//借出这种书的一本书
	void return_one(){++iavailable;}//还这种书的一本书
	void set_info();//设置图书信息
};
#endif