#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DATA_NUM 1370  // 收集数据的数量
#define FEATURE_NUM 4  // 每一组数据的特征的数量
#define START_NUM 1000  // 从START_NUM处开始分类
#define END_NUM 1370  // 从END_NUM处结束分类


int getData(char data_road[]);  // 收集数据
int dataPrediction(const double * theta, const double * x);  // 数据预测

float correctRate(double *theta, int start_num, int end_num);  // 统计预测正确率

double *dataTraining();  // 数据训练
double sigmodFunction(double x);  // sigmod函数实现结果介于(0, 1)

double dataList[DATA_NUM][FEATURE_NUM+1];  // 定义全局变量数据集矩阵


int getData(char data_road[]){  // 收集数据
    FILE *fr;
    char strLine[1024];
    int i = 0;
    if((fr=fopen(data_road, "r+")) == NULL){
        printf("Can't open the file.\n");
        return -1;
    }
    while(!feof(fr) && (i<DATA_NUM)){    //获取DATA_NUM个有效数据
        fgets(strLine, 1024, fr);
        char seg[] = " ";
        int  j = 0;
        char *subStr = strtok(strLine, seg);
        while(subStr != NULL){
            dataList[i][j] = atoi(subStr);
            j++;
            subStr = strtok(NULL, seg);
        }
        i++;
    }
    fclose(fr);
    return 0;
}

double sigmodFunction(double x){  // sigmod函数实现结果介于(0, 1)
    double ex;
    ex = pow(2.178281828, x);
    return ex/(1+ex);
}

int dataPrediction(const double * theta, const double * x){  // 数据预测，即分为0，1两类
    double result=0;
    for (int i = 0; i < FEATURE_NUM; ++i) {
        result += theta[i]*x[i];
    }
    if ((sigmodFunction(result) >= 0.5) && (x[FEATURE_NUM] == 1)){
        return 1;
    }
    else if ((sigmodFunction(result) <= 0.5) && (x[FEATURE_NUM] == 0)){
        return 1;
    }
    else {
        return 0;
    }
}

float correctRate(double *theta, int start_num, int end_num){  // 统计预测的正确率
    int realNumber = 0;
    for (int l = start_num; l < end_num; ++l) {
        int rightNum = dataPrediction(theta, dataList[l]);
        if (rightNum){
            realNumber += 1;
        }
    }
    printf("%f %%\n", 100.0*realNumber/(end_num-start_num));
}

double *dataTraining(){  // 数据训练
    int iter = 1;

    double h=0;
    double loss;
    double error = 0;
    static double theta[FEATURE_NUM];
    double learning_rate=0.005;

    for (int i = 0; i < FEATURE_NUM; ++i) {  // 对theta赋初始值
        theta[i] = 1;
    }
    while (iter < 1000){
        for (int j = 0; j < DATA_NUM-370; ++j){
            h = 0;
            for (int k = 0; k < FEATURE_NUM; ++k) {
                h = h + theta[k]*dataList[j][k];
            }
            error = sigmodFunction(h) - dataList[j][FEATURE_NUM];
            for (int l = 0; l < FEATURE_NUM; ++l) {
                loss = (-1)*error*dataList[j][l];
                theta[l] = theta[l] + learning_rate*loss;
            }
        }
        iter = iter + 1;
    }
    for (int m = 0; m < FEATURE_NUM; ++m) {
        printf("theta[%d] = %lf\n", m, theta[m]);
    }
    return theta;
}

int main()
{
    getData("..//data2.txt");  // 收集数据并将其转换为矩阵
    double *theta = dataTraining();  // 数据训练
    correctRate(theta, START_NUM, END_NUM);  // 数据分类正确率统计
    return 0;
}
