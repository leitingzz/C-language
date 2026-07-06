#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

#define FILENAME "D:\\c++\\Term Project\\student.txt"

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
    char id[10];

    while(1){
        printf("\n请输入调用功能对应数字：");
        scanf("%d", &choice);
 
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

        case 3:{
            printf("请输入学生学号：");
            scanf("%s", id);
            Student* curr = searchStudent(head, id);
            if(curr == NULL){
                printf("未找到该学生信息！\n");
            }else{
                printf("学号：%s\n", curr->id);
                printf("姓名：%s\n", curr->name);
                printf("性别：%s\n", curr->gender);
                printf("班级：%s\n", curr->class_name);
                printf("成绩；%.1f\n", curr->score);
            }
            break;
        }
        case 4:
            printf("请输入学生学号：");
            scanf("%s", id);
            updateStudent(head, id);
            break;
        
        case 5:
            printAll(head);
            break;

        case 0:
            saveToFile(head, FILENAME);
            freeList(head);
            printf("已保存并退出，再见！\n");
            return 0;
        default:
            printf("无效选择，请重新输入！\n");
            break;
        }
    }
    return 0;
}