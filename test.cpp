#include <stdio.h>
#include <stdlib.h>
struct book
{
    int price;
    struct book *next;
    
};
int main(){
    struct book *p=(struct book *)malloc(sizeof(struct book));
    if (p == NULL)
    {
        return 1;
    }
    
    p->price = 50;
    printf("书本价格为%d",p->price);
    free(p);
    return 0;
}
