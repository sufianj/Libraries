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
	char strisbn[20];//���isbn
	char strname[30];//�������
	char strauthor[20];//�������
	unsigned int isum;//�Ȿ�������
	unsigned int iavailable;//�ڹ���Ŀ
	unsigned int id;//����ڲ���ţ��൱�����ݱ������������Ψһ��
public:
	book *p_next;
	book *p_last;
	book();//ͼ�����Ĭ�Ϲ��캯��
	book(int);//ͼ����Ĺ��캯��
	book(book &);//ͼ����Ŀ������캯��
	string get_isbn(){string str(strisbn); return str;}//����isbn
	string get_name(){string str(strname); return str;}
	string get_author(){string str(strauthor); return str;}
	unsigned int get_available(){return iavailable;}//��������ڹݲ���
	unsigned int get_sum(){return isum;}//�����������
	unsigned int get_id(){return id;}//��������ڲ����
	void set_isbn();//����isbn
	void set_name();//�����������
	void set_author();//�����������
	void set_sum();//������Ĳ���
	void set_available();//��������ڹ�����
	void set_id(unsigned int i){id = i;}//��������ڲ����
	void view_info();//�������ͼ�����Ϣ
	void borrow_one(){--iavailable;}//����������һ����
	void return_one(){++iavailable;}//���������һ����
	void set_info();//����ͼ����Ϣ
};
#endif