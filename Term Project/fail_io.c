#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

Student* loadFromFile(char* filename){
    FILE* fp = fopen(filename, "r");
    if(fp == NULL){
        return NULL;
    }

    Student* head = NULL;
    Student* tail = NULL;

    char id[10];
    char name[20];
    char gender[4];
    char class_name[20];
    float score;

    while(fscanf(fp, "%s %s %s %s %f", id, name, gender, class_name, &score) == 5){
        Student* newNode = creatNode(id, name, gender, class_name, score);
        if(head == NULL){
            head = newNode;
            tail = newNode;
        }else{
            tail->next = newNode;
            tail = newNode;
        }
    }

    fclose(fp);
    return head;
}

void saveToFile(Student* head, char* filename){
    FILE* fp = fopen(filename, "w");
    if(head == NULL){
        printf("文件打开失败！保存失败！");
        return;
    }
    
    Student* curr = head;
    while(curr != NULL){
        fprintf(fp, "%s %s %s %s %f\n", curr->id, curr->name, curr->gender, curr->class_name, curr->score);
        curr = curr->next;
    }

    fclose(fp);
    printf("数据已保存到%s\n",filename);
}