#include <stdio.h>
int main()
{
    int n,a=0,b,c;
    scanf("%d",&n);
    b=n;
    n=10*n;
    for (n!=0;n/=10;)
    {
        a=a*10+n%10;
    }
    c=a+b;
    printf("和为：%d",c);
    return 0;
}