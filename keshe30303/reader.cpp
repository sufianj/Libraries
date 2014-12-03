#include "reader.h"
#include <string.h>
#include <time.h>
#include "myfunction.h"
#include "mytime.h"
#include "booklist.h"
reader::reader():nbook(0)
{
	strncpy(strname, "", 20);
	strncpy(strpassword, "", 20);
	strncpy(strnum, "", 20);
	for(int ii(0); ii != 3; ++ii)
		binfo[ii].id = 0;
}

reader::reader(int i):nbook(0)
{
	if (i == 1)
	{	
		set_name();
		set_password();
		set_num();
	}
	else
	{
		strncpy(strname, "unset", 20);
		strncpy(strpassword, "888888", 7);
		strncpy(strnum, "unset", 20);
	}
	for(int ii(0); ii != 3; ++ii)
		binfo[ii].id = 0;
}

reader::reader(reader &r)
{
	nbook = r.get_nbook();
	strncpy(strname, r.get_name().c_str(), 20);
	strncpy(strpassword, r.get_password().c_str(), 6);
	strncpy(strnum, r.get_num().c_str(), 20);
	r.copy_binfo(this->binfo);
	id = r.get_id();
}

long reader::forfeit()
{
	struct tm current_t;
	struct tm btime;
	time_t t;
	t = time(NULL);
	current_t = *(localtime(&t));
	long iforfeit(0), itemp(0);
	for (int ii (0); ii != 3; ++ii)//�Ҽ���ÿ�������һ�����Ƿ��1Ԫ������Ƿ������ٽ���
	{
		if (binfo[ii].id )//id == 0��ʾû�н��顣
		{	
			btime = *(localtime(&(binfo[ii].bt )));
			itemp = ( current_t.tm_year - btime.tm_year ) * 365 \
				+ current_t.tm_yday - btime.tm_yday - 30;//�ݶ�ÿ�ν���ʮ���顣
			if (itemp > 0)
				iforfeit += itemp;
		}
	}
	return iforfeit;
}

void reader::view_info()
{
	mytime mt;
	booklist bl("book.txt");
	cout << PURFLE << endl;
	cout << "������ " << strname << " ��ţ� " << strnum 
		<< " id�� " << id << endl;
	cout << "���룺"<< strpassword << " Ƿ� " << forfeit() << " Ԫ" << endl;
	cout << " ������Ϣ��" << endl;
	for (int i(0); i != 3; ++ i)
		if (binfo[i].id )
		{
			bl.p_current = bl.p_head->p_next;
			while (bl.p_current->get_id () != binfo[i].id)
				++bl;
			cout << " ���� " << bl.p_current->get_name() << " id: " << binfo[i].id ;
			mt.set_time(&(binfo[i].bt));
			cout << "��������" << mt ;
			mt += 30;//�����������Ϊ30��
			cout << "��ٻ�������" << mt << endl;
		}
}

void reader::copy_binfo(struct borrow_info bi[3])
{
	for (int i(0); i != 3; ++i)
	{
		bi[i].bt = binfo[i].bt;
		bi[i].id = binfo[i].id;
	}
}

void reader::add_book(unsigned int iid)
{
	int i;
	for (i = 0; i != 3; ++i)
		if (binfo[i].id == 0)
			break;
	binfo[i].id = iid;
	binfo[i].bt = time(NULL);
	++nbook;
	cout << "����ɹ���" << endl;
	system("pause");
} 

void reader::delete_book(unsigned int iid)
{
	int i;
	for (i = 0; i != 3; ++i)
		if (binfo[i].id  == iid)
			break;
	binfo[i].id = 0;
	--nbook;
	cout << "����ɹ���" << endl;
	system("pause");
}

bool reader::check_book(unsigned int id)
{
	bool bflag(0);
	for (int i(0); i != 3; ++i)
		if (binfo[i].id == id)
		{
			bflag = 1;
			break;
		}
	return (bflag);
}