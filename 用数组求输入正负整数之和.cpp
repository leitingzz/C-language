#include <stdio.h>
int main()
{int numbers[10];
int psum=0;
int nsum=0;
for(int i=1;i<=10;i++)
{printf("请输入第%d个整数：",i);
scanf("%d",&numbers[i]);}
for(int i=1;i<=10;i++)
if(numbers[i]>0){psum+=numbers[i];}
else if(numbers[i]<=0){nsum+=numbers[i];}
printf("正数之和为:%d\n负数之和为:%d",psum,nsum);
return 0;
}