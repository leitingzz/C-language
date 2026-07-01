#include <stdio.h>
int main()
{
    int n,b=0;
    int num[5];
    printf("请输入五位以内的数：");
    scanf("%d",&n);
    for(b=0;n!=0;b++)
    {
        num[b]=n%10;
        n/=10;
    }
    printf("这是一个%d位数\n",b);
    printf("按序输出：");
    for(int i=b-1;i>=0;i--)
    {
        printf("%d,",num[i]);
    }
    printf("逆序输出：");
    for(int i=0;i<b;i++)
    {
        printf("%d,",num[i]);
    }
    return 0;
}