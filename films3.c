/* films3.c -- 使用抽象数据类型(ADT)风格的链表 */
/* 与 list.c 一起编译 */
#include <stdio.h>
#include <stdlib.h>		/* 提供 exit() 的原型	*/
#include "list.h"		/* 定义 List, Item		*/
void showmovies(Item item);

List movies;
Item temp;

int main(void)
{
	

	/* 初始化 */
	InitializeList(&movies);
	if (ListIsFull(&movies))
	{
		fprintf(stderr, "No memory available! Bye!\n");
		exit(1);
	}

	int n;
	do
	{
		menu();
		scanf("%d", &n);
		while (getchar() != '\n')
			continue;
		switch (n)
		{
			case 1:	fnDataInput();
					break;
			case 2: fnSearch();
					break;
			case 3: fnDel();
					break;
			case 4: fnModify();
					break;
			case 5: fnInsert();
					break;
			case 6: fnSort();
					break;
			case 7: fnTotal();
					break;
			case 8: fnScoreShow();
					break;
			default: break;
		}
	}
	while(n);

	/* 清理 */
	EmptyTheList(&movies);
	printf("Bye!\n");
	getchar();

	return 0;
}

void fnDataInput(void)
{
	char ch[2];
	//while (s_gets(temp.title, TSIZE) != NULL && temp.title[0] != '\0')
	do
	{
		Node * nhead = movies;			/* 设置链表开始 */
		printf("\n\tPlease enter student information:\n\t\tID):");
		scanf("%ld", &temp.no);
		if (nhead != NULL)
			while (nhead != NULL)
			{
				if (temp.no == nhead->item.no)
				{
					printf("\tStudent number already exists!\n\n");
					return;
				}
				nhead = nhead->next;	/* 设置下一节点 */
			}
		while (getchar() != '\n')
			continue;
		printf("\t\tname):");
		s_gets(temp.name, NSIZE);
		printf("\t\tmath):");
		scanf("%f", &temp.math);
		printf("\t\tyw):");
		scanf("%f", &temp.yw);
		printf("\t\teng):");
		scanf("%f", &temp.eng);
		temp.sum = temp.math + temp.yw + temp.eng;
		while (getchar() != '\n')
			continue;

		/* 上面一整块可以写进 list.c */

		if (AddItem(temp, &movies) == false)
		{
			fprintf(stderr, "Problem allocating memory\n");
			break;
		}
		if (ListIsFull(&movies))
		{
			puts("The list is now full.");
			break;
		}
		printf("\tEnter next movie title (y/n):");
		s_gets(ch, 2);
	} while (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0);
}

void fnSearch(void)
{
	long snum;
	printf("\n\tPlease enter the student number:");
	scanf("%ld", &snum);
	if (Sch(&movies, snum, showmovies) == false)
		printf("\tNode does not exist!\n");
	else
		getchar();
}

void fnDel(void)
{
	long snum;
	printf("\n\tPlease enter the student number:");
	scanf("%ld", &snum);
	if (Del(&movies, snum) == false)
		printf("\tNode does not exist!\n");
	getchar();
}

void fnModify(void)
{
	long snum;
	printf("\n\tPlease enter the student number:");
	scanf("%ld", &snum);
	if (Chg(&movies, snum) == false)
		printf("\tNode does not exist!\n");
	getchar();
}

void fnInsert(void)
{
	long snum;
	if (ListIsEmpty(&movies))
		printf("\tNo data entered\n");
	else
	{
		printf("\n\tPlease enter the student number:");
		scanf("%ld", &snum);
		if (Ins(&movies, snum) == false)
			printf("\tNode does not exist!\n");
	}
	
	getchar();
}

void fnSort()
{

}

void fnTotal()
{

}

void fnScoreShow()
{
	if (ListIsEmpty(&movies))
		printf("\tNo data entered\n");
	else
	{
		printf("\n\tID\tName\tMath\tYw\tEng\tSum\n");
		Traverse(&movies, showmovies);
	}
	printf("\tYou entered %d movies.\n", ListItemCount(&movies));	/* 计数器 */
	getchar();
}

void showmovies(Item item)
{
	printf("\t%-8ld%-8s%-8.1lf%-8.1lf%-8.1lf%-8.1lf\n", 
			item.no, item.name, item.math, item.yw, item.eng, item.sum);
}
