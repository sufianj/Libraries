#include "booklist.h"
#include "book.h"
#include <fstream>

using std::ifstream;
using std::ofstream;
using std:: ios;

void booklist::newone(int i)
{	
	ifstream input;
	input.open("id.txt", ios::binary);
	if (input.fail())
	{
		cout << "打开文件id.txt失败，请稍后再试！" << endl;
		system("pause");
		return;
	}
	unsigned int id;
	input.read((char *)&id, sizeof(unsigned int));
	input.close();
	++id;
	book *p_one;
	p_one = new book(i);
	p_one->set_id(id);
	p_one->p_next = p_current->p_next;
	p_one->p_last = p_current;
	p_current->p_next = p_one;
	p_current = p_one;
	++isum;
	ofstream output;
	output.open("id.txt", ios::binary);
	if (output.fail())
	{
		cout << "打开文件id.txt失败, 目前id = " << id
			<< "， 请退出并联系系统管理员修复。"<< endl;//这里有待改进，不应该让用户总是找管理员啊。
		system("pause");
		return;
	}
	output.write((char *)&id, sizeof(unsigned int));
	output.close();
}