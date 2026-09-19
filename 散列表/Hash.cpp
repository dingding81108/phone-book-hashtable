#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <windows.h>
#define MAXSIZE  20
#define HASHSIZE 53                 //定义表长
typedef char NA[MAXSIZE];
typedef int Status;

typedef struct{
	NA name;
	NA add;
	NA tel;
}Record;

typedef struct{
	Record* elem[HASHSIZE];
	int count;
	int size;
}HashTable;

Status eq(NA x, NA y)
{
	//关键字比较，相等返回1；否则返回-1
	if (strcmp(x, y) == 0)
		return 1;
	else return -1;
}

FILE* p;
int NUM = 0;

int read_file(FILE* p, Record* a)
{
	int i;
	p = fopen("file.txt", "r");

	if (p == NULL) {
		printf("Error opening file\n");
		return 0;
	}
	for (i = 0; i < NUM; i++) {
		fread(&(a[i]), sizeof(Record), 1, p);
	}  //出错好多，溢出错误，sizeof全局变量没有赋值
	fclose(p);
	return 1;
}

int write_file(FILE* p, Record* a)
{
	int i;
	p = fopen("file.txt", "w");
	if (p == NULL)
	{
		printf("open error\n");
		return 0;
	}
	for (i = 0; i < NUM; i++)
	{
		fwrite(&(a[i]), sizeof(Record), 1, p);
	}
	fclose(p);
	return 1;
}

void freeall(FILE* p,Record* a)
{
	int i;
	for (i = 0; i < NUM; i++)
	{
		if (a != NULL)
		{
			free(a);
		}
	}
	a = NULL;
	p = fopen("file.txt", "wb");
	fclose(p);
}

void Creat_Record(Record* a)
{
	//键盘输入各人的信息
	printf("输入要添加的个数：\n");
	scanf("%d", &NUM);
	int i;
	for (i = 0; i < NUM; i++)
	{

		printf("请输入第%d个记录的用户名:\n", i+1);
		scanf("%s", a[i].name);
		printf("请输入%d个记录的电话号码:\n", i+1);
		scanf("%s", a[i].tel);
		printf("请输入第%d个记录的地址:\n", i+1);
		scanf("%s", a[i].add);
		write_file(p, a);
	}
	printf("信息录入成功！\n");
	getchar();
	system("pause");
}

void ShowInfo(Record* a)         //显示输入的用户信息
{
	int i;
	for (i = 0; i < NUM ; i++)
		printf("\n第%d个用户信息:\n 姓名：%s\n 电话号码：%s\n 联系地址：%s\n", i + 1, a[i].name, a[i].tel, a[i].add);
	system("pause");
}

void Show_face() 
{
	printf("                欢迎使用电话号码查找系统             ");
	printf("\n========================================================");
	printf("\n|             1.  添加用户信息                         |");
	printf("\n|             2.  读取所有用户信息                     |");
	printf("\n|             3.  退出程序                            |");
	printf("\n|             4.  查找并显示给定用户名的记录           |");
	printf("\n|             5.  查找并显示给定电话号码的记录         |");
	printf("\n|             0.  数据清空                           |");
	printf("\n========================================================");
	printf("\n");
}

long fold(NA s)
{//人名的折叠处理
	char* p;
	long sum = 0;
	NA ss;
	strcpy(ss, s);                            //复制字符串，不改变原字符串的大小写
	strupr(ss);                              //将字符串ss转换为大写形式
	p = ss;
	while (*p != '\0')
		sum += *p++;
	printf("\n表的地址总数%d", sum);
	return sum;
}

int NameHash(NA str)
{//姓名建表的散列函数
	long n;
	int m;
	n = fold(str);                          //先将用户名进行折叠处理
	m = n % HASHSIZE;                         //折叠处理后的数，用除留余数法构造散列函数
	return m;                             //并返回模值
}

int TelHash(NA str)
{//电话号码建表的散列函数
	long n;
	int m;
	n = atoi(str);                        //把字符串转换成整型的函数.
	m = n % HASHSIZE;                         //用除留余数法构造散列函数
	return m;                             //并返回模值
}

Status collision(int p, int& c)
{//冲突处理函数，采用二次探测再散列法解决冲突
	int i, q;
	i = c / 2 + 1;
	while (i < HASHSIZE)
	{
		if (c % 2 == 0)
		{
			c++;
			q = (p + i * i) % HASHSIZE;
			if (q >= 0) return q;
			else i = c / 2 + 1;
		}
		else
		{
			q = (p - i * i) % HASHSIZE;
			c++;
			if (q >= 0) return q;
			else i = c / 2 + 1;
		}
	}
	return -1;
}

