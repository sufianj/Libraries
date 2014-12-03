#ifndef BOOKLIST_H
#define BOOKLIST_H
#include "mylist.h"
#include "book.h"
class booklist:public mylist<book>
{
public:
	booklist(char *str):mylist<book>(str){};//书链表类的构造函数
	void newone(int);//添加一类书
};
#endif