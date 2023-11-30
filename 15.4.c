// 解决中文乱码
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int main() {
    // 设置本地化，使用中文编码
    setlocale(LC_ALL, "zh_CN.UTF-8");

    char input[1000];
    printf("请输入中文字符串：");
    fgets(input, 1000, stdin);
    // 去掉换行符
    input[strcspn(input, "\n")] = 0;
    printf("直接打印输出中文：\n");
    printf("%s\n", input);
    printf("转码打印输出中文：\n");
    // 使用GBK编码打印输出
    #ifdef _WIN32 // 这里判断若是 Windows 系统，就切换编码到GBK，然后再输出刚刚的中文字符串
        system("chcp 936 > nul");
    #endif
    printf("%s\n", input);
    return 0;
}