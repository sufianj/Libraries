#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>

//书结构体
struct book
{
	char strname[30];
	char strISBN[30];
	int inum;//内部编号
	int isum;//在馆总数
};

//用户结构体
struct user
{
	char strname[30];
	char strpassword[30];
	char strnum[30];//学号
	int nbook;//借书的数目
	int mybook[3];//用来存所借书的内部编号
};

//int gi_nuser;//文件中用户总数
int gi_last_book = 0;//文件中最后一本图书的编号，这样0就表示没有这本书

void login();
void add_user();
void delete_user();
void add_book();
void delete_book();
void print_books_all();
void print_users_all();
void print_info(struct user *p_user);
void modify_info(struct user *p_user);
void borrow_book(struct user *p_user);
void return_book(struct user *p_user);
void admin();
void reader(struct user *p_user);

//管理员的界面
void admin()
{
	int icmd;
	system("color F0");
	while (1)
	{
		system("cls");
		printf("please input the number of your command\n");
		printf("1. 添加用户\n");
		printf("2. 删除用户\n");
		printf("3. 添加图书\n");
		printf("4. 删除图书\n");
		printf("5. 输出所有图书\n");
		printf("6. 输出所有用户\n");
		printf("7. 返回上级菜单\n");
		printf("8. 退出\n");
		scanf("%d",&icmd);
		switch (icmd)
		{
		case 1: add_user(); break;
		case 2: delete_user(); break;
		case 3: add_book(); break;
		case 4: delete_book(); break;
		case 5: print_books_all(); break;
		case 6: print_users_all(); break;
		case 7: return; 
		case 8: exit(0);
		}
	}
}

//读者登录以后的界面
void reader(struct user *p_user)
{
	int icmd;
	system("color 27");//读者界面是友好的绿色
	while (1)
	{
		system("cls");
		printf("please input the number of your command\n");
		printf("1. 修改个人信息\n");
		printf("2. 查看个人信息\n");
		printf("3. 借书\n");
		printf("4. 还书\n");
		printf("5. 输出所有图书\n");
		printf("6. 返回上级菜单\n");
		printf("7. 退出\n");
		printf("\n");
		scanf("%d",&icmd);
		switch (icmd)
		{
		case 1: modify_info(p_user); break;
		case 2: print_info(p_user); break;
		case 3: borrow_book(p_user); break;
		case 4: return_book(p_user); break;
		case 5: print_books_all(); break;
		case 6: login(); break;
		case 7: exit(0);
		}
	}
}

//添加用户，这个系统只能由管理员添加用户，跟学校一样
void add_user()
{
	struct user *p_user;
	FILE *fp_user;
	system("cls");
	if ((fp_user = fopen("user.txt","a+")) == NULL)
	{
		printf("打不开用户文件\n");
		system("pause");
		return;
	}
	p_user = (struct user *)malloc(sizeof(struct user));
	printf("请输入要添加用户的名字\n");
	scanf("%s",p_user->strname);
	printf("请输入要添加用户的密码\n");
	scanf("%s",p_user->strpassword);
	printf("请输入要添加用户的学号\n");
	scanf("%s",p_user->strnum);
	p_user->nbook = 0;
	memset(p_user->mybook, 0, 3);
	fwrite(p_user, sizeof(struct user), 1, fp_user);
	printf("添加用户成功！\n");
	fclose(fp_user);
	free(p_user);
	system("pause");
	return;
}

