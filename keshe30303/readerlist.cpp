#include "readerlist.h"
#include "reader.h"
#include "booklist.h"
void readerlist::newone(int i)
{	
	ifstream input;
	input.open("id2.txt", ios::binary);
	if (input.fail())
	{
		cout << "���ļ�id2.txtʧ�ܣ����Ժ����ԣ�" << endl;
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
		cout << "���ļ�id2.txtʧ��, Ŀǰid = " << id
			<< "�� ���˳�����ϵϵͳ����Ա�޸���"<< endl;//�����д��Ľ�����Ӧ�����û������ҹ���Ա����
		system("pause");
		return;
	}
	output.write((char *)&id, sizeof(unsigned int));
	output.close();
}
void readerlist::menu()//���߽���
{
	system("color 2d");//���߽������̵׺���
	unsigned int ichoice(0);
	while (ichoice != 5)
	{
		system("cls");
		cout << "��ӭ����С����ͼ�����ϵͳ" << endl;
		cout << PURFLE << endl;
		cout << "������������" << endl;
		cout << "1--> �޸ĸ�����Ϣ" << endl;
		cout << "2--> �鿴������Ϣ" << endl;
		cout << "3--> ����ͼ��" << endl;
		cout << "4--> �鿴����ͼ��" << endl;
		cout << "5--> �����ϼ��˵�" << endl;
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
			cout << "�˹�����δ��ͨ��" << endl;
			system("pause");
			break;
		}
	}
}