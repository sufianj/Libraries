#ifndef READERLIST_H
#define READERLIST_H
#include "mylist.h"
#include "reader.h"
class readerlist : public mylist<reader>
{
public:
	readerlist(char * str):mylist<reader>(str){}//����������Ĺ��캯��
	void newone(int);
	void menu();
};
#endif
