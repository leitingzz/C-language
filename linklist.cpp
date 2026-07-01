#include <stdio.h>
#include <stdlib.h>

typedef struct LNode {
    int data;
    struct LNode *next;
} LNode, *LinkList;

// 最简单的合并方法：直接头插法
LinkList Merge(LinkList *La, LinkList *Lb) {
    LinkList Lc = NULL;  // 结果链表
    LNode *p, *q, *temp;
    
    p = *La;  // p指向La的第一个结点
    q = *Lb;  // q指向Lb的第一个结点
    
    // 当两个链表都不空时
    while (p && q) {
        if (p->data <= q->data) {
            temp = p;      // 摘除p结点
            p = p->next;   // p后移
        } else {
            temp = q;      // 摘除q结点
            q = q->next;   // q后移
        }
        // 头插法插入Lc
        temp->next = Lc;
        Lc = temp;
    }
    
    // 处理剩余结点
    while (p) {
        temp = p;
        p = p->next;
        temp->next = Lc;
        Lc = temp;
    }
    
    while (q) {
        temp = q;
        q = q->next;
        temp->next = Lc;
        Lc = temp;
    }
    
    // 原链表置空
    *La = NULL;
    *Lb = NULL;
    
    return Lc;
}

// 创建链表
void CreateList(LinkList *L, int arr[], int n) {
    *L = NULL;
    LNode *tail = NULL;
    
    for (int i = 0; i < n; i++) {
        LNode *s = (LNode*)malloc(sizeof(LNode));
        s->data = arr[i];
        s->next = NULL;
        
        if (*L == NULL) {
            *L = s;
            tail = s;
        } else {
            tail->next = s;
            tail = s;
        }
    }
}

// 打印链表
void PrintList(LinkList L) {
    LNode *p = L;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main() {
    LinkList La, Lb;
    
    int a[] = {1, 3, 5, 7};
    int b[] = {2, 4, 6, 8, 8};
    
    CreateList(&La, a, 4);
    CreateList(&Lb, b, 5);
    
    printf("La: ");
    PrintList(La);
    printf("Lb: ");
    PrintList(Lb);
    
    LinkList Lc = Merge(&La, &Lb);
    
    printf("Lc: ");
    PrintList(Lc);
    
    return 0;
}