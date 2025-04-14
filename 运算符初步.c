/*
 * C语言基本运算符性能对比程序
 * 
 * 本程序测试并比较以下C语言运算符的执行效率:
 * - 基本算术运算符 (+, -, *, /)
 * - 自增自减运算符 (++, --)
 *
 * 通过多次重复执行运算并计时，展示不同运算符的性能差异
 */

#include <stdio.h>    // 包含标准输入输出函数，用于printf等
#include <stdlib.h>   // 包含内存分配、随机数等函数
#include <time.h>     // 包含时间相关函数，用于测量性能

// 设置循环次数，数值较大以便能测出性能差异
#define LOOP_COUNT 1000000000

int main() {
    // 声明变量，用于记录开始和结束时间
    clock_t start_time, end_time;
    double execution_time;
    
    // 声明整型变量，用于运算测试
    int i;              // 循环计数器
    int a = 0;          // 用于自增自减运算
    int b = 3, c = 7;   // 用于基本运算
    
    // volatile关键字告诉编译器不要优化这个变量
    // 这确保编译器不会删除我们的测试循环
    volatile int result = 0;
    
    // 用当前时间初始化随机数生成器
    srand((unsigned)time(NULL));
    
    printf("每个测试运行 %d 次\n\n", LOOP_COUNT);
    
    // 加法测试
    start_time = clock();
    for (i = 0; i < LOOP_COUNT; i++) {
        result = b + c;    // 3 + 7 = 10
    }
    end_time = clock();
    execution_time = (double)(end_time - start_time) * 1000 / CLOCKS_PER_SEC;
    printf("加法:\t\t%.3f 毫秒\n", execution_time);        
    // 打印最终结果，防止编译器优化掉整个计算过程
    printf("\nresult= %d, a = %d\n", result, a);
    return 0;
}