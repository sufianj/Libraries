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
	char strname[20];//����
	char strnum[20];//���
	char strpassword[7];//���룬ͳһ����λ��
public:
	string get_name(){string str(strname); return str;}
	string get_num(){string str(strnum); return str;}
	string get_password(){string str(strpassword); return str;}
	void set_name()//�����û���
	{
		cout << "�������û���" << endl;
		input_str(strname, 20);
		cout << endl;
		system("pause");
	}
	void set_num()//����ѧ��
	{
		cout << "������ѧ��" << endl;
		input_str(strnum, 20);
		cout << endl;
		system("pause");
	}
	void set_password();//��������
	void set_info();//������Ϣ
	virtual void view_info(); //��ʾ������Ϣ
	virtual void search_book();//����ͼ��
	void view_all_book()//�鿴����ͼ��
	{
		booklist bl("book.txt");
		bl.show_all();
	}
};
#endif