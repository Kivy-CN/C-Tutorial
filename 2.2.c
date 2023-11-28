#include <stdio.h>
#include <time.h>

int main() {
    // 定义变量n，表示要输出多少个斐波那契数列
    int n = 100, i, t1 = 0, t2 = 1, nextTerm;
    // 输出字符串
    printf("Fibonacci Series: ");

    // 记录开始时间
    clock_t start = clock();
    // 循环输出斐波那契数列
    for (i = 1; i <= n; ++i) {
        // 输出斐波那契数列的第i个数
        printf("%d, ", t1);
        // 计算下一个斐波那契数列的值
        nextTerm = t1 + t2;
        // 将t1的值赋给t2
        t1 = t2;
        // 将nextTerm的值赋给t2
        t2 = nextTerm;
    }
    // 记录结束时间
    clock_t end = clock();

    // 计算程序运行时间
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    // 输出程序运行时间
    printf("\nTime taken: %f seconds\n", time_spent);

    return 0;

    /*多行的代码
    要如何注释掉呢*/
}