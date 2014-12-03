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
	for (int ii (0); ii != 3; ++ii)//我假设每本书过期一天就有欠款1元，付清欠款才能再借书
	{
		if (binfo[ii].id )//id == 0表示没有借书。
		{	
			btime = *(localtime(&(binfo[ii].bt )));
			itemp = ( current_t.tm_year - btime.tm_year ) * 365 \
				+ current_t.tm_yday - btime.tm_yday - 30;//暂定每次借三十本书。
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
	cout << "姓名： " << strname << " 编号： " << strnum 
		<< " id： " << id << endl;
	cout << "密码："<< strpassword << " 欠款： " << forfeit() << " 元" << endl;
	cout << " 借书信息：" << endl;
	for (int i(0); i != 3; ++ i)
		if (binfo[i].id )
		{
			bl.p_current = bl.p_head->p_next;
			while (bl.p_current->get_id () != binfo[i].id)
				++bl;
			cout << " 书名 " << bl.p_current->get_name() << " id: " << binfo[i].id ;
			mt.set_time(&(binfo[i].bt));
			cout << "借书日期" << mt ;
			mt += 30;//假设借书期限为30天
			cout << "最迟还书日期" << mt << endl;
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
	cout << "借书成功！" << endl;
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
	cout << "还书成功！" << endl;
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