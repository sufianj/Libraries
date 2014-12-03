#ifndef READER_H
#define READER_H
#include <time.h>
#include "myfunction.h"
#include "user.h"
class reader :public user
{
protected:
	struct borrow_info binfo[3];//借书信息
	int nbook;//借书数目
	unsigned int id;//读者的内部编号，相当于数据表里的主键，是唯一的

public:
	reader();//读者类的默认构造函数
	reader(int);//读者类的构造函数
	reader(reader &);//读者类的拷贝构造函数
	reader *p_last;//指向上一个节点的指针
	reader *p_next;//指向下一个节点的指针
	void copy_binfo(struct borrow_info bi[3]);
	int get_nbook(){return nbook;}//返回读者的借书数目
	unsigned int get_id(){return id;}//返回读者的内部编号
	long forfeit();//返回读者的欠款
	void view_info();//显示读者信息
	void set_id(unsigned int i){id = i;}//设置读者的内部编号
	void add_book(unsigned int);//添加借书图书信息
	void delete_book(unsigned int);//删掉借了的书的信息。
	bool check_book(unsigned int);//检查读者是否有借某本书。
};
#endif