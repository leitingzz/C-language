#include <stdio.h>
int main()
{
    int i,sum,j;
    printf("输出1000以内的所有完全数：");
    for(i=2;i<=1000;i++)
    {
        sum=0;
        for(j=1;j<i;j++)
        {
            if (i%j==0)
            {
                sum+=j;
            }
        }
        if (sum==i)
        {
            printf("%d,",i);
        }
    }
    return 0;
}