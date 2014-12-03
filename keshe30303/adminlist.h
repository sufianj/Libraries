#ifndef ADMINLIST_H
#define ADMINLIST_H
#include "admin.h"
#include "mylist.h"
class adminlist: public mylist<admin>
{
public:
	adminlist(char *str): mylist<admin>(str){}//管理员链表类的构造函数
	void newone(int);//添加一个管理员
	void menu();//管理员操作的主菜单
};
#endif