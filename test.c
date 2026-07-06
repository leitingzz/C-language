#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILENAME "D:\\c++\\flight.c\\flights.txt"
#define MAX_FLIGHTS 100

typedef struct {
    char flightNo[10];
    char start[20];
    char end[20];
    char days[20];
    char departTime[10];
    char arriveTime[10];
    char model[10];
    int price;
}Flight;

//从文件中加载数据
Flight flights[MAX_FLIGHTS];
int count = 0;

void loadFromFile(){
    FILE*fp = fopen(FILENAME,"r");      //fopen(文件名，打开方式)
    if(fp == NULL){
        printf("文件不存在，将创建新文件\n");
        return;
    }

    char line[256];
    fgets(line, sizeof(line), fp);        //fgets(存放数据的字符数组，最大读取长度，数据来源)
    count = 0;
    while(fscanf(fp,"%s%s%s%s%s%s%s%d",      //fscanf的返回值是成功匹配并赋值的参数个数
        flights[count].flightNo,
        flights[count].start,
        flights[count].end,
        flights[count].days,
        flights[count].departTime,
        flights[count].arriveTime,
        flights[count].model,
        &flights[count].price) == 8){
        count++;
        if(count >= MAX_FLIGHTS) break;
    }

    fclose(fp);
    printf("成功加载%d条航班\n",count);
}

//保存数据到文件
void saveToFile(){
    FILE*fp = fopen(FILENAME,"w");
    if(fp == NULL){
        printf("无法打文开件写入!\n");
        return;
    }

    fprintf(fp,"%-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n","航班号","起点","终点","航班期","起飞时间","到达时间","机型","机票");
    for(int i = 0; i < count; i++){
        fprintf(fp, "%s %s %s %s %s %s %s %d\n",
        flights[i].flightNo,
        flights[i].start,
        flights[i].end,
        flights[i].days,
        flights[i].departTime,
        flights[i].arriveTime,
        flights[i].model,
        flights[i].price);
    }
    fclose(fp);
    printf("数据已保存到文件。\n");
}

//显示所有航班
void displayAll(){
    if(count == 0){
        printf("当前无航班记录。\n");
        return;
    }

    printf("%-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n","航班号","起点","终点","航班期","起飞时间","到达时间","机型","机票");

    for(int i = 0; i < count; i++){
        printf("%-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10d\n",
        flights[i].flightNo,
        flights[i].start,
        flights[i].end,
        flights[i].days,
        flights[i].departTime,
        flights[i].arriveTime,
        flights[i].model,
        flights[i].price);
    }
}

void addFlight(){
    if(count >= MAX_FLIGHTS){
        printf("航班数量已达上限，无法添加！\n");
        return;
    }

    Flight f;
    printf("请输入航班号：");
    scanf("%s",f.flightNo);
    printf("请输入起点站：");
    scanf("%s",f.start);
    printf("请输入终点站：");
    scanf("%s",f.end);
    printf("请输入航班期：");
    scanf("%s",f.days);
    printf("请输入起飞时间：");
    scanf("%s",f.departTime);
    printf("请输入到达时间：");
    scanf("%s",f.arriveTime);
    printf("请输入机型：");
    scanf("%s",f.model);
    printf("请输入票价：");
    scanf("%s",f.price);

    flights[count++] = f;
    printf("添加成功!\n");
}

int main(){
    loadFromFile();
    displayAll();
    return 0;
}