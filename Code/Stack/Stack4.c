#include <stdio.h>

#define STACK_INIT_SIZE 10 //存储空间的初始分配量
#define STACK_INCREMENT 2 //分配增量 

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef char SElemType;
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
    if( !S->base)exit(0);
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
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

//获取栈的当前长度
int StackLength(SqStack S)
{
	return (S.top - S.base);
} 

int main()
{
	SqStack s;
	char c,e;
	InitStack(&s);
	printf("请输入中缀表达式，以#作为结束标记：\n");
	scanf("%c",&c);
	printf("输出转换后的逆波兰式：\n");
	while(c != '#')
	{	
		//这里需要考虑数字会是多位的情况
		while(c >= '0' && c <= '9')
		{
			printf("%c", c);
            scanf("%c", &c);
            if( c<'0' || c>'9' )
            {
                printf(" ");
            }
		} 
		//假如是右括号，弹出栈中的字符，直到遇到左括号 
		if( ')' == c )
        {
            PopStack(&s, &e);
            while( '(' != e )
            {
                printf("%c ", e);
                PopStack(&s, &e);
            }
        }
        //假如是加减号 ，如果栈里没元素，直接压栈，有要做下判断
	 	else if( '+'==c || '-'==c )
        {
            if( !StackLength(s) )
            {
                PushStack(&s, c);
            }
            else
            {
                do
                {
                    PopStack(&s, &e);
                    if( '(' == e )
                    {
                        PushStack(&s, e);
                    }
                    else
                    {
                        printf("%c ", e);
                    }
                }while( StackLength(s) && '('!=e );
                PushStack(&s, c);
            }
        } 
        //假如是乘除或左括号，直接压栈 
        else if( '*'==c || '/'==c || '('==c )
        {
            PushStack(&s, c);
        }
		//是#，则代表表达式输入完毕
  		else if( '#'== c )
        {
            break;
        }
		//如果是其他字符，打印字符不合法
		else
        {
            printf("\n出错：输入错误！\n");
            return -1;
        } 
		scanf("%c", &c);	 
	}
	
	//遍历栈中的剩余运算符
	while( StackLength(s))
    {
        PopStack(&s, &e);
        printf("%c ", e);
    } 
	printf("\n\n");
	return 0;
} 