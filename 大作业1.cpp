#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LEN 20
#define MAX_COURSES 5
#define COURSE_NAMES {"数学", "语文", "英语", "物理", "化学"}

// 学生结构体
typedef struct {
    int id;                     // 学号
    char name[MAX_NAME_LEN];    // 姓名
    int age;                    // 年龄
    float scores[MAX_COURSES];  // 各科成绩
    float total;                // 总分
    float average;              // 平均分
} Student;

Student students[MAX_STUDENTS];  // 学生数组
int student_count = 0;           // 当前学生数量
char course_names[][10] = COURSE_NAMES;

// 函数声明
void show_menu();
void add_student();
void delete_student();
void modify_student();
void search_student();
void show_all_students();
void sort_students();
void statistics();
void save_to_file();
void load_from_file();

// 工具函数
int find_student_by_id(int id);
void calculate_student_stats(Student *stu);
void input_student_info(Student *stu);
void display_student(Student stu);

// 排序算法
void bubble_sort(int by_total, int course_index);
void quick_sort(int left, int right, int by_total, int course_index);
int partition(int left, int right, int by_total, int course_index);

int main() {
    int choice;
    
    // 从文件加载数据
    load_from_file();
    
    printf("========== 学生信息管理系统 ==========\n");
    
    while (1) {
        show_menu();
        printf("请输入选择: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                add_student();
                break;
            case 2:
                delete_student();
                break;
            case 3:
                modify_student();
                break;
            case 4:
                search_student();
                break;
            case 5:
                show_all_students();
                break;
            case 6:
                sort_students();
                break;
            case 7:
                statistics();
                break;
            case 8:
                save_to_file();
                break;
            case 9:
                load_from_file();
                break;
            case 0:
                printf("感谢使用！再见！\n");
                save_to_file();  // 退出前保存
                return 0;
            default:
                printf("输入错误，请重新输入！\n");
        }
        
        printf("\n按回车键继续...");
        getchar();
        getchar();
    }
    
    return 0;
}

// 显示菜单
void show_menu() {
    printf("\n========== 主菜单 ==========\n");
    printf("1. 添加学生信息\n");
    printf("2. 删除学生信息\n");
    printf("3. 修改学生信息\n");
    printf("4. 查询学生信息\n");
    printf("5. 显示所有学生\n");
    printf("6. 排序学生信息\n");
    printf("7. 统计信息\n");
    printf("8. 保存到文件\n");
    printf("9. 从文件加载\n");
    printf("0. 退出系统\n");
    printf("===========================\n");
}

// 添加学生
void add_student() {
    if (student_count >= MAX_STUDENTS) {
        printf("学生数量已达上限(%d)！\n", MAX_STUDENTS);
        return;
    }
    
    Student new_student;
    printf("\n=== 添加新学生 ===\n");
    
    // 输入学号
    while (1) {
        printf("请输入学号: ");
        scanf("%d", &new_student.id);
        
        if (find_student_by_id(new_student.id) != -1) {
            printf("该学号已存在！请重新输入。\n");
        } else {
            break;
        }
    }
    
    // 输入姓名
    printf("请输入姓名: ");
    scanf("%s", new_student.name);
    
    // 输入年龄
    printf("请输入年龄: ");
    scanf("%d", &new_student.age);
    
    // 输入各科成绩
    printf("请输入%d门课程成绩:\n", MAX_COURSES);
    for (int i = 0; i < MAX_COURSES; i++) {
        printf("%s: ", course_names[i]);
        scanf("%f", &new_student.scores[i]);
    }
    
    // 计算总分和平均分
    calculate_student_stats(&new_student);
    
    // 添加到数组
    students[student_count++] = new_student;
    printf("学生添加成功！\n");
}

// 删除学生
void delete_student() {
    if (student_count == 0) {
        printf("当前没有学生信息！\n");
        return;
    }
    
    int id, index;
    printf("\n=== 删除学生 ===\n");
    printf("请输入要删除的学生学号: ");
    scanf("%d", &id);
    
    index = find_student_by_id(id);
    if (index == -1) {
        printf("未找到学号为%d的学生！\n", id);
        return;
    }
    
    printf("找到学生: \n");
    display_student(students[index]);
    
    char confirm;
    printf("确认删除？(y/n): ");
    scanf(" %c", &confirm);
    
    if (tolower(confirm) == 'y') {
        // 移动后面的元素
        for (int i = index; i < student_count - 1; i++) {
            students[i] = students[i + 1];
        }
        student_count--;
        printf("删除成功！\n");
    } else {
        printf("取消删除。\n");
    }
}

