/* list.h -- 简单链表类型的头文件 */
#ifndef LIST_H_
#define LIST_H_
#include <stdbool.h>
#include <string.h>

/* 特定数组的声明 */

#define NSIZE	16	/* 储存电影名的数组大小 */
struct film
{
	long no;
	char name[NSIZE];
	float math;
	float yw;
	float eng;
	float sum;
};

/* 一般类型定义 */

typedef struct film Item;

typedef struct node
{
	Item item;
	struct node * next;
} Node;

typedef Node * List;

/* 函数原型 */

void menu(void);

/* 操作：		初始化一个链表													*/
/* 前期条件：	plist 指向一个链表												*/
/* 后置条件：	链表初始化为空													*/
void InitializeList(List * plist);

/* 操作：		确定链表是否为空定义，plist 指向一个已初始化的链表					*/
/* 后置条件：	如果链表为空，该函数返回 true; 否则返回 false						*/
bool ListIsEmpty(const List *plist);

/* 操作：		确定链表是否已满，plist 指向一个已初始化的链表						*/
/* 后置条件：	如果链表已满，该函数返回真，否则返回假								*/
bool ListIsFull(const List *plist);

/* 操作：		确定链表中的项数，plist 指向一个已初始化的链表						*/
/* 后置条件：	该函数返回链表中的项数											*/
unsigned int ListItemCount(const List *plist);

/* 操作：		在链表的末尾添加项												*/
/* 前提条件：	item 是一个待添加至链表的项，plist 指向一个已初始化的链表			*/
/* 后置条件：	如果可以，该函数在链表末尾添加一个项，且返回 true；否则返回 false	*/
bool AddItem(Item item, List * plist);

/* 操作：		把函数作用于链表中的每一项											*/
/* 				plist 指向一个已初始化的链表										*/
/* 				pfun 指向一个函数，该函数接收一个 Item 类型的参数，且无返回值		*/
/* 后置条件：	pfun 指向的函数作用于链表中的每一项一次								*/
void Traverse(const List *plist, void(*pfun)(Item item));


/* 操作：		释放已分配的内存（如果有的话）										*/
/* 				plist 指向一个已初始化的链表										*/
/* 后置条件：	释放了为链表分配的所有内存，链表设置为空							*/
void EmptyTheList(List * plist);

/* 操作：		插入到 n 的后一个节点	*/
bool Ins(List * plist, long n);

/* 操作：		删除第 n 个节点 */
bool Del(List * plist, long n);

/* 操作：		修改第 n 个节点的值 */
bool Chg(List * plist,long n);

/* 操作：		查询学号并显示	*/
bool Sch(const List * plist, long n, void(*pfun)(Item item));

/* 菜单功能 */

void fnDataInput();

void fnSearch();

void fnDel();

void fnModify();

void fnInsert();

void fnSort();

void fnTotal();

void fnScoreShow();

char * s_gets(char * st, int n);

#endif