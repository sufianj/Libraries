#ifndef MYTIME_H
#define MYTIME_H
#include <time.h>
#include <iostream>
using std::ostream;
class mytime//我的时间类
{
public:
	void set_time(time_t *pt)
	{
		t = localtime(pt);
	}
	struct tm *t;
	void operator += (int);//时间加上天数
	friend ostream & operator <<( ostream &os, const mytime &mt);
};
#endif