#include <stdio.h>
int main()
{   int n;
    double a=2.0,b=1.0,c,sum;
    printf("请输入要求的项数：");
    scanf("%d",&n);
for (int i=1;i<=n;i++)
{   sum+=a/b;
    c=b;
    b=a;
    a=a+c;
}
printf("前%d项和为：%lf",n,sum);
return 0;
}