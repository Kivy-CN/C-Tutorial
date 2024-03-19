#include <stdio.h>  // 引入标准输入输出库

int main() {  // 主函数
    int a = 10;  // 定义整型变量a并赋值为10
    unsigned int b = 20;  // 定义无符号整型变量b并赋值为20
    float c = 3.14;  // 定义浮点型变量c并赋值为3.14
    double d = 3.14159;  // 定义双精度浮点型变量d并赋值为3.14159
    char e = 'A';  // 定义字符型变量e并赋值为'A'
    char f[] = "Hello, World!";  // 定义字符数组f并赋值为"Hello, World!"
    int *g = &a;  // 定义整型指针g并指向变量a的地址

    // printf 示例
    printf("a (int): %d, size: %zu bytes\n", a, sizeof(a));  // 打印变量a的值和大小
    printf("b (unsigned int): %u, size: %zu bytes\n", b, sizeof(b));  // 打印变量b的值和大小
    printf("c (float): %f, size: %zu bytes\n", c, sizeof(c));  // 打印变量c的值和大小
    printf("d (double): %lf, size: %zu bytes\n", d, sizeof(d));  // 打印变量d的值和大小
    printf("e (char): %c, size: %zu bytes\n", e, sizeof(e));  // 打印变量e的值和大小
    printf("f (string): %s, size: %zu bytes\n", f, sizeof(f));  // 打印变量f的值和大小
    printf("g (pointer): %p, size: %zu bytes\n", (void *)g, sizeof(g));  // 打印变量g的值和大小

    // scanf 示例
    printf("Enter an integer: ");  // 提示用户输入一个整数
    scanf("%d", &a);  // 读取用户输入的整数并赋值给变量a
    printf("You entered: %d, size: %zu bytes\n", a, sizeof(a));  // 打印用户输入的整数和其大小

    printf("Enter a float: ");  // 提示用户输入一个浮点数
    scanf("%f", &c);  // 读取用户输入的浮点数并赋值给变量c
    printf("You entered: %f, size: %zu bytes\n", c, sizeof(c));  // 打印用户输入的浮点数和其大小

    return 0;  // 程序正常结束，返回0
}