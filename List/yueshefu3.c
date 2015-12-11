#include <stdio.h>  
  
int main()  
{  
  int n, m, i, s=0;  
  printf ("N M = "); 
  scanf("%d%d", &n, &m);  
  for (i=2; i<=n; i++)s=(s+m)%i;  
  printf ("最后一个剩下的人: %d\n", s+1);  
  return 0;  
}  