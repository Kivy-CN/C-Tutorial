#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    // 定义文件指针
    FILE *fp;
    // 定义文件名
    char filename[] = "time.txt";
    // 定义缓冲区
    char buffer[80];
    // 定义时间戳
    time_t rawtime;
    // 定义时间信息
    struct tm *timeinfo;

    // 获取当前时间戳
    time(&rawtime);
    // 获取本地时间信息
    timeinfo = localtime(&rawtime);

    // 打开文件
    fp = fopen(filename, "w");
    // 判断文件是否创建成功
    if (fp == NULL) {
        printf("Failed to create file.\n");
        exit(1);
    }

    // 将时间信息转换为字符串
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
    // 将时间信息写入文件
    fprintf(fp, "Date and Time: %s\n", buffer);

    // 关闭文件
    fclose(fp);
    // 提示文件创建成功
    printf("File created successfully.\n");
    return 0;
}