#include <stdio.h>
#include "tools.h"

int main() {
    // 定义一个变量n，用于存储一个正整数
    int n;
    // 打印出提示信息，让用户输入一个正整数
    printf("Enter a positive integer: ");
    // 使用scanf函数读取用户输入的正整数
    scanf("%d", &n);
    // 调用print_factors函数，打印出正整数的因子
    print_factors(n);
    return 0;
}