// 修改学生信息
void modify_student() {
    if (student_count == 0) {
        printf("当前没有学生信息！\n");
        return;
    }
    
    int id, index;
    printf("\n=== 修改学生信息 ===\n");
    printf("请输入要修改的学生学号: ");
    scanf("%d", &id);
    
    index = find_student_by_id(id);
    if (index == -1) {
        printf("未找到学号为%d的学生！\n", id);
        return;
    }
    
    printf("当前信息: \n");
    display_student(students[index]);
    
    printf("\n输入新信息（直接回车保持原值）:\n");
    
    // 临时存储原值
    Student old_student = students[index];
    Student new_student = old_student;
    
    // 修改姓名
    char temp[50];
    printf("姓名[%s]: ", old_student.name);
    getchar();  // 清除缓冲区
    fgets(temp, sizeof(temp), stdin);
    if (temp[0] != '\n') {
        temp[strcspn(temp, "\n")] = 0;  // 去除换行符
        strcpy(new_student.name, temp);
    }
    
    // 修改年龄
    printf("年龄[%d]: ", old_student.age);
    fgets(temp, sizeof(temp), stdin);
    if (temp[0] != '\n') {
        new_student.age = atoi(temp);
    }
    
    // 修改成绩
    printf("修改各科成绩（直接回车保持原值）:\n");
    for (int i = 0; i < MAX_COURSES; i++) {
        printf("%s[%.1f]: ", course_names[i], old_student.scores[i]);
        fgets(temp, sizeof(temp), stdin);
        if (temp[0] != '\n') {
            new_student.scores[i] = atof(temp);
        }
    }
    
    // 重新计算统计信息
    calculate_student_stats(&new_student);
    
    students[index] = new_student;
    printf("修改成功！\n");
}

// 查询学生
void search_student() {
    if (student_count == 0) {
        printf("当前没有学生信息！\n");
        return;
    }
    
    int choice, id;
    char name[MAX_NAME_LEN];
    
    printf("\n=== 查询学生 ===\n");
    printf("1. 按学号查询\n");
    printf("2. 按姓名查询\n");
    printf("请选择查询方式: ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        printf("请输入学号: ");
        scanf("%d", &id);
        
        int index = find_student_by_id(id);
        if (index == -1) {
            printf("未找到学号为%d的学生！\n", id);
        } else {
            printf("查询结果: \n");
            display_student(students[index]);
        }
    } else if (choice == 2) {
        printf("请输入姓名: ");
        scanf("%s", name);
        
        int found = 0;
        for (int i = 0; i < student_count; i++) {
            if (strcmp(students[i].name, name) == 0) {
                if (!found) {
                    printf("查询结果: \n");
                    found = 1;
                }
                display_student(students[i]);
            }
        }
        
        if (!found) {
            printf("未找到姓名为%s的学生！\n", name);
        }
    } else {
        printf("无效的选择！\n");
    }
}

// 显示所有学生
void show_all_students() {
    if (student_count == 0) {
        printf("当前没有学生信息！\n");
        return;
    }
    
    printf("\n=== 所有学生信息 ===\n");
    printf("学号\t姓名\t年龄");
    for (int i = 0; i < MAX_COURSES; i++) {
        printf("\t%s", course_names[i]);
    }
    printf("\t总分\t平均分\n");
    
    printf("-------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < student_count; i++) {
        printf("%d\t%s\t%d", students[i].id, students[i].name, students[i].age);
        for (int j = 0; j < MAX_COURSES; j++) {
            printf("\t%.1f", students[i].scores[j]);
        }
        printf("\t%.1f\t%.1f\n", students[i].total, students[i].average);
    }
}

// 排序学生
void sort_students() {
    if (student_count == 0) {
        printf("当前没有学生信息！\n");
        return;
    }
    
    int choice1, choice2;
    
    printf("\n=== 排序学生 ===\n");
    printf("1. 按总分排序\n");
    printf("2. 按单科成绩排序\n");
    printf("请选择排序依据: ");
    scanf("%d", &choice1);
    
    printf("\n1. 冒泡排序\n");
    printf("2. 快速排序\n");
    printf("请选择排序算法: ");
    scanf("%d", &choice2);
    
    int course_index = -1;
    if (choice1 == 2) {
        printf("\n请选择科目:\n");
        for (int i = 0; i < MAX_COURSES; i++) {
            printf("%d. %s\n", i + 1, course_names[i]);
        }
        printf("请选择: ");
        scanf("%d", &course_index);
        course_index--;  // 转换为0-based索引
    }
    
    // 执行排序
    if (choice2 == 1) {
        bubble_sort(choice1 == 1, course_index);
        printf("冒泡排序完成！\n");
    } else if (choice2 == 2) {
        quick_sort(0, student_count - 1, choice1 == 1, course_index);
        printf("快速排序完成！\n");
    }
    
    // 显示排序后的结果
    show_all_students();
}

