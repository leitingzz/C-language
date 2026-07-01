#include <stdio.h>
int Fibonacci(int n)
{int a=1,b=1,c;
for(int i=3;i<=n;i++)
{c=a+b;
a=b;
b=c;}
return b;}
int main()
{int n;
printf("请输入大于2的正整数:");
scanf("%d",&n);
printf("第%d个斐波那契数是:%d",n,Fibonacci(n));
return 0;
} 