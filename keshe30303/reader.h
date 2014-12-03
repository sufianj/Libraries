#ifndef READER_H
#define READER_H
#include <time.h>
#include "myfunction.h"
#include "user.h"
class reader :public user
{
protected:
	struct borrow_info binfo[3];//������Ϣ
	int nbook;//������Ŀ
	unsigned int id;//���ߵ��ڲ���ţ��൱�����ݱ������������Ψһ��

public:
	reader();//�������Ĭ�Ϲ��캯��
	reader(int);//������Ĺ��캯��
	reader(reader &);//������Ŀ������캯��
	reader *p_last;//ָ����һ���ڵ��ָ��
	reader *p_next;//ָ����һ���ڵ��ָ��
	void copy_binfo(struct borrow_info bi[3]);
	int get_nbook(){return nbook;}//���ض��ߵĽ�����Ŀ
	unsigned int get_id(){return id;}//���ض��ߵ��ڲ����
	long forfeit();//���ض��ߵ�Ƿ��
	void view_info();//��ʾ������Ϣ
	void set_id(unsigned int i){id = i;}//���ö��ߵ��ڲ����
	void add_book(unsigned int);//��ӽ���ͼ����Ϣ
	void delete_book(unsigned int);//ɾ�����˵������Ϣ��
	bool check_book(unsigned int);//�������Ƿ��н�ĳ���顣
};
#endif