#include <stdio.h>
int main()
{
    int number[10],dif[10],freq[10]={0};
    int i,j,num=0,maxfreq=0,maxnum;
    printf("请输入十个正整数：");
    for(i=0;i<10;i++)
    {
        scanf("%d",&number[i]);
    }
    for(i=0;i<10;i++)
    {
        int a=0;
        for(j=0;j<num;j++)
        {
            if(number[i]==dif[j])
            {
                freq[j]++;
                a=1;
                break;
            }
        }
        if(a==0)
        {
            dif[num]=number[i];
            freq[num]=1;
            num++;
        }
    }
    for(i=0;i<=num;i++)
    {
        if(freq[i]>maxfreq)
        {
            maxfreq=freq[i];
            maxnum=dif[i];
        }
    }
    printf("互不相同的数有%d个\n",num);
    printf("%d出现次数最多\n",maxnum);
    printf("出现次数为%d\n",maxfreq);
    return 0;
}