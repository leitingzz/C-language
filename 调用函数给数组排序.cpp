#include <stdio.h>
int func(int *a,int n)
{   int firstzero=0;
    for(int i=0;i<n;i++)
    {
        if(a[i]==0)
        {
            firstzero=i;
            break;
        }
    }
    int b=0;
    for(int i=0;i<n;i++)
    {
        if(a[i]!=0)
        {
            a[b]=a[i];
            b++;
        }
    }
    for(int i=1;i<b;i++)
    {
        for(int j=1;j<b-i;j++)
        {
            if(a[j]>a[j+1])
            {
                int c=a[j+1];
                a[j+1]=a[j];
                a[j]=c;
            }
        }
    }
    for(int i=b;i<n;i++)
    {
        a[i]=0;
    }
    return firstzero;
}
int main()
{
    int a[]={1,2,7,8,5,3,0,9,6,0};
    int n=sizeof(a)/sizeof(a[0]);
    int firstzero=func(a,n);
    for(int i=0;i<n;i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n%d",firstzero);
    return 0;
}