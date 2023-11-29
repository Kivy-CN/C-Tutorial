#include <stdio.h> 
int main()
{
    // 定义变量a，类型为int，赋值为10
    int a = 10;
    // 定义变量b，类型为float，赋值为3.14
    float b = 3.14;
    // 定义变量c，类型为double，将a和b相加
    double c = a + b; // 隐式将int类型转换为double类型

    // 定义变量d，类型为double，赋值为3.14159
    double d = 3.14159;
    // 将d转换为int类型，赋值给e
    int e = (int)d; // 显式将double类型转换为int类型
    // 打印变量c和e的值
    printf("c = %f \ne = %d\n", c, e);
    return 0;
}