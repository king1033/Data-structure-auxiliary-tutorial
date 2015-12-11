#include <stdio.h>
int main()
{
	//参数: n(人数),m(第m个人死),last(剩余的人数)
	int i,j,n,m,last;
	int tag[100];
	printf("输入参加的人数:\n");  
  	scanf("%d",&n);  
  	printf("输入每隔多少死一个人:\n");  
  	scanf("%d",&m);
	printf("\n准备报数！\n\n");     
  	//初始化数组
	for(i = 0;i < n;i++)
	{
		tag[i] = 1;	
 	} 
 	 //开始报数
  	j = 1;
  	last = n;
  	for(i = 0;last > 1;i++)
  	{
		if(!tag[i%n])continue;
		if(j == m)
		{
			j = 1;
			tag[i%n] = 0;
			printf("第- %d -个人自杀了，大家快鼓掌！啪啪啪！\n",(i%n)+1);
			last--;
		}
		else j++;	
 	} 
 	for(i = 0;i < n;i++)if(tag[i])break;
 	printf("第- %d -个人活下来了！\n",i+1);
 	return 0;
}