//删除用户
void delete_user()
{
	struct user *p_user;
	FILE *fp_user, *fp;
	char strtemp[30];
	int ifound = 0;
	system("cls");
	if ((fp_user = fopen("user.txt","r+")) == NULL)
	{
		printf("打不开用户文件\n");
		system("pause");
		return;
	}
	if ((fp = fopen("temp.txt","w+")) == NULL)
	{
		printf("打不开文件temp\n");
		system("pause");
		return;
	}
	p_user = (struct user *)malloc(sizeof(struct user));
	printf("请输入要删除用户的名字\n");
	scanf("%s",strtemp);
	fread(p_user, sizeof(struct user), 1, fp_user);
	while (!feof(fp_user))
	{
		if (strcmp(p_user->strname,strtemp) == 0)
			ifound = 1;
		else
			fwrite(p_user, sizeof(struct user), 1, fp);
		fread(p_user, sizeof(struct user), 1, fp_user);
	}
	fclose(fp_user);
	rewind(fp);
	if (ifound)
	{
		fread(p_user, sizeof(struct user), 1, fp);
		if ((fp_user = fopen("user.txt","w+")) == NULL)
		{
			printf("打不开用户文件\n");
			system("pause");
			fclose(fp);
			free(p_user);
			return;
		}
		while (!feof(fp))
		{
			fwrite(p_user, sizeof(struct user), 1, fp_user);
			fread(p_user, sizeof(struct user), 1, fp);
		}
		printf("删除成功！\n");
	}
	else
		printf("找不到叫这个的用户\n");
	fclose(fp);
	fclose(fp_user);
	free(p_user);
	system("pause");
	return;
}

//登录，这里比较傻，忘了设退出，所以只能按esc或者登录了再退出
void login()
{
	char strname[30];
	char strpassword[30];
	char strAdminName[10] = "admin";
	char strAdminPassword[10] = "123";
	struct user *p_user;
	FILE *fp_user;
	int iflag = 1;
	system("color 37");
	while (1)
	{
		system("cls");
		p_user = (struct user *)malloc(sizeof(struct user));
		printf("请输入用户名(管理员叫admin)\n");
		scanf("%s",strname);
		printf("请输入密码(管理员的是123)\n");
		scanf("%s",strpassword);
		if (strcmp(strname, strAdminName) == 0 && strcmp(strpassword, strAdminPassword) == 0)
			admin();
		else
		{
			if ((fp_user = fopen("user.txt","r+")) == NULL)
			{
				printf("打不开用户文件\n");
				system("pause");
				return;
			}
			fread(p_user, sizeof(struct user), 1, fp_user);
			while (!feof(fp_user))
			{
				if (strcmp(strname, p_user->strname) == 0 && strcmp(strpassword, p_user->strpassword) == 0)
				{
					reader(p_user);
					iflag = 0;
					break;
				}
				fread(p_user, sizeof(struct user), 1, fp_user);
			}
			if (iflag)
				printf("此用户不存在或密码错~\n");
			fclose(fp_user);
			free(p_user);
			system("pause");
		}
	}
}

//添加图书
void add_book()
{
	struct book *p_book;
	FILE *fp_book;
	system("cls");
	if ((fp_book = fopen("book.txt","a+")) == NULL)
	{
		printf("打不开图书文件\n");
		system("pause");
		return;
	}
	p_book = (struct book *)malloc(sizeof(struct book));
	printf("请输入要添加图书的标题\n");
	getchar();
	gets(p_book->strname);
	printf("请输入要添加图书的ISBN\n");
	scanf("%s",p_book->strISBN);
	printf("请输入此图书的数目\n");
	scanf("%d",&p_book->isum);
	p_book->inum = ++gi_last_book;
	fwrite(p_book, sizeof(struct book), 1, fp_book);
	printf("添加图书成功！\n");
	fclose(fp_book);
	free(p_book);
	system("pause");
	return;
}

