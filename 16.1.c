// 斐波那契数列 int
#include <stdio.h>
#include <time.h>

int main() {
    // 定义变量n，表示要输出多少个斐波那契数列
    long long  n = 100, i, t1 = 0, t2 = 1, nextTerm;
    // 输出提示信息
    printf("Fibonacci Series: ");

    // 记录开始时间
    clock_t start = clock();
    // 循环输出斐波那契数列
    for (i = 1; i <= n; ++i) {
        // 输出斐波那契数列的值
        printf("%lld, ", t1);
        // 计算下一个斐波那契数列的值
        nextTerm = t1 + t2;
        // 更新t1和t2的值
        t1 = t2;
        t2 = nextTerm;
    }
    // 记录结束时间
    clock_t end = clock();

    // 计算程序运行的时间
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    // 输出程序运行的时间
    printf("\nTime taken: %f seconds\n", time_spent);

    return 0;
}