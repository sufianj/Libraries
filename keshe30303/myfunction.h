#ifndef MYFUNCTION_H
#define MYFUNCTION_H
#include<iostream>
#include<conio.h>
#include <time.h>

//����
#define PURFLE "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++�ء�ء�ء���"

using std::cin;
using std::cout;
using std::endl;

void type_password(char *p_str);
void input_usint(unsigned int &);
void input_str(char *str, int i);
void initialize();
void senior_admin_menu();
void admin_login();
void reader_login();
void senior_admin_login();
void view_admin();

void login();
struct borrow_info
{
	time_t bt;//����ʱ��
	unsigned int id;//���id������id==0��ʾû�н��顣
};
#endif