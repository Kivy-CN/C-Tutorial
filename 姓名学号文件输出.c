#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 函数声明
int print_factors(int number, char name[], int factors[]);
char* save_to_file(char name[], int number, int factors[], int count);

int main() {
    int id;
    char name[50];
    int factors[1000] = {0}; // 假设最多1000个因子
    int count;
    char* filepath;

    printf("请输入学号：");
    scanf("%d", &id);

    printf("请输入姓名：");
    scanf("%s", name);

    // 打印因子并获取因子数量
    count = print_factors(id, name, factors);
    
    // 保存到文件并获取文件路径
    filepath = save_to_file(name, id, factors, count);
    
    printf("结果已保存到文件：%s\n", filepath);
    
    // 释放动态分配的内存
    free(filepath);

    return 0;
}

// 输出学号的所有因子，并返回因子数量
int print_factors(int number, char name[], int factors[]) {
    int count = 0;
    
    printf("%s的幸运数字（学号 %d 的因子）有：", name, number);
    
    for (int i = 1; i <= number; i++) {
        if (number % i == 0) {
            printf("%d ", i);
            factors[count++] = i;
        }
    }
    
    printf("\n");
    
    return count;
}

// 将因子信息保存到文件，返回文件路径
char* save_to_file(char name[], int number, int factors[], int count) {
    FILE *file;
    char* filepath = (char*)malloc(100 * sizeof(char));
    
    // 创建文件名：姓名.txt
    sprintf(filepath, "%s.txt", name);
    
    // 打开文件用于写入
    file = fopen(filepath, "w");
    if (file == NULL) {
        printf("无法创建文件 %s\n", filepath);
        return filepath;
    }
    
    // 写入文件
    fprintf(file, "%s的幸运数字（学号 %d 的因子）有：", name, number);
    
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d ", factors[i]);
    }
    
    fprintf(file, "\n");
    
    // 关闭文件
    fclose(file);
    
    return filepath;
}