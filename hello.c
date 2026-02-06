#include <stdio.h>      // 标准输入输出（printf, scanf）
#include <stdlib.h>     // 标准库（malloc, free, EXIT_SUCCESS）
#include <string.h>     // 字符串操作（strcpy, strlen）
#include <math.h>       // 数学函数（sqrt, pow）
#include <stdbool.h>    // 布尔类型（bool, true, false）

// 函数声明（可选，因定义在 main 之后）
double compute_hypotenuse(double a, double b);

int main(void) {
    // === 基本数据类型 ===
    int          age = 25;                     // 整型
    short        count = 100;                  // 短整型
    long         big_num = 123456789L;         // 长整型
    long long    huge_num = 9876543210LL;      // 更长整型

    float        price = 19.99f;               // 单精度浮点
    double       pi = 3.1415926535;            // 双精度浮点

    char         grade = 'A';                  // 字符（ASCII）
    unsigned char byte_val = 255;              // 无符号字符

    bool         is_valid = true;              // 布尔值（C99起）

    // === 构造类型：数组、结构体、枚举 ===
    int scores[3] = {90, 85, 95};              // 数组

    struct Student {                           // 结构体
        char name[20];
        int age;
        double gpa;
    } stu = {"Alice", 20, 3.8};

    enum Color { RED, GREEN, BLUE };           // 枚举
    enum Color bg = GREEN;

    // === 指针与动态内存 ===
    int *p = &age;                             // 指针（指向 age）
    int *arr = malloc(5 * sizeof(int));        // 动态分配数组
    if (arr == NULL) return EXIT_FAILURE;
    for (int i = 0; i < 5; i++) arr[i] = i * 2;

    // === 使用标准库函数 ===
    printf("Hello, %s! Age: %d\n", stu.name, stu.age);
    printf("Pi is about %.6f, sqrt(2) is about %.4f\n", pi, sqrt(2.0));
    printf("Hypotenuse of (3,4): %.2f\n", compute_hypotenuse(3.0, 4.0));

    // === 控制结构 ===
    if (is_valid) {
        printf("Status: Valid\n");
    }

    for (int i = 0; i < 3; i++) {
        printf("Score[%d] = %d\n", i, scores[i]);
    }

    // === 释放动态内存 ===
    free(arr);

    return EXIT_SUCCESS;  // 程序正常退出
}

// === 自定义函数 ===
double compute_hypotenuse(double a, double b) {
    return sqrt(a * a + b * b);  // 调用 math.h 中的 sqrt
}