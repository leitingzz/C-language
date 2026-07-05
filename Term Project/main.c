#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

#define FILENAME "student.txt"

int main(){

    printf("\n=========班级成员信息管理系统=========\n");
    printf("1.增加学生信息\n");
    printf("2.删除学生信息\n");
    printf("3.查找学生信息\n");
    printf("4.修改学生信息\n");
    printf("5.打印所有学生信息\n");
    printf("0.保存并退出程序\n");

    Student* head = loadFromFile(FILENAME);
    int choice;
    char* id;

    while(1){
        printf("请输入调用功能对应数字：");
        scanf("%d", choice);

        switch (choice)
        {
        case 1:
            head = addStudent(head);
            break;

        case 2:
            printf("请输入学生学号：");
            scanf("%s", id);
            head = deleteStudent(head, id);
            break;

        case 3:
            
        default:
            break;
        }
    }
}