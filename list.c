/* list.c -- 支持链表操作的函数 */
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* 局部函数原型 */
static void CopyToNode(Item item, Node * pnode);

void menu(void)
{
	puts("\t$************Student system************$");
	puts("\t$       0. Exit                        $");
	puts("\t$       1. DataInput                   $");
	puts("\t$       2. Search                      $");
	puts("\t$       3. Delete                      $");
	puts("\t$       4. Modify                      $");
	puts("\t$       5. Insert                      $");
	puts("\t$       6. Sort                        $");
	puts("\t$       7. Statistics                  $");
	puts("\t$       8. ScoreShow                   $");
	puts("\t$**************************************$");
	printf("\tPlease choose your operation<0-8>:");
}

/* 接口函数 */
/* 把链表设置为空 */
void InitializeList(List * plist)
{
	*plist = NULL;
}

/* 如果链表为空，返回 true */
bool ListIsEmpty(const List * plist)
{
	if (*plist == NULL)
		return true;
	else
		return false;
}

/* 如果链表已满，返回 true */
bool ListIsFull(const List * plist)
{
	Node * pt;
	bool full;

	pt = (Node *)malloc(sizeof(Node));
	if (pt == NULL)
		full = true;
	else
		full = false;
	free(pt);

	return full;
}

/* 返回节点的数量 */
unsigned int ListItemCount(const List * plist)
{
	unsigned int count = 0;
	Node * pnode = *plist;		/* 设置链表的开始 */

	while (pnode != NULL)
	{
		++count;
		pnode = pnode->next;	/* 设置下一个节点 */
	}
	return count;
}

/* 创建储存项的节点，并将其添加至由 plist 指向的链表末尾（较慢的实现） */
bool AddItem(Item item, List * plist)
{
	Node * pnew;
	Node * scan = *plist;

	pnew = (Node *) malloc(sizeof(Node));
	if (pnew == NULL)
		return false;		/* 失败时退出函数 */

	CopyToNode(item, pnew);
	pnew->next = NULL;
	if (scan == NULL)		/* 空链表，所以把 */
		*plist = pnew;		/* pnew 放在链表的开头 */
	else
	{
		while (scan->next != NULL)
			scan = scan->next;	/* 找到链表的末尾 */
		scan->next = pnew;		/* 把 pnew 添加到链表的末尾 */
	}
	return true;
}

/* 访问每个节点并执行 pfun 指向的函数 */
void Traverse(const List * plist, void(*pfun)(Item item))
{
	Node * pnode = *plist;		/* 设置链表的开始 */

	while (pnode != NULL)
	{
		(*pfun)(pnode->item);	/* 把函数应用于链表中的项 */
		pnode = pnode->next;	/* 前进到下一项 */
	}
}

/* 释放由 malloc 分配的内存	*/
/* 设置链表指针为 NULL		*/
void EmptyTheList(List * plist)
{
	Node * psave;

	while (*plist != NULL)
	{
		psave = (*plist)->next;		/* 保存下一个节点的地址	*/
		free(*plist);				/* 释放当前节点			*/
		*plist = psave;				/* 前进至下一个节点		*/
	}
}

bool Ins(List * plist, long n)
{
	Node * pnew;
	Node * find = *plist;			/* 设置插入链表的位置 */
	Node * phead = *plist;			/* 设置链表开始 */
	while (find != NULL && (n != find->item.no))
	{
		find = find->next;
	}

	if (find != NULL)
	{
		pnew = (Node *) malloc(sizeof(Node));
		if (pnew == NULL)
			return false;		/* 失败时退出函数 */
		printf("\n\tPlease enter student information:\n\t\tID):");
		scanf("%ld", &pnew->item.no);
		/* 是否重复 */
		while (phead != NULL)
		{
			if (pnew->item.no == phead->item.no)
			{
				printf("\tStudent number already exists!\n\n");
				return false;
			}
			phead = phead->next;	/* 设置下一节点 */
		}

		while (getchar() != '\n')
			continue;
		printf("\t\tname):");
		s_gets(pnew->item.name, NSIZE);
		printf("\t\tmath):");
		scanf("%f", &pnew->item.math);
		printf("\t\tyw):");
		scanf("%f", &pnew->item.yw);
		printf("\t\teng):");
		scanf("%f", &pnew->item.eng);
		pnew->item.sum = pnew->item.math + pnew->item.yw + pnew->item.eng;
		while (getchar() != '\n')
			continue;

		//填充 pnew 节点的指针域，也就是说把 pnew 的指针域指向 find 的下一个节点
		pnew->next = find->next;
		//填充 find 节点的指针域，把 find 的指针域重新指向 pnew
		find->next = pnew;
		return true;
	}
	else
		return false;
}

bool Del(List * plist, long n)
{
	Node * pnode;
	Node * find = *plist;
	while (find != NULL && (n != find->item.no))
	{
		pnode = find;
		find = find->next;
	}
	if (find != NULL)
	{
		pnode->next = find->next;
		*plist = pnode;
		free(find);
		return true;
	}
	else
		return false;
}

bool Chg(List * plist, long n) 
{
	Node * pchg = *plist;
	while (pchg != NULL)
	{
		if (n == pchg->item.no)
		{
			while (getchar() != '\n')
				continue;
			printf("\tname):");
			s_gets(pchg->item.name, NSIZE);
			printf("\tmath):");
			scanf("%f", &pchg->item.math);
			printf("\tyw):");
			scanf("%f", &pchg->item.yw);
			printf("\teng):");
			scanf("%f", &pchg->item.eng);
			pchg->item.sum = pchg->item.math +
				pchg->item.yw + pchg->item.eng;
			return true;
		}
		pchg = pchg->next;
	}
	return false;
}

bool Sch(const List * plist, long n, void(*pfun)(Item item))
{
	Node * pnode = *plist;		/* 设置链表的开始 */
	while (pnode != NULL && (n != pnode->item.no))
	{
		pnode = pnode->next;	/* 前进到下一项 */
	}
	if (pnode != NULL)
	{
		printf("\n\tID\tName\tMath\tYw\tEng\tSum\n");
		(*pfun)(pnode->item);	/* 把函数应用于链表中的项 */
		return true;
	}
	else
		return false;
	
}

char * s_gets(char * st, int n)
{
	char * ret_val;
	char * find;

	ret_val = fgets(st, n, stdin);
	if (ret_val)
	{
		find = strchr(st, '\n');
		if (find)
			*find = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
	return ret_val;
}


/* 局部函数定义 */
/* 把一个项拷贝到节点中 */
static void CopyToNode(Item item, Node * pnode)
{
	pnode->item = item;		/* 拷贝结构 */
}