// 统计信息
void statistics() {
    if (student_count == 0) {
        printf("当前没有学生信息！\n");
        return;
    }
    
    printf("\n=== 班级统计信息 ===\n");
    
    // 计算每门课程的总分和平均分
    float course_totals[MAX_COURSES] = {0};
    float course_averages[MAX_COURSES];
    float course_highest[MAX_COURSES];
    float course_lowest[MAX_COURSES];
    
    // 初始化最高分和最低分
    for (int i = 0; i < MAX_COURSES; i++) {
        course_highest[i] = students[0].scores[i];
        course_lowest[i] = students[0].scores[i];
    }
    
    int fail_counts[MAX_COURSES] = {0};
    float total_total = 0;
    
    // 遍历所有学生
    for (int i = 0; i < student_count; i++) {
        total_total += students[i].total;
        
        for (int j = 0; j < MAX_COURSES; j++) {
            course_totals[j] += students[i].scores[j];
            
            if (students[i].scores[j] > course_highest[j]) {
                course_highest[j] = students[i].scores[j];
            }
            if (students[i].scores[j] < course_lowest[j]) {
                course_lowest[j] = students[i].scores[j];
            }
            if (students[i].scores[j] < 60) {
                fail_counts[j]++;
            }
        }
    }
    
    // 计算平均分
    for (int i = 0; i < MAX_COURSES; i++) {
        course_averages[i] = course_totals[i] / student_count;
    }
    
    // 输出统计结果
    printf("学生总数: %d\n", student_count);
    printf("班级平均总分: %.1f\n", total_total / student_count);
    printf("\n各科目统计:\n");
    printf("科目\t\t平均分\t最高分\t最低分\t不及格人数\n");
    printf("----------------------------------------------------\n");
    
    for (int i = 0; i < MAX_COURSES; i++) {
        printf("%s\t\t%.1f\t%.1f\t%.1f\t%d\n", 
               course_names[i], course_averages[i], 
               course_highest[i], course_lowest[i], fail_counts[i]);
    }
    
    // 找出总分最高和最低的学生
    int highest_index = 0, lowest_index = 0;
    for (int i = 1; i < student_count; i++) {
        if (students[i].total > students[highest_index].total) {
            highest_index = i;
        }
        if (students[i].total < students[lowest_index].total) {
            lowest_index = i;
        }
    }
    
    printf("\n总分最高学生:\n");
    display_student(students[highest_index]);
    
    printf("\n总分最低学生:\n");
    display_student(students[lowest_index]);
}

// 保存到文件
void save_to_file() {
    FILE *file = fopen("students.dat", "wb");
    if (file == NULL) {
        printf("无法打开文件进行保存！\n");
        return;
    }
    
    fwrite(&student_count, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), student_count, file);
    
    fclose(file);
    printf("数据已保存到 students.dat 文件！\n");
}

// 从文件加载
void load_from_file() {
    FILE *file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf("没有找到数据文件，将创建新文件。\n");
        return;
    }
    
    fread(&student_count, sizeof(int), 1, file);
    fread(students, sizeof(Student), student_count, file);
    
    fclose(file);
    printf("从 students.dat 文件加载了 %d 条学生记录！\n", student_count);
}

// 工具函数实现
int find_student_by_id(int id) {
    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            return i;
        }
    }
    return -1;
}

void calculate_student_stats(Student *stu) {
    stu->total = 0;
    for (int i = 0; i < MAX_COURSES; i++) {
        stu->total += stu->scores[i];
    }
    stu->average = stu->total / MAX_COURSES;
}

void display_student(Student stu) {
    printf("学号: %d\n", stu.id);
    printf("姓名: %s\n", stu.name);
    printf("年龄: %d\n", stu.age);
    printf("各科成绩:\n");
    for (int i = 0; i < MAX_COURSES; i++) {
        printf("  %s: %.1f\n", course_names[i], stu.scores[i]);
    }
    printf("总分: %.1f\n", stu.total);
    printf("平均分: %.1f\n", stu.average);
}

// 排序算法实现
void bubble_sort(int by_total, int course_index) {
    for (int i = 0; i < student_count - 1; i++) {
        for (int j = 0; j < student_count - 1 - i; j++) {
            int swap = 0;
            
            if (by_total) {
                // 按总分排序（降序）
                if (students[j].total < students[j + 1].total) {
                    swap = 1;
                }
            } else {
                // 按单科成绩排序（降序）
                if (students[j].scores[course_index] < students[j + 1].scores[course_index]) {
                    swap = 1;
                }
            }
            
            if (swap) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

void quick_sort(int left, int right, int by_total, int course_index) {
    if (left < right) {
        int pivot = partition(left, right, by_total, course_index);
        quick_sort(left, pivot - 1, by_total, course_index);
        quick_sort(pivot + 1, right, by_total, course_index);
    }
}

int partition(int left, int right, int by_total, int course_index) {
    float pivot_value;
    
    if (by_total) {
        pivot_value = students[right].total;
    } else {
        pivot_value = students[right].scores[course_index];
    }
    
    int i = left - 1;
    
    for (int j = left; j < right; j++) {
        int condition;
        
        if (by_total) {
            condition = students[j].total >= pivot_value;  // 降序排序
        } else {
            condition = students[j].scores[course_index] >= pivot_value;
        }
        
        if (condition) {
            i++;
            Student temp = students[i];
            students[i] = students[j];
            students[j] = temp;
        }
    }
    
    Student temp = students[i + 1];
    students[i + 1] = students[right];
    students[right] = temp;
    
    return i + 1;
}