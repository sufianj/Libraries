#ifndef ADMINLIST_H
#define ADMINLIST_H
#include "admin.h"
#include "mylist.h"
class adminlist: public mylist<admin>
{
public:
	adminlist(char *str): mylist<admin>(str){}//����Ա������Ĺ��캯��
	void newone(int);//���һ������Ա
	void menu();//����Ա���������˵�
};
#endif