#include <stdio.h>
int main()
{int i,j,k,n=0;
    for (i=1;i<=4;i++)
{for (j=1;j<=4;j++)
{if (j==i)continue;
for (k=1;k<=4;k++)
{if (k==i||k==j)continue;
printf("%d%d%d\n",i,j,k);
n++;}}}
printf("能组成%d个互不相同且无重复的三位数",n);
return 0;
}