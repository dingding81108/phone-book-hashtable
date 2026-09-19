#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <windows.h>
#define Maxsize 30
#define HashtableMaxsize 50

typedef struct {
	char name[Maxsize];
	char add[Maxsize];//地址
	int tel;//电话号
}Record;
typedef struct {
	Record* elem[HashtableMaxsize + 1];
	int size;//存储哈希表长度
	int count;//存储当前哈希表内元素个数
}Hashtable;
FILE* p;
int SizeofRecord;
int SizeofRecord1;
void Creat_Record(Record* a);
int Show_Record(Record* a);
int read_file(FILE* p, Record* a);
int write_file(FILE* p, Record* a);
void Save();
void Cls(Record* a);
void Show_face();
void CreateHash_tel(Hashtable* H, Record* a);
int Hash2(int str);
int collision(int p, int* c);
void CreateHash_name(Hashtable* H, Record* a);
int Hash1(char str[Maxsize]);
long fold(char s[Maxsize]);
void SearchHash_name(Hashtable* H);
void SearchHash_tel(Hashtable* H);
int eq(int x, int y);
int eq1(char x[Maxsize], char y[Maxsize]);
void freeall(FILE* p, Record* a);

int main()
{
	int i, flag = 0;
	Hashtable* H;
	Record basic_inf[Maxsize];
	H = (Hashtable*)malloc(sizeof(Hashtable));
	for (i = 0; i < HashtableMaxsize; i++)
		H->elem[i] = NULL;
	H->count = 0;
	H->size = HashtableMaxsize;
	Show_face();
	while (1)
	{
		int num;
		printf("请输入你想要的操作：");
		printf("\n");
		scanf("%d", &num);
		switch (num)
		{
		case 1:
			Creat_Record(basic_inf);
			SizeofRecord1 = SizeofRecord;
			break;
		case 2:
			Show_Record(basic_inf);
			break;
		case 3:
			freeall(p, basic_inf);
			break;
		case 4:
			CreateHash_name(H, basic_inf);// 以姓名建立散列表
			SearchHash_name(H);   //以姓名查找数据
			break;
		case 5:
			CreateHash_tel(H, basic_inf);  // 以电话号码建立散列表
			SearchHash_tel(H);   //以电话号码查找数据
			break;
		case 6:
			Cls(basic_inf);
			Show_face();
			break;
		case 7:
			return 0;
			break;
		default:
			printf("输入错误，请重新输入!");
			printf("\n");
		}
	}
	system("pause");
	return 0;
}
void Creat_Record(Record* a)
{
	int i = 0;
	printf("请输入记录数量：\n");
	scanf("%d", &SizeofRecord);
	for (i = 0; i < SizeofRecord; i++)
	{
		printf("请输入电话号:\n");
		scanf("%d", &a[i].tel);
		printf("请输入姓名:\n");
		scanf("%s", &a[i].name);//??
		printf("请输入地址:\n");
		scanf("%s", &a[i].add);
		write_file(p, a);
	}
}

