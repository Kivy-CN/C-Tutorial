#include <stdio.h> 
int main()
{
    // 定义变量a，类型为int，赋值为10
    int a;
    a = 10;
    float b = (float)a; // 显式将double类型转换为int类型
    // 打印变量a和b的值
    printf("a = %d \nb = %f\n", a, b);
    return 0;
}