//删除图书，这里有问题，一不小心删了人家借了的书就猥琐了……待完善~
void delete_book()
{
	struct book *p_book;
	FILE *fp_book, *fp;
	char strtemp[30];
	int ifound = 0;
	system("cls");
	if ((fp_book = fopen("book.txt","r+")) == NULL)
	{
		printf("打不开图书文件\n");
		system("pause");
		return;
	}
	if ((fp = fopen("temp.txt","w+")) == NULL)
	{
		printf("打不开文件temp\n");
		system("pause");
		return;
	}
	p_book = (struct book *)malloc(sizeof(struct book));
	printf("请输入要删除图书的标题或ISBN\n");
	getchar();
	gets(strtemp);
	fread(p_book, sizeof(struct book), 1, fp_book);
	while (!feof(fp_book))
	{
		if (strcmp(p_book->strname,strtemp) == 0 || strcmp(p_book->strISBN,strtemp) == 0)
			ifound = 1;
		else
			fwrite(p_book, sizeof(struct book), 1, fp);
		fread(p_book, sizeof(struct book), 1, fp_book);
	}
	fclose(fp_book);
	rewind(fp);
	if (ifound)
	{
		fread(p_book, sizeof(struct book), 1, fp);
		if ((fp_book = fopen("book.txt","w+")) == NULL)
		{
			printf("打不开图书文件\n");
			system("pause");
			fclose(fp);
			free(p_book);
			return;
		}
		while (!feof(fp))
		{
			fwrite(p_book, sizeof(struct book), 1, fp_book);
			fread(p_book, sizeof(struct book), 1, fp);
		}
		printf("删除成功！\n");
	}
	else
		printf("找不到叫这个的书\n");
	fclose(fp);
	fclose(fp_book);
	free(p_book);
	system("pause");
	return;
}

//输出所有用户
void print_users_all()
{
	FILE *fp_user;
	struct user *p_user;
	system("cls");
	if ((fp_user = fopen("user.txt","r")) == NULL)
	{
		printf("不好意思啊，打不开用户文件，回去吧");
		system("pause");
		return;
	}
	p_user = (struct user *)malloc(sizeof(struct user));
	fread(p_user, sizeof(struct user), 1, fp_user);
	while(!feof(fp_user))
	{
		printf("姓名: %s 学号: %s 密码: %s借书数目: %d\n",p_user->strname,
			p_user->strnum, p_user->strpassword, p_user->nbook);
		fread(p_user, sizeof(struct user), 1, fp_user);
	}
	fclose(fp_user);
	free(p_user);
	printf("用户都给您打出来啦！\n");
	system("pause");
	return;
}

//输出所有图书
void print_books_all()
{
	FILE *fp_book;
	struct book *p_book;
	system("cls");
	if ((fp_book = fopen("book.txt","r")) == NULL)
	{
		printf("不好意思啊，打不开图书文件，回去吧");
		system("pause");
		return;
	}
	p_book = (struct book *)malloc(sizeof(struct book));
	fread(p_book, sizeof(struct book), 1, fp_book);
	while(!feof(fp_book))
	{
		printf("标题: %s ISBN: %s 内部编号: %d 在馆总数: %d\n",p_book->strname,
			p_book->strISBN, p_book->inum, p_book->isum);
		fread(p_book, sizeof(struct book), 1, fp_book);
	}
	fclose(fp_book);
	free(p_book);
	printf("图书都给您打出来啦！\n");
	system("pause");
	return;
}

//账户查看自己的信息
void print_info(struct user *p_user)
{
	int i;
	struct book *p_book;
	FILE *fp_book;
	system("cls");
	printf("姓名: %s\n学号: %s\n密码: %s\n借书数目: %d\n",p_user->strname,
	p_user->strnum, p_user->strpassword, p_user->nbook);
	if ((fp_book = fopen("book.txt","r")) == NULL)
		printf("不好意思，打不开图书文件，不能显示您借的书了。。\n");
	else
	{
		printf("以下是您所借的书的基本信息：\n");
		p_book = (struct book *)malloc(sizeof(struct book));
		for(i = 0; i < p_user->nbook; i++)
		{
			while(!feof(fp_book))
			{
				fread(p_book, sizeof(struct book), 1, fp_book);
				if (p_user->mybook[i] == p_book->inum)
				{
					printf("标题: %s ISBN: %s 内部编号: %d 在馆总数: %d\n",
						p_book->strname, p_book->strISBN, p_book->inum, p_book->isum);
					break;
				}
			}
			rewind(fp_book);
		}
		system("pause");
		free(p_book);
		fclose(fp_book);
	}
	return;
}

