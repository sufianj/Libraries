#ifndef MYTIME_H
#define MYTIME_H
#include <time.h>
#include <iostream>
using std::ostream;
class mytime//�ҵ�ʱ����
{
public:
	void set_time(time_t *pt)
	{
		t = localtime(pt);
	}
	struct tm *t;
	void operator += (int);//ʱ���������
	friend ostream & operator <<( ostream &os, const mytime &mt);
};
#endif