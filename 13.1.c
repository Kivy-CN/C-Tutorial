// 文件读取
#include <stdio.h>
#include <stdlib.h>

int main() {
    // 定义文件指针
    FILE *fp;
    // 定义文件名
    char filename[] = "time.txt";
    // 定义缓冲区
    char buffer[80];

    // 打开文件
    fp = fopen(filename, "r");
    // 判断文件是否打开成功
    if (fp == NULL) {
        printf("Failed to open file.\n");
        exit(1);
    }

    // 读取文件内容并输出
    while (fgets(buffer, 80, fp) != NULL) {
        printf("%s", buffer);
    }

    // 关闭文件
    fclose(fp);
    return 0;
}