//账户自己修改信息
void modify_info(struct user *p_user)
{
	FILE *fp_temp, *fp_user;
	struct user *p_temp;
	system("cls");
	if ((fp_user = fopen("user.txt","r+")) == NULL)
	{
		printf("打不开用户文件呢……回去吧\n");
		system("pause");
		return;
	}
	if ((fp_temp = fopen("temp.txt","w+")) == NULL)
	{
		printf("打不开临时文件啊……回去吧\n");
		system("pause");
		return;
	}
	p_temp = (struct user *)malloc(sizeof(struct user));
	printf("请输入新的用户名吧~原来的名字是%s\n",p_user->strname);
	scanf("%s",p_user->strname);
	printf("请输入新的密码吧~原来的密码是%s\n",p_user->strpassword);
	scanf("%s",p_user->strpassword);
	fread(p_temp,sizeof(struct user), 1, fp_user);
	while (!feof(fp_user))
	{
		if (strcmp(p_temp->strnum, p_user->strnum) == 0)
			fwrite(p_user, sizeof(struct user), 1, fp_temp);
		else
			fwrite(p_temp, sizeof(struct user), 1, fp_temp);
		fread(p_temp,sizeof(struct user), 1, fp_user);
	}
	rewind(fp_temp);
	fclose(fp_user);
	if ((fp_user = fopen("user.txt","w+")) == NULL)
	{
		printf("打不开用户文件\n");
		fclose(fp_temp);
		free(p_temp);
		system("pause");
		return;
	}
	fread(p_temp,sizeof(struct user), 1, fp_temp);
	while (!feof(fp_temp))
	{
		fwrite(p_temp, sizeof(struct user), 1, fp_user);
		fread(p_temp, sizeof(struct user), 1, fp_temp);
	}
	fclose(fp_temp);
	fclose(fp_user);
	free(p_temp);
	printf("资料修改成功！\n");
	system("pause");
	return;
}

