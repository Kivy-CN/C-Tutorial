// 代码1  基本变量的内存地址演示
#include <stdio.h>
int main() {
    // 创建一个整型变量
    int number = 42;   
    // &运算符可以获取变量的内存地址
    printf("变量number的值: %d\n", number);
    printf("变量number的内存地址: %p\n", &number);   
    return 0;
}