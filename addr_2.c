// 代码2  指针的基本概念
#include <stdio.h>
int main() {
    // 声明一个整型变量
    int value = 10;   
    // 声明一个整型指针变量
    int *ptr;   
    // 将value的地址赋给指针变量
    ptr = &value;   
    printf("value的值: %d\n", value);
    printf("value的地址: %p\n", &value);
    printf("ptr存储的地址: %p\n", ptr);   
    return 0;
}