//借书
void borrow_book(struct user *p_user)
{
	FILE *fp_book, *fp_user, *fp_temp;
	struct book *p_book, *p_temp_b;
	struct user *p_temp_u;
	char strtemp[30];
	int ifound = 0, i;
	system("cls");
	if (p_user->nbook >= 3)
	{
		printf("您已经借了3本书啦，请先归还部分图书再来吧~\n");
		system("pause");
		return;
	}
	else
	{
		if ((fp_user = fopen("user.txt","r+")) == NULL)
		{
			printf("不好意思，打不开用户文件\n");
			system("pause");
			return;
		}
		if ((fp_book = fopen("book.txt","r+")) == NULL)
		{
			printf("不好意思，打不开图书文件\n");
			fclose(fp_user);
			system("pause");
			return;
		}
		p_book = (struct book *)malloc(sizeof(struct book));
		
		//找到一个空位来存书的内部编号。
		for (i =0; i < 3; i++)
		{
			if (i == 0)
				break;
		}
		printf("请输入你想借的书的书名或ISBN吧\n");
		getchar();
		gets(strtemp);

		fread(p_book, sizeof(struct book), 1, fp_book);
		while(!feof(fp_book))
		{
			if (strcmp(p_book->strname, strtemp) == 0 || strcmp(p_book->strISBN, strtemp) == 0)
			{
				ifound = 1;
				break;
			}
			fread(p_book, sizeof(struct book), 1, fp_book);
		}

		if (ifound)
		{
			if (p_book->isum == 0)
			{
				printf("客官好眼力，这本书已经借光光了，请回吧\n");
				fclose(fp_book);
				fclose(fp_user);
				free(p_book);
				system("pause");
				return;
			}

			if ((fp_temp = fopen("temp.txt","w+")) == NULL)
			{
				printf("不好意思啊，打不开临时文件，请回吧\n");
				fclose(fp_book);
				fclose(fp_user);
				free(p_book);
				system("pause");
				return;
			}

			p_user->mybook[i] = p_book->inum;
			(p_user->nbook)++;
			(p_book->isum)--;

			p_temp_u = (struct user *)malloc(sizeof(struct user));
			fread(p_temp_u, sizeof(struct user), 1, fp_user);
			while (!feof(fp_user))
			{
				if (strcmp(p_temp_u->strnum, p_user->strnum) == 0)
					fwrite(p_user, sizeof(struct user), 1, fp_temp);
				else
					fwrite(p_temp_u, sizeof(struct user), 1, fp_temp);
				fread(p_temp_u, sizeof(struct user), 1, fp_user);
			}
			rewind(fp_temp);
			rewind(fp_user);

			fread(p_temp_u, sizeof(struct user), 1, fp_temp);
			while (!feof(fp_temp))
			{
				fwrite(p_temp_u, sizeof(struct user), 1, fp_user);
				fread(p_temp_u, sizeof(struct user), 1, fp_temp);
			}
			fclose(fp_temp);
			fclose(fp_user);
			free(p_temp_u);

			if ((fp_temp = fopen("temp.txt","w+")) == NULL)
			{
				printf("不好意思啊，打不开临时文件，请回吧\n");
				fclose(fp_book);
				free(p_book);
				system("pause");
				return;
			}
			p_temp_b = (struct book *)malloc(sizeof(struct book));
			rewind(fp_book);
			fread(p_temp_b, sizeof(struct book), 1, fp_book);
			while (!feof(fp_book))
			{
				if (p_temp_b->inum == p_book->inum)
					fwrite(p_book, sizeof(struct book), 1, fp_temp);
				else
					fwrite(p_temp_b, sizeof(struct book), 1, fp_temp);
				fread(p_temp_b, sizeof(struct book), 1, fp_book);
			}
			rewind(fp_temp);
			rewind(fp_book);

			fread(p_temp_b, sizeof(struct book), 1, fp_temp);
			while (!feof(fp_temp))
			{
				fwrite(p_temp_b, sizeof(struct book), 1, fp_book);
				fread(p_temp_b, sizeof(struct book), 1, fp_temp);
			}
			fclose(fp_temp);
			fclose(fp_book);
			free(p_temp_b);
			free(p_book);
			printf("借书成功啦\n");
			system("pause");
			return;
		}
		else
		{
				printf("客官斗鸡眼，哪来的书。。本馆没听说过，请回吧\n");
				fclose(fp_book);
				fclose(fp_user);
				free(p_book);
				system("pause");
				return;
		}
	}
}

