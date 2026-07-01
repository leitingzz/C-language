#include <stdio.h>
#include <ctype.h>
void count(char *str,int *a)
{
    for (int i=0;i<5;i++)
    {
        a[i]=0;
    }
    for(int i=0;str[i]!='\0';i++)
    {
        if(isupper(str[i]))
        {
            a[0]++;
        }
        else if(islower(str[i]))
        {
            a[1]++;
        }
        else if(str[i]==' ')
        {
            a[2]++;
        }
        else if(isdigit(str[i]))
        {
            a[3]++;
        }
        else
        {
            a[4]++;
        }
    }
}
int main()
{
    char str[100];
    int a[5];
    fgets(str,sizeof(str),stdin);
    count(str,a);
    printf("%d\n",a[0]);
    printf("%d\n",a[1]);
    printf("%d\n",a[2]);
    printf("%d\n",a[3]);
    printf("%d\n",a[4]);
    return 0;
}