// 给出一个整数，返回因子列表
#include <stdlib.h>

int* get_factors(int num, int* count) {
    // 定义一个变量i和一个计数器
    int i;
    *count = 0;
    // 计算因子的数量
    for(i = 1; i <= num; ++i) {
        if (num % i == 0) {
            (*count)++;
        }
    }
    // 分配存储因子的数组
    int* factors = (int*) malloc(*count * sizeof(int));
    // 将因子存储到数组中
    int j = 0;
    for(i = 1; i <= num; ++i) {
        if (num % i == 0) {
            factors[j++] = i;
        }
    }
    // 返回指向因子列表的指针
    return factors;
}

void free_factors(int* factors) {
    // 释放存储因子的数组
    free(factors);
}
