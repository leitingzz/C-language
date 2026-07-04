#include <stdio.h>
#include <stdlib.h>

int isLeapYear(int year){
    return (year % 4 == 0 && year % 100 != 0)||(year % 400 == 0);
}  

int getDaysInMonth(int year, int month){
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(isLeapYear(year)){
        return 29;
    }

    return days[month - 1];
}

int getTotalDays(int year, int month, int day){
    int totalDays = 0;

    for(int i = 1; i < year; i++){
        if(isLeapYear(i)){
            totalDays += 366;
        }else{
            totalDays += 365;
        }
    }

    for(int i = 1; i < month; i++){
        totalDays += getDaysInMonth(year, i);
    }

    totalDays += day;

    return totalDays;
}

int getWeekday(int year, int month, int day){
    return getTotalDays(year, month, day) % 7;
}

void printMonthCalendar(int year, int month){
    char* months[] = {"一月","二月","三月","四月","五月","六月","七月","八月","九月","十月","十一月","十二月"};

    printf("\n  %s %d\n", months[month - 1], year);
    printf("日  一  二  三  四  五  六\n");
    
    int getFirstWeekday = getWeekday(year, month, 1);

    for(int i = 0; i < getFirstWeekday; i++){
        printf("    ");
    }

    for(int i = 1; i <= getDaysInMonth(year, month); i++){
        printf("%-4d", i);

        if((i + getFirstWeekday) % 7 == 0){
            printf("\n");
        }
    }

    printf("\n");
}

void printYearCalendar(int year){
    for(int i = 1; i <= 12; i++){
        printMonthCalendar(year, i);
    }
}

void queryWeekday(int year, int month, int day){
    char* weekdays[] = {"星期日","星期一","星期二","星期三","星期四","星期五","星期六"};
    printf("%s",weekdays[getWeekday(year, month, day)]);
}

int main(){
    int year, month, day;
    
    printf("\n==========万年历系统==========\n");
    printf("1.查询指定日期的星期\n");
    printf("2.查询指定月份的日历\n");
    printf("3.查询指定年份的日历\n");
    printf("0.退出系统\n");
    while(1){
        
        printf("\n请输入所需功能对应的数字:");
    
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {

        case 0:

            printf("\n感谢使用，再见！");
            return 0;

        case 1:

            printf("\n请依次输入查询日期的年、月、日:");
            scanf("%d %d %d", &year, &month, &day);
            queryWeekday(year, month, day);
            
            break;
        
        case 2:

            printf("\n请依次输入查询月份的年、月:");
            scanf("%d %d", &year, &month);
            printMonthCalendar(year, month);

            break;

        case 3:

            printf("\n请输入查询年份:");
            scanf("%d", &year);
            printYearCalendar(year);

            break;


        default:

            printf("\n输入无效，请重试！");
            break;
        }
    }

    return 0;
}