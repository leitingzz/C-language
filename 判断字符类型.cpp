#include <stdio.h>
#include <ctype.h>
int main()
{char a;
    printf("请输入一个字符：");
    scanf("%c",&a);
    if (isdigit(a))
    {printf("%c是数字",a);}
    else if (islower(a))
    {printf("%c是小写字母",a);}
    else if (isupper(a))
    {printf("%c是大写字母",a);}
    else
    {printf("%c是其他字符",a);}
return 0;
}