#ifndef BOOKLIST_H
#define BOOKLIST_H
#include "mylist.h"
#include "book.h"
class booklist:public mylist<book>
{
public:
	booklist(char *str):mylist<book>(str){};//��������Ĺ��캯��
	void newone(int);//���һ����
};
#endif