void CreateNameTable(HashTable* H, Record* a) {
	int i, p = -1, c, q;
	H->count = 0;
	for(i = 0;i< NUM; i++)
	{
		c = 0;
		p = NameHash(a[i].name);
		q = p;
		while (H->elem[q] != NULL)
		{
			q = collision(p, c);
			if (q < 0)
			{
				printf("第%d记录无法解决冲突", i+1); //需要显示冲突次数时输出
				continue;
			}                                   //无法解决冲突，跳入下一循环(即+1)
		}
		H->elem[q] = &(a[i]);                      //求得散列地址，将信息存入
		H->count++;
		printf("第%d个记录冲突次数为%d。\n", i+1, c); //需要显示冲突次数时输出
	}
	printf("\n建表完成!\n此散列表容量为%d,当前表内存储的记录个数为%d.\n", HASHSIZE, H->count);
}

void SearchName(HashTable* H)
{//在通讯录里查找姓名关键字，若查找成功，显示信息//c用来显示冲突次数
	NA str;
	int c = 0;
	printf("\n请输入要查找记录的姓名：\n");
	scanf("%s", str);
	int p, q;
	p = NameHash(str);
	q = p;
	while ((H->elem[q] != NULL) && (eq(str, H->elem[q]->name) == -1))
		q = collision(p, c);
	if (H->elem[q] != NULL && eq(str, H->elem[q]->name) == 1)
	{
		printf("\n查找成功！\n查找过程冲突次数为%d．以下是您需要要查找的信息：\n\n", c);
		printf("姓  名：%s\n电话号码：%s\n联系地址：%s\n", H->elem[q]->name, H->elem[q]->tel, H->elem[q]->add);
	}
	else printf("\n查找失败!\n");
	system("pause");
}


void CreateTelTable(HashTable* H, Record* a)
{//建表，以电话号码为关键字，建立相应的散列表，并解决相应的冲突
	int i, p = -1,c=0, q;
	H->count = 0;
	for (i = 0; i < NUM; i++)
	{
		c = 0;
		p = TelHash(a[i].tel);
		q = p;
		while (H->elem[q] != NULL)
		{
			q = collision(p, c);
			if (q < 0)
			{
				printf("第%d记录无法解决冲突", i+1);   //需要显示冲突次数时输出
				continue;
			}                                      //无法解决冲突，跳入下一循环(即+1)
		}
		H->elem[q] = &(a[i]);                      //求得散列地址，将信息存入
		H->count++;
		printf("第%d个记录冲突次数为%d。\n", i+1,c);//需要显示冲突次数时输出
	}
	printf("\n建表完成!\n此散列表容量为%d,当前表内存储的记录个数为%d.\n", HASHSIZE, H->count);
}

void SearchTel(HashTable* H)
{//在通讯录里查找电话号码关键字，若查找成功，显示信息//c用来记录冲突次数,查找成功时显示冲突次数
	NA tele;
	int p, q;
	int c = 0;
	printf("\n请输入要查找记录的电话号码：\n");
	scanf("%s",tele);
	p = TelHash(tele);
	q = p;
	while ((H->elem[q] != NULL) && (eq(tele, H->elem[q]->tel) == -1))
		q = collision(p, c);
	if (H->elem[q] != NULL && eq(tele, H->elem[q]->tel) == 1)
	{
		printf("\n查找成功！\n查找过程冲突次数为%d．以下是您需要查找的信息：\n",c);
		printf("姓  名：%s\n电话号码：%s\n联系地址：%s\n", H->elem[q]->name, H->elem[q]->tel, H->elem[q]->add);
	}
	else printf("\n查找失败!!\n");
	system("pause");
}

int main( )
{
	int flag = 1;
	HashTable* H;
	H = (HashTable*)malloc(sizeof(HashTable));
	for (int i = 0; i < HASHSIZE; i++)
	     H->elem[i] = NULL;
	H->size = HASHSIZE;
	H->count = 0;
    Record a[MAXSIZE];
	read_file(p, a);

	while (1)
	{
		 int n;
		 system("cls");
		 Show_face();
	     printf("请输入你想要的操作：");
	     printf("\n");
		 scanf("%d", &n);
		 switch (n)
		 {
		 case 1: Creat_Record(a);
			     break;
		 case 2: ShowInfo(a);
			     break;
		 case 3: freeall(p, a);
			     break;
		 case 4: CreateNameTable(H, a);   // 以姓名建立散列表
			     SearchName(H);   //以姓名查找数据
			     break;
		 case 5: CreateTelTable(H, a);  // 以电话号码建立散列表
			     SearchTel(H);   //以电话号码查找数据
			     break;
		 case 0: return 0;
			     break;
		 default:printf("输入错误，请重新输入!");
			     printf("\n");
		 }
	 system("cls");
	} 
	system("pause");
	return 0;
}
