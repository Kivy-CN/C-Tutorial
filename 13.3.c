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
    // 减去一天的秒数
    rawtime -= 24 * 60 * 60;
    // 获取昨天的时间信息
    timeinfo = localtime(&rawtime);

    // 打开文件
    fp = fopen(filename, "a");
    // 判断文件是否打开成功
    if (fp == NULL) {
        printf("Failed to open file.\n");
        exit(1);
    }

    // 将时间信息转换为字符串
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
    // 将时间信息写入文件
    fprintf(fp, "Yesterday's Date and Time: %s\n", buffer);

    // 关闭文件
    fclose(fp);
    // 提示文件写入成功
    printf("File written successfully.\n");
    return 0;
}
