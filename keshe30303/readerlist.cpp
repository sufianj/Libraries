#include "readerlist.h"
#include "reader.h"
#include "booklist.h"
void readerlist::newone(int i)
{	
	ifstream input;
	input.open("id2.txt", ios::binary);
	if (input.fail())
	{
		cout << "打开文件id2.txt失败，请稍后再试！" << endl;
		system("pause");
		return;
	}
	unsigned int id;
	input.read((char *)&id, sizeof(unsigned int));
	input.close();
	++id;

	reader *p_one;
	p_one = new reader(i);
	p_one->set_id(id);
	p_one->p_next = p_current->p_next;
	p_one->p_last = p_current;
	p_current->p_next = p_one;
	p_current = p_one;
	++isum;

	ofstream output;
	output.open("id2.txt", ios::binary);
	if (output.fail())
	{
		cout << "打开文件id2.txt失败, 目前id = " << id
			<< "， 请退出并联系系统管理员修复。"<< endl;//这里有待改进，不应该让用户总是找管理员啊。
		system("pause");
		return;
	}
	output.write((char *)&id, sizeof(unsigned int));
	output.close();
}
void readerlist::menu()//读者界面
{
	system("color 2d");//读者界面是绿底红字
	unsigned int ichoice(0);
	while (ichoice != 5)
	{
		system("cls");
		cout << "欢迎进入小江的图书管理系统" << endl;
		cout << PURFLE << endl;
		cout << "请输入操作序号" << endl;
		cout << "1--> 修改个人信息" << endl;
		cout << "2--> 查看个人信息" << endl;
		cout << "3--> 查找图书" << endl;
		cout << "4--> 查看所有图书" << endl;
		cout << "5--> 返回上级菜单" << endl;
		input_usint(ichoice);
		switch(ichoice)
		{
		case 1:
			p_current->set_info();break;
		case 2:
			p_current->view_info();system("pause"); break;
		case 3:
			p_current->search_book();break;
		case 4:
			p_current->view_all_book(); system("pause"); break;
		case 5:
			break;
		default :
			cout << "此功能尚未开通！" << endl;
			system("pause");
			break;
		}
	}
}