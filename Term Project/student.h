#ifndef STUDENT_H           //防止文件嵌套导致重复定义
#define STUDNET_H

typedef struct Student{
    char id[10];
    char name[20];
    char gender[4];
    char class_name[20];
    float score;
    struct Student* next;
}Student;

//链表基本操作
Student* createNode(char *id, char *name, char *gender, char *class_name, float score);
Student* searchStudent(Student *head, char *id);
Student* addStudent(Student *head);
Student* deleteStudent(Student *head, char *id);
void updateStudent(Student *head, char *id);
void printAll(Student *head);
void freeList(Student *head);

//文件读写 
void saveToFile(Student *head, char *filename);
Student* loadFromFile(char *filename);

#endif