#include <stdio.h>
int main()
{
    int i,j,k;
    int num[10];
    for (i=0;i<10;i++)
    {
        scanf("%d",&num[i]);
    }
    for (i=0;i<9;i++)
    {
        for (j=0;j<9-i;j++)
        {
            if(num[j]>num[j+1])
            {
                k=num[j];
                num[j]=num[j+1];
                num[j+1]=k;
            }
        }
    }
    for (i=0;i<10;i++)
    {
        printf("%d,",num[i]);
    }
    return 0;
}