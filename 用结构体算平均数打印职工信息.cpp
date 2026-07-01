#include <stdio.h>
struct worker
{
    int id;
    char name[10];
    char sex[5];
    char idcard[6];
    int salary;
};
int main()
{
    struct worker w[6]=
    {
        {1,"张三","男","11111",111},
        {2,"李四","男","22222",222},
        {3,"王五","男","33333",333},
        {4,"熊大","男","44444",444},
        {5,"熊二","男","55555",555},
        {6,"吉吉","男","66666",666},
    };
    int sum=0;
    int max=w[0].salary;
    int a=0;
    for(int i=0;i<6;i++)
    {
        sum+=w[i].salary;
        if(w[i].salary>max)
        {
            max=w[i].salary;
            a=i;
        }
    }
    printf("%d\n",sum/6);
    printf("%d %s %s %s %d",w[a].id,w[a].name,w[a].sex,w[a].idcard,w[a].salary);
    return 0;
}