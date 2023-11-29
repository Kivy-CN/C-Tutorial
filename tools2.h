#include <stdlib.h>

// 计算一个数的所有因子
int* get_factors(int n, int* num_factors) {
    // 分配一个数组，用于存储因子
    int* factors = (int*) malloc(n * sizeof(int));
    // 记录因子个数
    int count = 0;
    // 从1开始，到n结束，每次循环加1
    for (int i = 1; i <= n; ++i) {
        // 如果n能被i整除，则将i记录到factors中
        if (n % i == 0) {
            factors[count++] = i;
        }
    }
    // 将因子个数记录到num_factors中
    *num_factors = count;
    // 返回因子数组
    return factors;
}