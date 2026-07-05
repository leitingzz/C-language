#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

Student* creatNode(char* id, char* name, char* gender, char* class_name, float score){            //拷贝数据，字符串要传指针
    Student* node = (Student*)malloc((sizeof(Student)));
    if(node == NULL){
        printf("内存分配失败!\n");
        exit(1);            //立即终止，关闭文件
    }
    strcpy(node->id, id);
    strcpy(node->name, name);
    strcpy(node->gender, gender);
    strcpy(node->class_name, class_name);
    node->score = score;
    node->next = NULL;
    return node;
}

Student* searchStudent(Student* head, char* id){
    Student* curr = head;
    while(curr != NULL){
        if(strcmp(id, curr->id) == 0){
            return curr; 
        }
        curr = curr->next;
    }
    return NULL;
}

Student* addStudent(Student* head){

    char* id[10], name[20], gender[4], class_name[20];
    float score;

    printf("请输入学生学号：");
    scanf("%s",id);

    if(searchStudent(head, id) != NULL){
        printf("该学生信息已存在！\n");
        return head;
    }

    printf("请输入学生姓名：");
    scanf("%s",name);
    printf("请输入学生性别：");
    scanf("%s",gender);
    printf("请输入学生班级：");
    scanf("%s",class_name);
    printf("请输入学生分数：");
    scanf("%s",score);

    Student* node = creatNode(id, name, gender, class_name, score);
    node->next = head;
    return node;
    
}

Student* deleteStudent(Student* head, char* id){
    Student* curr = head;
    Student* prev = NULL;

    while(curr != NULL){
        if(strcmp(curr->id, id) == 0){
            if(prev == NULL){
                head = head->next;
            }else{
                prev->next = curr->next;
            }
            free(curr);
            printf("删除成功！\n");
            return head;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("该学生信息不存在！\m");
    return head;
}

void updateStudent(Student* head, char* id){
    char* id[10], name[20], gender[4], class_name[20];
    float score;

    Student* node = searchStudent(head, id);
    if(node == NULL){
        printf("未找到该学生信息！\n");
    }else{
        printf("请输入新学号：");
        scanf("%s", node->id);
        printf("请输入新姓名：");
        scanf("%s", node->name);
        printf("请输入新性别；");
        scanf("%s", node->gender);
        printf("请输入新班级：");
        scanf("%s", node->class_name);
        printf("请输入新成绩；");
        scanf("%f", &node->score);

        printf("修改成功！\n");
    }

}

void printAll(Student* head){
    if(head == NULL){
        printf("当前没有学生信息！\n");
    }
    printf("%-10s %-10s %-10s %-10s %-10s\n","学号","姓名","性别","班级","成绩");

    Student* curr = head;
    while(curr != NULL){
        printf("%-10s %-10s %-10s %-10s %-10f\n", curr->id, curr->name, curr->gender, curr->class_name, curr->score);
        curr = curr->next;
    }
    printf("\n");
}

void freeList(Student* head){
    Student* curr = head;
    Student* next;
    while(curr != NULL){
        next = curr->next;
        free(curr);
        curr = next;
    }    
}