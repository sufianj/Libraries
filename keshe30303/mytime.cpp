#include "mytime.h"

void mytime::operator += (int i)
{
	switch (t->tm_mon + 1)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
		if (t->tm_mday + i > 31)
		{
			t->tm_mon += 1;
			t->tm_mday += i - 31;
		}
		else
			t->tm_mday += i;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		if (t->tm_mday + i > 30)
		{
			t->tm_mon += 1;
			t->tm_mday += i - 30;
		}
		else
			t->tm_mday += i;
		break;
	case 12:
		if (t->tm_mday + i > 31)
		{
			t->tm_mon = 1;
			t->tm_year += 1;
			t->tm_mday += i - 31;
		}
		else
			t->tm_mday += i;
		break;
	case 2:
		if ((t->tm_year % 4 == 0 && t->tm_year % 100 != 0) \
			||(t->tm_year % 400 == 0) )
			if (t->tm_mday + i > 29)
			{
				t->tm_mon = 3;
				t->tm_mday += i - 29;
			}
			else
				t->tm_mday += i;
		else
			if (t->tm_mday + i > 28)
			{
				t->tm_mon = 3;
				t->tm_mday += i - 28;
			}
			else
				t->tm_mday +=  i;
		break;
	}
}