#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>

//��ṹ��
struct book
{
	char strname[30];
	char strISBN[30];
	int inum;//�ڲ����
	int isum;//�ڹ�����
};

//�û��ṹ��
struct user
{
	char strname[30];
	char strpassword[30];
	char strnum[30];//ѧ��
	int nbook;//�������Ŀ
	int mybook[3];//��������������ڲ����
};

//int gi_nuser;//�ļ����û�����
int gi_last_book = 0;//�ļ������һ��ͼ��ı�ţ�����0�ͱ�ʾû���Ȿ��

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

//����Ա�Ľ���
void admin()
{
	int icmd;
	system("color F0");
	while (1)
	{
		system("cls");
		printf("please input the number of your command\n");
		printf("1. ����û�\n");
		printf("2. ɾ���û�\n");
		printf("3. ���ͼ��\n");
		printf("4. ɾ��ͼ��\n");
		printf("5. �������ͼ��\n");
		printf("6. ��������û�\n");
		printf("7. �����ϼ��˵�\n");
		printf("8. �˳�\n");
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

//���ߵ�¼�Ժ�Ľ���
void reader(struct user *p_user)
{
	int icmd;
	system("color 27");//���߽������Ѻõ���ɫ
	while (1)
	{
		system("cls");
		printf("please input the number of your command\n");
		printf("1. �޸ĸ�����Ϣ\n");
		printf("2. �鿴������Ϣ\n");
		printf("3. ����\n");
		printf("4. ����\n");
		printf("5. �������ͼ��\n");
		printf("6. �����ϼ��˵�\n");
		printf("7. �˳�\n");
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

//����û������ϵͳֻ���ɹ���Ա����û�����ѧУһ��
void add_user()
{
	struct user *p_user;
	FILE *fp_user;
	system("cls");
	if ((fp_user = fopen("user.txt","a+")) == NULL)
	{
		printf("�򲻿��û��ļ�\n");
		system("pause");
		return;
	}
	p_user = (struct user *)malloc(sizeof(struct user));
	printf("������Ҫ����û�������\n");
	scanf("%s",p_user->strname);
	printf("������Ҫ����û�������\n");
	scanf("%s",p_user->strpassword);
	printf("������Ҫ����û���ѧ��\n");
	scanf("%s",p_user->strnum);
	p_user->nbook = 0;
	memset(p_user->mybook, 0, 3);
	fwrite(p_user, sizeof(struct user), 1, fp_user);
	printf("����û��ɹ���\n");
	fclose(fp_user);
	free(p_user);
	system("pause");
	return;
}

//ɾ���û�
void delete_user()
{
	struct user *p_user;
	FILE *fp_user, *fp;
	char strtemp[30];
	int ifound = 0;
	system("cls");
	if ((fp_user = fopen("user.txt","r+")) == NULL)
	{
		printf("�򲻿��û��ļ�\n");
		system("pause");
		return;
	}
	if ((fp = fopen("temp.txt","w+")) == NULL)
	{
		printf("�򲻿��ļ�temp\n");
		system("pause");
		return;
	}
	p_user = (struct user *)malloc(sizeof(struct user));
	printf("������Ҫɾ���û�������\n");
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
			printf("�򲻿��û��ļ�\n");
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
		printf("ɾ���ɹ���\n");
	}
	else
		printf("�Ҳ�����������û�\n");
	fclose(fp);
	fclose(fp_user);
	free(p_user);
	system("pause");
	return;
}

//��¼������Ƚ�ɵ���������˳�������ֻ�ܰ�esc���ߵ�¼�����˳�
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
		printf("�������û���(����Ա��admin)\n");
		scanf("%s",strname);
		printf("����������(����Ա����123)\n");
		scanf("%s",strpassword);
		if (strcmp(strname, strAdminName) == 0 && strcmp(strpassword, strAdminPassword) == 0)
			admin();
		else
		{
			if ((fp_user = fopen("user.txt","r+")) == NULL)
			{
				printf("�򲻿��û��ļ�\n");
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
				printf("���û������ڻ������~\n");
			fclose(fp_user);
			free(p_user);
			system("pause");
		}
	}
}

//���ͼ��
void add_book()
{
	struct book *p_book;
	FILE *fp_book;
	system("cls");
	if ((fp_book = fopen("book.txt","a+")) == NULL)
	{
		printf("�򲻿�ͼ���ļ�\n");
		system("pause");
		return;
	}
	p_book = (struct book *)malloc(sizeof(struct book));
	printf("������Ҫ���ͼ��ı���\n");
	getchar();
	gets(p_book->strname);
	printf("������Ҫ���ͼ���ISBN\n");
	scanf("%s",p_book->strISBN);
	printf("�������ͼ�����Ŀ\n");
	scanf("%d",&p_book->isum);
	p_book->inum = ++gi_last_book;
	fwrite(p_book, sizeof(struct book), 1, fp_book);
	printf("���ͼ��ɹ���\n");
	fclose(fp_book);
	free(p_book);
	system("pause");
	return;
}

//ɾ��ͼ�飬���������⣬һ��С��ɾ���˼ҽ��˵��������ˡ���������~
void delete_book()
{
	struct book *p_book;
	FILE *fp_book, *fp;
	char strtemp[30];
	int ifound = 0;
	system("cls");
	if ((fp_book = fopen("book.txt","r+")) == NULL)
	{
		printf("�򲻿�ͼ���ļ�\n");
		system("pause");
		return;
	}
	if ((fp = fopen("temp.txt","w+")) == NULL)
	{
		printf("�򲻿��ļ�temp\n");
		system("pause");
		return;
	}
	p_book = (struct book *)malloc(sizeof(struct book));
	printf("������Ҫɾ��ͼ��ı����ISBN\n");
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
			printf("�򲻿�ͼ���ļ�\n");
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
		printf("ɾ���ɹ���\n");
	}
	else
		printf("�Ҳ������������\n");
	fclose(fp);
	fclose(fp_book);
	free(p_book);
	system("pause");
	return;
}

//��������û�
void print_users_all()
{
	FILE *fp_user;
	struct user *p_user;
	system("cls");
	if ((fp_user = fopen("user.txt","r")) == NULL)
	{
		printf("������˼�����򲻿��û��ļ�����ȥ��");
		system("pause");
		return;
	}
	p_user = (struct user *)malloc(sizeof(struct user));
	fread(p_user, sizeof(struct user), 1, fp_user);
	while(!feof(fp_user))
	{
		printf("����: %s ѧ��: %s ����: %s������Ŀ: %d\n",p_user->strname,
			p_user->strnum, p_user->strpassword, p_user->nbook);
		fread(p_user, sizeof(struct user), 1, fp_user);
	}
	fclose(fp_user);
	free(p_user);
	printf("�û����������������\n");
	system("pause");
	return;
}

//�������ͼ��
void print_books_all()
{
	FILE *fp_book;
	struct book *p_book;
	system("cls");
	if ((fp_book = fopen("book.txt","r")) == NULL)
	{
		printf("������˼�����򲻿�ͼ���ļ�����ȥ��");
		system("pause");
		return;
	}
	p_book = (struct book *)malloc(sizeof(struct book));
	fread(p_book, sizeof(struct book), 1, fp_book);
	while(!feof(fp_book))
	{
		printf("����: %s ISBN: %s �ڲ����: %d �ڹ�����: %d\n",p_book->strname,
			p_book->strISBN, p_book->inum, p_book->isum);
		fread(p_book, sizeof(struct book), 1, fp_book);
	}
	fclose(fp_book);
	free(p_book);
	printf("ͼ�鶼�������������\n");
	system("pause");
	return;
}

//�˻��鿴�Լ�����Ϣ
void print_info(struct user *p_user)
{
	int i;
	struct book *p_book;
	FILE *fp_book;
	system("cls");
	printf("����: %s\nѧ��: %s\n����: %s\n������Ŀ: %d\n",p_user->strname,
	p_user->strnum, p_user->strpassword, p_user->nbook);
	if ((fp_book = fopen("book.txt","r")) == NULL)
		printf("������˼���򲻿�ͼ���ļ���������ʾ��������ˡ���\n");
	else
	{
		printf("���������������Ļ�����Ϣ��\n");
		p_book = (struct book *)malloc(sizeof(struct book));
		for(i = 0; i < p_user->nbook; i++)
		{
			while(!feof(fp_book))
			{
				fread(p_book, sizeof(struct book), 1, fp_book);
				if (p_user->mybook[i] == p_book->inum)
				{
					printf("����: %s ISBN: %s �ڲ����: %d �ڹ�����: %d\n",
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

//�˻��Լ��޸���Ϣ
void modify_info(struct user *p_user)
{
	FILE *fp_temp, *fp_user;
	struct user *p_temp;
	system("cls");
	if ((fp_user = fopen("user.txt","r+")) == NULL)
	{
		printf("�򲻿��û��ļ��ء�����ȥ��\n");
		system("pause");
		return;
	}
	if ((fp_temp = fopen("temp.txt","w+")) == NULL)
	{
		printf("�򲻿���ʱ�ļ���������ȥ��\n");
		system("pause");
		return;
	}
	p_temp = (struct user *)malloc(sizeof(struct user));
	printf("�������µ��û�����~ԭ����������%s\n",p_user->strname);
	scanf("%s",p_user->strname);
	printf("�������µ������~ԭ����������%s\n",p_user->strpassword);
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
		printf("�򲻿��û��ļ�\n");
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
	printf("�����޸ĳɹ���\n");
	system("pause");
	return;
}

//����
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
		printf("���Ѿ�����3�����������ȹ黹����ͼ��������~\n");
		system("pause");
		return;
	}
	else
	{
		if ((fp_user = fopen("user.txt","r+")) == NULL)
		{
			printf("������˼���򲻿��û��ļ�\n");
			system("pause");
			return;
		}
		if ((fp_book = fopen("book.txt","r+")) == NULL)
		{
			printf("������˼���򲻿�ͼ���ļ�\n");
			fclose(fp_user);
			system("pause");
			return;
		}
		p_book = (struct book *)malloc(sizeof(struct book));
		
		//�ҵ�һ����λ��������ڲ���š�
		for (i =0; i < 3; i++)
		{
			if (i == 0)
				break;
		}
		printf("���������������������ISBN��\n");
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
				printf("�͹ٺ��������Ȿ���Ѿ������ˣ���ذ�\n");
				fclose(fp_book);
				fclose(fp_user);
				free(p_book);
				system("pause");
				return;
			}

			if ((fp_temp = fopen("temp.txt","w+")) == NULL)
			{
				printf("������˼�����򲻿���ʱ�ļ�����ذ�\n");
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
				printf("������˼�����򲻿���ʱ�ļ�����ذ�\n");
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
			printf("����ɹ���\n");
			system("pause");
			return;
		}
		else
		{
				printf("�͹ٶ����ۣ��������顣������û��˵������ذ�\n");
				fclose(fp_book);
				fclose(fp_user);
				free(p_book);
				system("pause");
				return;
		}
	}
}

//����
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
		printf("��һ���鶼û����~��ذɣ�\n");
		system("pause");
		return;
	}
	else
	{
		if ((fp_user = fopen("user.txt","r+")) == NULL)
		{
			printf("������˼���򲻿��û��ļ�\n");
			system("pause");
			return;
		}
		if ((fp_book = fopen("book.txt","r+")) == NULL)
		{
			printf("������˼���򲻿�ͼ���ļ�\n");
			fclose(fp_user);
			system("pause");
			return;
		}
		p_book = (struct book *)malloc(sizeof(struct book));
		printf("���������뻹�����������ISBN��\n");
		getchar();
		gets(strtemp);
		//���������û�Ȿ�顣
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
			//��Ҫ����������û���Ȿ�顣
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
					printf("������˼�����򲻿���ʱ�ļ�����ذ�\n");
					fclose(fp_book);
					fclose(fp_user);
					free(p_book);
					system("pause");
					return;
				}

				p_user->mybook[i] = 0;
				(p_user->nbook)--;
				(p_book->isum)++;
				//����Ͷ��Ǹ���ͼ��Ͷ��ߵ��ļ�����
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
					printf("������˼�����򲻿���ʱ�ļ�����ذ�\n");
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
				printf("����ɹ���\n");
				system("pause");
				return;
			}
			else
			{
				printf("��ɶ��Ц�أ���û�н��Ȿ�鰡����ذɣ�\n");
				fclose(fp_book);
				fclose(fp_user);
				free(p_book);
				system("pause");
				return;
			}
		}
		else
		{
				printf("�һ��ɹ���Ա���Ȿ��ɾ�ˣ������������~�Ժ��ٽ�һ�����ǣ���ذ�\n");
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
	//ϵͳ��ʼ������ȡ��ǰ��������һ������ڲ����
	if ((fp_book = fopen("book.txt","r+")) == NULL)
	{
		printf("�򲻿�ͼ���ļ���ϵͳ��ʼ��ʧ��~\n");
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
		printf("1. ��¼\n");
		printf("2. �˳�\n");
		scanf("%d",&icmd);
		switch (icmd)
		{
		case 1: login(); break;
		case 2: exit(0);
		}
	}
}