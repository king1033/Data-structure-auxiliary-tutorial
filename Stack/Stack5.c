#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define STACK_INIT_SIZE 10 //存储空间的初始分配量
#define STACK_INCREMENT 2 //分配增量 
#define MAX_BUFFER_SIZE 10

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef double SElemType;
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

//判断是否为空栈
Status StackEmpty(SqStack S)
{
    return S.top == S.base?TRUE:FALSE;
} 

int main()
{
	char c;
	double d,e;
	int i = 0;
	char buffer[MAX_BUFFER_SIZE];
	SqStack s;
    InitStack(&s);
    printf("请输入所要计算表达式的逆波兰表达式，数字(包括小数)之间用空格分开，以#表示结束！\n");
    scanf("%c",&c);
    while(c!='#')
    {
    	//判断字符是否为数字或小数点 
  	 	while(isdigit(c)||c=='.')
  	 	{
 	 	 	buffer[i++]=c;
            buffer[i]='\0';	
             if(i>=10){
                printf("\n出错！超过最大缓冲区大小！\n");
                return -1;
            }
            scanf("%c",&c);
            //判断是否为空格，是的话将缓冲区里的字符串转换为double类型的数据，压入栈中 
			if(c == ' ')
			{
				d = atof(buffer);
                PushStack(&s,d);
                i=0;
                break;
			} 
 	  	}
 	  	//如果是运算符则，弹出栈中的两个元素，作为参数进行运算，将结果压入栈中 
		//另外，要注意：除法除数不能为0 
 	  	switch(c)
 	  	{
	  		case '+':
            	PopStack(&s,&d);
            	PopStack(&s,&e);
            	PushStack(&s,d+e);
            	break;
			case '-':
            	PopStack(&s,&d);
            	PopStack(&s,&e);
            	PushStack(&s,e-d);
            	break;
		 	case '*':
            	PopStack(&s,&d);
            	PopStack(&s,&e);
            	PushStack(&s,d*e);
            	break;
            case '/':
            	PopStack(&s,&d);
            	PopStack(&s,&e);
            	if(e!=0)PushStack(&s,e/d);
				else{
                	printf("\n出错，除数不能为0！");
                	return -1;
            	}
            	break;		
 	 	}
 	 	scanf("%c",&c);
    }
    PopStack(&s,&d);
    printf("\n最终结果为：%f\n",d);
	return 0;
}