int Show_Record(Record* a)
{
	int i;
	read_file(p, a);
	if (SizeofRecord == 0)
	{
		printf("记录已被清空\n");
		return 0;
	}
	else
		for (i = 0; i < SizeofRecord; i++)
			printf("tel:%d\tname:%s\tadd:%s\t\n", a[i].tel, a[i].name, a[i].add);
	return 1;
}
int read_file(FILE* p, Record* a)
{
	int i;
	
	p = fopen("file.txt", "rb");
	if (p == NULL) {
		printf("Error opening file\n");
		return 0;
	}
	for (i = 0; i < SizeofRecord; i++) {
		fread(&(a[i]), sizeof(Record), 1, p);
	}  //出错好多，溢出错误，sizeof全局变量没有赋值
	fclose(p);
	return 1;
}
int write_file(FILE* p, Record* a)
{
	int i;
	p = fopen("file.txt", "wb");
	if (p == NULL)
	{
		printf("open error\n");
		return 0;
	}
	for (i = 0; i < SizeofRecord; i++)
	{
		fwrite(&(a[i]), sizeof(Record), 1, p);
	}
	fclose(p);
	return 1;
}
void Save()
{//保存数据函数
	FILE* fp;
	if ((fp = fopen("file.txt", "w")) == NULL)
	{
		printf("\nERROR opening customet file");
	}
	fclose(fp);
}
void Cls(Record* a)
{//完成清屏操作
	printf("*");
	system("cls");
}
void Show_face()
{
	printf("                欢迎使用电话号码查找系统             ");
	printf("\n             1.  添加用户信息                         ");
	printf("\n             2.  读取所有用户信息                     ");
	printf("\n             3.  清除数据                             ");
	printf("\n             4.  查找并显示给定用户名的记录           ");
	printf("\n             5.  查找并显示给定电话号码的记录         ");
	printf("\n             6.  清空屏幕                             ");
	printf("\n             7.  退出程序                             ");
	printf("\n");
}
void CreateHash_tel(Hashtable* H, Record* a)
{//建表，以电话号码为关键字，建立相应的散列表，并解决相应的冲突
	int i, b = -1, c, pp;
	H->count = 0;
	if (SizeofRecord == 0)
	{
		printf("记录已被清空，请重新输入\n");
		return;
	}
	for (i = 0; i < SizeofRecord; i++)
	{
		c = 0;
		b = Hash2(a[i].tel);
		pp = b;
		while (H->elem[pp] != NULL)
		{
			pp = collision(b, &c);
			if (pp < 0)
			{
				printf("第%d记录无法解决冲突", i + 1);   //需要显示冲突次数时输出
				continue;
			}                                      //无法解决冲突，跳入下一循环(即+1)
		}
		H->elem[pp] = &(a[i]);                      //求得散列地址，将信息存入
		H->count++;
		printf("第%d个记录冲突次数为%d。\n", i + 1, c);//需要显示冲突次数时输出
	}
	printf("\n建表完成!\n此散列表容量为%d,当前表内存储的记录个数为%d.\n", HashtableMaxsize, H->count);
}
int Hash2(int str)
{//电话号码建表的散列函数
	int m;
	m = str % HashtableMaxsize;                         //用除留余数法构造散列函数
	return m;                             //并返回模值
}
int collision(int p, int* c)
{//冲突处理函数，采用二次探测再散列法解决冲突
	int i, q;
	i = (*c) / 2 + 1;
	while (i < HashtableMaxsize)
	{
		if ((*c) % 2 == 0)
		{
			(*c)++;
			q = (p + i * i) % HashtableMaxsize;
			if (q >= 0) return q;
			else i = (*c) / 2 + 1;
		}
		else
		{
			q = (p - i * i) % HashtableMaxsize;
			(*c)++;
			if (q >= 0) return q;
			else i = (*c) / 2 + 1;
		}
	}
	return -1;
}
long fold(char s[Maxsize])
{//人名的折叠处理
	char* p;
	long sum = 0;
	char ss[Maxsize];
	strcpy(ss, s);                            //复制字符串，不改变原字符串的大小写
	strupr(ss);                              //将字符串ss转换为大写形式
	p = ss;
	while (*p != '\0')
		sum += *p++;
	printf("\n表的地址总数%d", sum);
	return sum;
}
int Hash1(char str[Maxsize])
{//姓名建表的散列函数
	long n;
	int m;
	n = fold(str);                          //先将用户名进行折叠处理
	m = n % HashtableMaxsize;                         //折叠处理后的数，用除留余数法构造散列函数
	return m;                             //并返回模值
}
void CreateHash_name(Hashtable* H, Record* a)
{//建表，以人的姓名为关键字，建立相应的散列表，并解决相应的冲突
	int i, b = -1, c, pp;
	H->count = 0;
	if (SizeofRecord == 0)
	{
		printf("记录已被清空，请重新输入\n");
		return;
	}
	for (i = 0; i < SizeofRecord; i++)
	{
		c = 0;
		b = Hash1(a[i].name);
		pp = b;
		while (H->elem[pp] != NULL)
		{
			pp = collision(b, &c);
			if (pp < 0)
			{
				printf("第%d记录无法解决冲突", i + 1); //需要显示冲突次数时输出
				continue;
			}                                   //无法解决冲突，跳入下一循环(即+1)
		}
		H->elem[pp] = &(a[i]);                      //求得散列地址，将信息存入
		H->count++;
		printf("第%d个记录冲突次数为%d。\n", i + 1, c); //需要显示冲突次数时输出
	}
	printf("\n建表完成!\n此散列表容量为%d,当前表内存储的记录个数为%d.\n", HashtableMaxsize, H->count);
}
void SearchHash_tel(Hashtable* H)
{//在通讯录里查找电话号码关键字，若查找成功，显示信息//c用来记录冲突次数,查找成功时显示冲突次数
	int tele;
	int b, bb;
	int c = 0;
	printf("\n请输入要查找记录的电话号码：\n");
	scanf("%d", &tele);
	b = Hash2(tele);
	bb = b;
	if (SizeofRecord == 0)
	{
		printf("记录已被清空，请重新输入\n");
		return;
	}
	while ((H->elem[bb] != NULL) && (eq(tele, H->elem[bb]->tel) == -1))
		bb = collision(b, &c);
	if (H->elem[bb] != NULL && eq(tele, H->elem[bb]->tel) == 1)
	{
		printf("\n查找成功！\n查找过程冲突次数为%d．以下是您需要查找的信息：\n", c);
		printf("姓  名：%s\n电话号码：%d\n联系地址：%s\n", H->elem[bb]->name, H->elem[bb]->tel, H->elem[bb]->add);
	}
	else printf("\n此人不存在，查找不成功!\n");
}
int eq(int x, int y)
{
	//关键字比较，相等返回1；否则返回-1
	if (x == y)
		return 1;
	else return -1;
}
int eq1(char x[Maxsize], char y[Maxsize])
{
	//关键字比较，相等返回1；否则返回-1
	if (strcmp(x, y) == 0)
		return 1;
	else return -1;
}
void SearchHash_name(Hashtable* H)
{//在通讯录里查找姓名关键字，若查找成功，显示信息//c用来显示冲突次数
	int c = 0;
	int b, bb;
	char str[Maxsize];
	printf("\n请输入要查找记录的姓名：\n");
	scanf("%s", str);
	b = Hash1(str);
	bb = b;
	if (SizeofRecord == 0)
	{
		printf("记录已被清空，请重新输入\n");
		return;
	}
	while ((H->elem[bb] != NULL) && (eq1(str, H->elem[bb]->name) == -1))
		bb = collision(b, &c);
	if (H->elem[bb] != NULL && eq1(str, H->elem[bb]->name) == 1)
	{
		printf("\n查找成功！\n查找过程冲突次数为%d．以下是您需要要查找的信息：\n\n", c);
		printf("姓  名：%s\n电话号码：%d\n联系地址：%s\n", H->elem[bb]->name, H->elem[bb]->tel, H->elem[bb]->add);
	}
	else printf("\n此人不存在，查找不成功!\n");
}
void freeall(FILE* p, Record* a)
{
	int i;
	for (i = 0; i < SizeofRecord; i++)
	{
		if (a != NULL)
		{
			free(a);
		}
	}
	a = NULL;
	SizeofRecord = 0;
	p = fopen("file.txt", "wb");
	fclose(p);

}
