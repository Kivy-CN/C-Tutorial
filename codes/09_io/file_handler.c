/*
 * file: file_handler.c
 * --------------------
 * 这个程序演示了 C 语言的文件输入输出操作。
 * 
 * 知识点：
 * 1. 文件的打开与关闭 (fopen, fclose)
 * 2. 文本文件的读写 (fprintf, fgets)
 * 3. 二进制文件的读写 (fwrite, fread)
 *
 * 编译命令:
 *   clang file_handler.c -o file_handler
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Config {
    int id;
    float value;
    char name[20];
};

void text_file_demo() {
    printf("=== 文本文件读写 ===\n");
    const char *filename = "test_data.txt";

    // 1. 写入文本文件
    FILE *fp = fopen(filename, "w"); // "w": 写入模式 (会清空已有内容)
    if (fp == NULL) {
        perror("打开文件失败");
        return;
    }
    
    fprintf(fp, "Hello, File IO!\n");
    fprintf(fp, "Line 2: Number %d\n", 42);
    fclose(fp);
    printf("写入完成: %s\n", filename);

    // 2. 读取文本文件
    fp = fopen(filename, "r"); // "r": 读取模式
    if (fp == NULL) {
        perror("读取文件失败");
        return;
    }

    char buffer[100];
    printf("文件内容:\n");
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("  %s", buffer); // buffer 中已包含换行符
    }
    fclose(fp);
}

void binary_file_demo() {
    printf("\n=== 二进制文件读写 ===\n");
    const char *filename = "config.bin";
    struct Config cfg_out = {101, 3.14159f, "Sensor_A"};

    // 1. 写入二进制文件
    FILE *fp = fopen(filename, "wb"); // "wb": 二进制写入
    if (fp) {
        // 写入整个结构体
        fwrite(&cfg_out, sizeof(struct Config), 1, fp);
        fclose(fp);
        printf("二进制数据已写入: %s\n", filename);
    }

    // 2. 读取二进制文件
    struct Config cfg_in;
    fp = fopen(filename, "rb"); // "rb": 二进制读取
    if (fp) {
        fread(&cfg_in, sizeof(struct Config), 1, fp);
        fclose(fp);
        
        printf("读取结果:\n");
        printf("  ID: %d\n", cfg_in.id);
        printf("  Value: %f\n", cfg_in.value);
        printf("  Name: %s\n", cfg_in.name);
    }
}

int main() {
    text_file_demo();
    binary_file_demo();
    return 0;
}
