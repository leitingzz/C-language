#include <stdlib.h>
#include <stdio.h>

typedef struct Node{
    int id;
    int password;
    Node* next;
}Node;

Node* creatCircularList(int n, int passwords[]){
    Node* head = NULL;
    Node* tail = NULL;

    for(int i = 0; i < n; i++){
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->id = i + 1;
        newNode->password = passwords[i];
        newNode->next = NULL;
        if(head == NULL){
            head = newNode;
            tail = newNode;
        }else{
            tail->next = newNode;
            tail = newNode;
        }
    } 

    if(tail != NULL){
        tail->next = head;
    }

    return head;
}

void Josephus(int n, int m, int passwords[]){
    Node* head = creatCircularList(n, passwords);
    Node* prev = head;
    while(prev->next != head){
        prev = prev->next;
    }
    Node* curr = head;
    printf("出列顺序：");

    for(int i = 0; i < n; i++){
        for(int j = 1; j < m; j++){
            prev = curr;
            curr = curr->next;
        }
        printf("%d",curr->id);
        if(i < n - 1){printf(",");}
        m = curr->password;
        Node* temp = curr;
        prev->next = curr->next;
        curr = curr->next;
        free(temp);
    }
    printf("\n");
}

int main(){
    int n,m;
    printf("请输入人数n和初始m:");
    scanf("%d %d",&n,&m);
    int* passwords = (int*)malloc(n * sizeof(int));
    printf("请输入%d个人的密码：",n);
    for(int i = 0; i < n; i++){
        scanf("%d",&passwords[i]);
    }

    Josephus(n, m, passwords);
    free(passwords);

    return 0;
}