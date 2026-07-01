#include <stdio.h>
int main()
{
    char a;
    printf("请输入+.-*/中的一个符号：");
    scanf("%c",&a);
    switch (a)
    {
case '+':printf("plus");break;        
case '-':printf("minus");break;  
case '*':printf("multiply");break;
case '/':printf("divide");break;
default:printf("Sorry you are wrong");break;
    }
    return 0;
}

