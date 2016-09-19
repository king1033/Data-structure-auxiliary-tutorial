#include <stdio.h>

#define STACK_INIT_SIZE 10 //存储空间的初始分配量
#define STACK_INCREMENT 2 //分配增量 

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int SElemType;
typedef int Status;
typedef struct SqStack
{
	SElemType *base;  //栈底指针变量 
	SElemType *top;  //栈顶指针变量 
	int stacksize;  //当前可试用的最大容量 
}SqStack;

//初始化栈 
void InitStack(SqStack *S)
{
    S->base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if( !S->base )exit(0);
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
}

//获取栈的当前长度
int StackLength(SqStack S)
{
	return (S.top - S.base);
}  

//入栈
void PushStack(SqStack *S, SElemType e)
{
    if(S->top - S->base >= S->stacksize )
    {
        S->base = (SElemType *)realloc(S->base, (S->stacksize + STACK_INCREMENT) * sizeof(SElemType));
        if( !S->base )exit(0);
        S->top = S->base + S->stacksize;
        S->stacksize = S->stacksize + STACK_INCREMENT;
    }
    *(S->top) = e;
    S->top++;
}

//出栈 
void PopStack(SqStack *S, SElemType *e)
{
    if(S->top == S->base )return;
    *e = *--(S->top);
}

int main()
{
	SqStack s;
	SElemType n,m,e;
	InitStack(&s);
	printf("请输入要转换的进制：n >= 0\n");
	scanf("%d",&n);
	printf("请输入要进行转换的十进制数：\n");
	scanf("%d",&m);
	while(m)
	{
		PushStack(&s,m % n);
		m = m / n;
	}
	printf("输出十进制转%d进制后的值：\n",n);
	while(StackLength(s))
	{
		PopStack(&s,&e);
		if(n == 16)
		{
			printf("%X ",e);  //输出十六进制的结果
		}
		else printf("%d ",e);
	}
	printf("\n\n");
	return 0; 
}