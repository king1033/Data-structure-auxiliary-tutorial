#include <stdio.h>

#define STACK_INIT_SIZE 10 //存储空间的初始分配量
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status; 
typedef int SElemType;

//存储结构 
typedef struct StackNode
{
    SElemType data;   //存放的数据
    struct StackNode *next;
}StackNode,*LinkStackPtr;

typedef struct LinkStack
{
    LinkStackPtr top;   //Top指针
    int count;          //栈元素计数器
}LinkStack;


//1.构建一个空栈
Status InitStack(LinkStack *S)
{
	S ->top = (LinkStackPtr)malloc(sizeof(StackNode));
	if(!S ->top)return ERROR;
	S ->top = NULL;
	S ->count = 0;
	return OK;
} 

//2.将栈置空
Status ClearStack(LinkStack *S)
{
	LinkStackPtr p,q;
 	p = S->top;
	while(p)
	{
		q = p;
		p = p ->next;
		free(q);
	}
	S ->count = 0;
	return OK;	 
}

//3.判断栈是否为空
Status StackEmpty(LinkStack S)
{
	return S.count == 0?TRUE:FALSE;
}

//4.获得栈中的元素个数
int StackLength(LinkStack S)
{
	return S.count;
}

//5.获得栈顶元素
Status GetTop(LinkStack *S,SElemType *e)
{
	 LinkStackPtr p;
	 if(StackEmpty(*S))return ERROR;
	 *e = S ->top->data;
	 p = S ->top;
	 return OK;
}

//6. 往链栈中插入元素(入栈)
Status PushStack(LinkStack *S,SElemType e)
{
	LinkStackPtr s = (LinkStackPtr)malloc(sizeof(StackNode));
	if(!s)return ERROR;
	s ->data = e;
	s ->next = S ->top;
	S ->top = s;
	S ->count++;
	return OK;
} 

//7.删除栈顶元素*出栈( 
 
Status PopStack(LinkStack *S,SElemType *e) 
{
	LinkStackPtr p;
	if(StackEmpty(*S))return ERROR;
	* e = S ->top ->data;
	p = S ->top;  //获取栈顶结点
	S ->top = S ->top ->next;  //栈顶指针下移一位 
	free(p);   //释放结点p
	S ->count--;
	return OK;
}

//8.遍历栈
Status StackTraverse(LinkStack S)
{
	LinkStackPtr p;
	p = S.top;
	while(p)
	{
 		visit(p->data);
        p=p->next;
	}
	printf("\n");
	return OK; 
} 

//定义一个打印元素的方法 
Status visit(SElemType c)
{
    printf("%d ",c);
    return OK;
}

int main()
{
	int i,e;
	LinkStack s;
	InitStack(&s);
	printf("初始化链栈，接着插入10个元素~\n");
	for(i = 1;i <= 10;i++)
	{
		PushStack(&s,i);
	}
	printf("此时栈中的元素依次为：\n");
	StackTraverse(s);
	printf("此时栈中有%d个元素\n",StackLength(s));	
	PopStack(&s,&e);
	printf("出栈，出栈结点为：%d\n",e);
	printf("此时栈中的元素依次为：\n ");
	StackTraverse(s);
	ClearStack(&s);
	printf("清空栈，此时栈中有%d个元素！\n\n",StackLength(s));	
	return 0;
}