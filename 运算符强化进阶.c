#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <math.h>  // 添加数学库

// 减少迭代次数，避免程序运行太久
#define ITERATIONS 100000000
// 数学函数测试使用更少的迭代次数
#define MATH_ITERATIONS 10000000
// 为分支预测测试使用更小的数组
#define ARRAY_SIZE 1000000

#define TEST(name, code) \
    start = clock(); \
    for (i = 0; i < ITERATIONS; i++) { code; } \
    end = clock(); \
    printf("%-30s %7.3f ms\n", name, (double)(end - start) * 1000 / CLOCKS_PER_SEC); \
    fflush(stdout);

#define MATH_TEST(name, code) \
    start = clock(); \
    for (i = 0; i < MATH_ITERATIONS; i++) { code; } \
    end = clock(); \
    printf("%-30s %7.3f ms\n", name, (double)(end - start) * 1000 / CLOCKS_PER_SEC); \
    fflush(stdout);

// 快速平方根近似计算 (牛顿法一次迭代)
float fast_sqrt(float x) {
    float half_x = 0.5f * x;
    int i = *(int*)&x;
    i = 0x5f375a86 - (i >> 1);  // 初始近似值（位操作技巧）
    x = *(float*)&i;
    x = x * (1.5f - half_x * x * x);  // 牛顿迭代一次
    return x * half_x * 2.0f;
}

// 快速Sin近似 (泰勒级数: sin(x) ≈ x - x³/6 + x⁵/120)
float fast_sin(float x) {
    // 将x归一化到[-π,π]区间
    while (x > M_PI) x -= 2 * M_PI;
    while (x < -M_PI) x += 2 * M_PI;
    
    float x2 = x * x;
    float x3 = x2 * x;
    float x5 = x3 * x2;
    
    return x - x3/6.0f + x5/120.0f;
}

int main() {
    clock_t start, end;
    int64_t i, a = 0, b = 3, c = 7;
    volatile int64_t result = 0; // 使用volatile防止编译器优化掉循环
    volatile float fresult = 0.0f;  // 浮点结果
    
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
    
    // 添加复杂数学函数性能测试
    printf("\n=== 复杂数学函数比较 ===\n");
    printf("运行每个数学测试 %ld 次\n", MATH_ITERATIONS);
    fflush(stdout);
    
    // 准备测试值
    float test_val = 1.234f;
    float angles[4] = {0.5f, 1.0f, 1.5f, 2.0f};
    int angle_idx = 0;
    
    // 平方根函数对比
    MATH_TEST("标准平方根 sqrt()", fresult = sqrt(test_val))
    MATH_TEST("快速平方根近似", fresult = fast_sqrt(test_val))
    
    // 三角函数对比
    MATH_TEST("标准正弦函数 sin()", {
        angle_idx = i % 4;
        fresult = sin(angles[angle_idx]);
    })
    
    MATH_TEST("快速正弦近似", {
        angle_idx = i % 4;
        fresult = fast_sin(angles[angle_idx]);
    })
    
    // 其他数学函数
    MATH_TEST("对数函数 log()", fresult = log(test_val + 1.0f))
    MATH_TEST("指数函数 exp()", fresult = exp(test_val - 3.0f))
    MATH_TEST("幂函数 pow()", fresult = pow(test_val, 2.5f))
    
    // 组合数学运算
    MATH_TEST("复合数学运算", {
        angle_idx = i % 4;
        fresult = sin(angles[angle_idx]) * cos(angles[angle_idx]) + 
                 sqrt(test_val) / log(test_val + 2.0f);
    })
    
    // 精度比较
    printf("\n=== 精度比较 ===\n");
    printf("sqrt(%.3f) = %.8f\n", test_val, sqrt(test_val));
    printf("fast_sqrt(%.3f) = %.8f\n", test_val, fast_sqrt(test_val));
    printf("sin(1.0) = %.8f\n", sin(1.0f));
    printf("fast_sin(1.0) = %.8f\n", fast_sin(1.0f));
    
    // 清理内存
    free(data);
    
    printf("\n结果值(防止优化): %ld, %.6f\n", result, fresult);
    printf("测试完成!\n");
    
    return 0;
}