//还书
void return_book(struct user *p_user)
{
	FILE *fp_book, *fp_user, *fp_temp;
	struct book *p_book, *p_temp_b;
	struct user *p_temp_u;
	char strtemp[30];
	int ifound = 0, i, ifound2 = 0;
	system("cls");
	if (p_user->nbook == 0)
	{
		printf("您一本书都没借嘛~请回吧！\n");
		system("pause");
		return;
	}
	else
	{
		if ((fp_user = fopen("user.txt","r+")) == NULL)
		{
			printf("不好意思，打不开用户文件\n");
			system("pause");
			return;
		}
		if ((fp_book = fopen("book.txt","r+")) == NULL)
		{
			printf("不好意思，打不开图书文件\n");
			fclose(fp_user);
			system("pause");
			return;
		}
		p_book = (struct book *)malloc(sizeof(struct book));
		printf("请输入你想还的书的书名或ISBN吧\n");
		getchar();
		gets(strtemp);
		//看看书库有没这本书。
		fread(p_book, sizeof(struct book), 1, fp_book);
		while(!feof(fp_book))
		{
			if (strcmp(p_book->strname, strtemp) == 0 || strcmp(p_book->strISBN, strtemp) == 0)
			{
				ifound = 1;
				break;
			}
			fread(p_book, sizeof(struct book), 1, fp_book);
		}

		if (ifound)
		{
			//还要看看读者有没借这本书。
			for (i = 0; i < 3; i++)
			{
				if (p_user->mybook[i] == p_book->inum)
				{
					ifound2 = 1;
					break;
				}
			}
			if (ifound2)
			{
				if ((fp_temp = fopen("temp.txt","w+")) == NULL)
				{
					printf("不好意思啊，打不开临时文件，请回吧\n");
					fclose(fp_book);
					fclose(fp_user);
					free(p_book);
					system("pause");
					return;
				}

				p_user->mybook[i] = 0;
				(p_user->nbook)--;
				(p_book->isum)++;
				//后面就都是更新图书和读者的文件啦。
				p_temp_u = (struct user *)malloc(sizeof(struct user));
				fread(p_temp_u, sizeof(struct user), 1, fp_user);
				while (!feof(fp_user))
				{
					if (strcmp(p_temp_u->strnum, p_user->strnum) == 0)
						fwrite(p_user, sizeof(struct user), 1, fp_temp);
					else
						fwrite(p_temp_u, sizeof(struct user), 1, fp_temp);
					fread(p_temp_u, sizeof(struct user), 1, fp_user);
				}
				rewind(fp_temp);
				rewind(fp_user);

				fread(p_temp_u, sizeof(struct user), 1, fp_temp);
				while (!feof(fp_temp))
				{
					fwrite(p_temp_u, sizeof(struct user), 1, fp_user);
					fread(p_temp_u, sizeof(struct user), 1, fp_temp);
				}
				fclose(fp_temp);
				fclose(fp_user);
				free(p_temp_u);

				if ((fp_temp = fopen("temp.txt","w+")) == NULL)
				{
					printf("不好意思啊，打不开临时文件，请回吧\n");
					fclose(fp_book);
					free(p_book);
					system("pause");
					return;
				}
				p_temp_b = (struct book *)malloc(sizeof(struct book));
				rewind(fp_book);
				fread(p_temp_b, sizeof(struct book), 1, fp_book);
				while (!feof(fp_book))
				{
					if (p_temp_b->inum == p_book->inum)
						fwrite(p_book, sizeof(struct book), 1, fp_temp);
					else
						fwrite(p_temp_b, sizeof(struct book), 1, fp_temp);
					fread(p_temp_b, sizeof(struct book), 1, fp_book);
				}
				rewind(fp_temp);
				rewind(fp_book);

				fread(p_temp_b, sizeof(struct book), 1, fp_temp);
				while (!feof(fp_temp))
				{
					fwrite(p_temp_b, sizeof(struct book), 1, fp_book);
					fread(p_temp_b, sizeof(struct book), 1, fp_temp);
				}
				fclose(fp_temp);
				fclose(fp_book);
				free(p_temp_b);
				free(p_book);
				printf("还书成功啦\n");
				system("pause");
				return;
			}
			else
			{
				printf("开啥玩笑呢，您没有借这本书啊！请回吧！\n");
				fclose(fp_book);
				fclose(fp_user);
				free(p_book);
				system("pause");
				return;
			}
		}
		else
		{
				printf("我怀疑管理员把这本书删了，算啦，送你吧~以后少借一本就是！请回吧\n");
				fclose(fp_book);
				fclose(fp_user);
				free(p_book);
				system("pause");
				return;
		}
	}
}

void main()
{
	int icmd = 0;
	FILE *fp_book;
	struct book *p_book;
	//系统初始化：获取当前书库中最后一本书的内部编号
	if ((fp_book = fopen("book.txt","r+")) == NULL)
	{
		printf("打不开图书文件，系统初始化失败~\n");
		system("pause");
		exit(0);
	}
	p_book = (struct book *)malloc(sizeof(struct book));
	fread(p_book, sizeof(struct book), 1, fp_book);
	while (!feof(fp_book))
	{
		gi_last_book = p_book->inum;
		fread(p_book, sizeof(struct book), 1, fp_book);
	}
	fclose(fp_book);
	free(p_book);
	while(icmd != 2)
	{
		system("cls");
		printf("please input the number of your command\n");
		printf("1. 登录\n");
		printf("2. 退出\n");
		scanf("%d",&icmd);
		switch (icmd)
		{
		case 1: login(); break;
		case 2: exit(0);
		}
	}
}