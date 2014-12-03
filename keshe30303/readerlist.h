#ifndef READERLIST_H
#define READERLIST_H
#include "mylist.h"
#include "reader.h"
class readerlist : public mylist<reader>
{
public:
	readerlist(char * str):mylist<reader>(str){}//读者链表类的构造函数
	void newone(int);
	void menu();
};
#endif
