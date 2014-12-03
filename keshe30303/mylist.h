#ifndef MYLIST_H
#define MYLIST_H
#include<fstream>
#include<iostream>
#include<string.h>

using std::ios;
using std::ifstream;
using std::ofstream;
using std::cin;
using std::cout;
using std::endl;

template < class T >
class mylist
{
protected:
	int isum;//�ڵ�����
	char filename[20];
	bool bok;//����������ʼ���ɹ������⹹��ʱδ���������������ʱϴ����������
public:
	T *p_head;//ָ��ͷ����ָ��
	T *p_current;//ָ��ǰ�ڵ��ָ��
	mylist(char *);
	void operator ++();//ǰ��һ���ڵ�
	void operator --();//����һ���ڵ�
	void erase();//�������
	void show_all();//��ʾȫ���ڵ����Ϣ
	void delete_current();//ɾ����ǰ�Ľڵ㣬��ָ����һ���ڵ�
	int get_isum(){return isum;}
	~mylist();
};

template < class T >
mylist < T >::mylist(char *str)
{	
	strcpy(filename, str);
	ifstream myfile;
	myfile.open(filename, ios::binary);
	if (myfile.fail())
	{
		cout << "cannot open " << filename << endl;
		system("pause");
		return;
	}
	p_head = new T;
	p_current = p_head;
	p_current->p_last = NULL;
	p_current->p_next = new T;
	myfile.read((char *)p_current->p_next, sizeof(T));
	isum  = 1;
	while(!myfile.eof())
	{
		p_current->p_next->p_last = p_current;
		p_current->p_next->p_next = NULL;
		p_current = p_current->p_next;
		p_current->p_next = new T;
		myfile.read((char *)p_current->p_next, sizeof(T));
		++isum;
	}
	delete p_current->p_next;
	p_current->p_next = NULL;
	myfile.close();
	bok = 1;
	cout << filename << "gou zao wan bi" << endl;
}

template < class T >
void mylist< T >::operator ++()
{
	if (p_current->p_next  == NULL)
	{
		cout << "�ѵ�������β��" << endl;
		system("pause");
	}
	else
		p_current = p_current->p_next;
}

template < class T >
void mylist< T >::operator --()
{
	if (p_current->p_last->p_last == NULL)
	{
		cout << "�ѵ�������ͷ��" << endl;
		system("pause");
	}
	else
		p_current = p_current->p_last;
}

template < class T >
void mylist< T > :: delete_current()
{
	T *temp;
	if (isum == 1)
	{
		delete p_current;
		--isum;
	}
	else if (p_current->p_next == NULL)
		{
			temp = p_current->p_last;
			p_current->p_last->p_next = NULL;
			delete p_current;
			p_current = temp;
			--isum;
		}
	else if (p_current->p_last == NULL)
		{
			p_current->p_next->p_last = NULL;
			temp = p_current->p_next;
			delete p_current;
			p_current = temp;
			--isum;
		}
	else 
		{
			p_current->p_last->p_next = p_current->p_next;
			p_current->p_next->p_last = p_current->p_last;
			temp = p_current->p_next;
			delete p_current;
			p_current = temp;
			--isum;
		}
}

template < class T >
void mylist< T > :: erase()
{
	p_current = p_head;
	while (isum > 0)
		delete_current();
}

template < class T >
void mylist< T > ::show_all()
{
	T *temp;
	int i(0);
	temp = p_head->p_next;
	while (temp != NULL)
	{
		temp->view_info();
		temp = temp->p_next;
		++i;
		if (i % 3 == 0)//ÿ����ʾ3����¼��
		{
			cout << "����3����¼��";
			system("pause");
			system("cls");
		}
	}
}

template < class T >
mylist< T > :: ~mylist()
{
	if (bok)
	{
		ofstream myfile;
		myfile.open(filename, ios::binary); 
		p_current = p_head->p_next;//ͷ����ǿյġ�
		while (p_current != NULL)
		{
			myfile.write((char *)p_current, sizeof(T));
			p_current = p_current->p_next;
		}
		myfile.close();
	}
	erase();
	cout << filename << "xi gou wan bi" << endl;
}
#endif