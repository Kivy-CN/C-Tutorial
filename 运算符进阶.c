#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

// 减少迭代次数，避免程序运行太久
#define ITERATIONS 100000000
// 为分支预测测试使用更小的数组
#define ARRAY_SIZE 1000000

#define TEST(name, code) \
    start = clock(); \
    for (i = 0; i < ITERATIONS; i++) { code; } \
    end = clock(); \
    printf("%-30s %7.3f ms\n", name, (double)(end - start) * 1000 / CLOCKS_PER_SEC); \
    fflush(stdout);

int main() {
    clock_t start, end;
    int64_t i, a = 0, b = 3, c = 7;
    volatile int64_t result = 0; // 使用volatile防止编译器优化掉循环
    
    // 初始化随机数生成器
    srand((unsigned)time(NULL));
    
    printf("运行每个测试 %ld 次\n\n", ITERATIONS);
    fflush(stdout);
    
    printf("=== 基本算术运算符 ===\n");
    TEST("加法 a + b", result = b + c)
    TEST("减法 a - b", result = c - b)
    TEST("乘法 a * b", result = b * c)
    TEST("除法 a / b", result = c / b)
    TEST("取模 a % b", result = c % b)
    
    printf("\n=== 位运算对比 ===\n");
    TEST("位左移 a << 2", result = b << 2)
    TEST("乘法 a * 4", result = b * 4)
    TEST("位右移 a >> 1", result = c >> 1)
    TEST("除法 a / 2", result = c / 2)
    TEST("位与 a & b", result = b & c)
    TEST("位或 a | b", result = b | c)
    TEST("位异或 a ^ b", result = b ^ c)
    
    printf("\n=== 高级优化场景 ===\n");
    // 乘法优化为移位
    TEST("乘以8 (a * 8)", result = c * 8)
    TEST("移位替代 (a << 3)", result = c << 3)
    
    // 取模优化 (仅对2的幂有效)
    TEST("取模16 (a % 16)", result = i % 16)
    TEST("位与替代 (a & 15)", result = i & 15)
    
    // 分支预测对比 - 使用堆分配而非栈分配
    printf("\n准备分支预测测试数据...\n");
    fflush(stdout);
    
    // 使用动态内存分配，避免栈溢出
    int64_t *data = (int64_t*)malloc(ARRAY_SIZE * sizeof(int64_t));
    if (data == NULL) {
        printf("内存分配失败！\n");
        return 1;
    }
    
    for (i = 0; i < ARRAY_SIZE; i++) {
        data[i] = rand() % 256;
    }
    
    printf("\n=== 分支预测影响 ===\n");
    result = 0;
    TEST("有序数据的if分支", {
        if (i < ITERATIONS/2) result += i;
        else result -= i;
    })
    
    result = 0;
    TEST("随机分支 (难以预测)", {
        if (data[i % ARRAY_SIZE] > 128) result += i;
        else result -= i;
    })
    
    printf("\n=== 自增自减操作 ===\n");
    TEST("前缀自增 ++a", { ++a; --a; })
    TEST("后缀自增 a++", { a++; a--; })
    
    // 清理内存
    free(data);
    
    printf("\n结果值(防止优化): %ld\n", result);
    printf("测试完成!\n");
    
    return 0;
}