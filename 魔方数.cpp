#include <stdio.h>
int main()
{
    int n,row,col,num,lastrow,lastcol;
    printf("请输入一个奇数:");
    scanf("%d",&n);
    int number[n][n];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            number[i][j]=0;
        }
    }
    row=0;
    col=n/2;
    number[row][col]=1;
    printf("当n=%d时，魔方阵为：\n",n);
    for (num=2;num<=n*n;num++)
    {
        lastrow=row;
        lastcol=col;
        row=row-1;
        col=col+1;
        if(row<0)
        {
            row=n-1;
        }
        if(col>n-1)
        {
            col=0;
        }
        if(number[row][col]!=0||(lastrow==0&&lastcol==n-1))
        {
            row=lastrow+1;
            col=lastcol;
        }
        number[row][col]=num;
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("%d ",number[i][j]);
        }
        printf("\n");
    }
    return 0;
}