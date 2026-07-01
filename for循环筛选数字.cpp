#include <stdio.h>
#include <math.h>
int main()
{int i,a,b,c;
printf("所有水仙花数分别为：\n");
for(i=100;i<=999;i++)
{a=i/100;
b=(i/10)%10;
c=i%10;
if(i==pow(a,3)+pow(b,3)+pow(c,3))
{printf("%d\n",i);}
}
return 0;
}