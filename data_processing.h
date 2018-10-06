#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define DATA_NUM 1000  //获取的有效数据量

struct dataStruct{
    char age[20];
    char workclass[30];
    char fnlwght[30];
    char education[30];
    char eduction_num[30];
    char marital_status[30];
    char occupation[30];
    char relationship[30];
    char race[30];
    char sex[30];
    char capital_gain[30];
    char capital_loss[30];
    char hours_per_week[30];
    char native_country[30];
    char result[30];
};

int readData(char data[]){
    FILE *fr;
    struct dataStruct people[DATA_NUM];
    int i = 0;
    char strline[1024];
    if((fr=fopen(data, "r+")) == NULL){
        printf("Can't open the file.\n");
        return -1;
    }
    fgets(strline, 1024, fr);
    while(!feof(fr) && (i<DATA_NUM)){    //获取DATA_NUM个有效数据

        fgets(strline, 1024, fr);
        int flag = 1, j = 0;       //分割字符串及数据清洗
        char seg[] = ",";
        char charlist[20][20] = {""};
        char *substr = strtok(strline, seg);
        while(substr != NULL){
            strcpy(charlist[j], substr);
            if(flag == 1) {
                for(int k=0; k<strlen(charlist[j]); k++){  //数据清洗
                    if(charlist[j][k] == '?'){
                        flag = 0;
                        break;
                    }
                }
            }
            j++;
            substr = strtok(NULL, seg);
        }             //分割字符串结束
        memcpy(people[i].age, charlist[0], 20);
        memcpy(people[i].workclass, charlist[1], 30);
        memcpy(people[i].fnlwght, charlist[2], 30);
        memcpy(people[i].education, charlist[3], 30);
        memcpy(people[i].eduction_num, charlist[4], 30);
        memcpy(people[i].marital_status, charlist[5], 30);
        memcpy(people[i].occupation, charlist[6], 30);
        memcpy(people[i].relationship, charlist[7], 30);
        memcpy(people[i].race, charlist[8], 30);
        memcpy(people[i].sex, charlist[9], 30);
        memcpy(people[i].capital_gain, charlist[10], 30);
        memcpy(people[i].capital_loss, charlist[11], 30);
        memcpy(people[i].hours_per_week, charlist[12], 30);
        memcpy(people[i].native_country, charlist[13], 30);
        memcpy(people[i].result, charlist[14], 30);
        i++;
        if (!flag)
            i--;
    }
    for (int l = 0; l < i; ++l) {
        printf("%d: %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s",l,
               people[l].age,
               people[l].workclass,
               people[l].fnlwght,
               people[l].education,
               people[l].eduction_num,
               people[l].marital_status,
               people[l].occupation,
               people[l].relationship,
               people[l].race,
               people[l].sex,
               people[l].capital_gain,
               people[l].capital_loss,
               people[l].hours_per_week,
               people[l].native_country,
               people[l].result);
    }
}

