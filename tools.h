#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>

// 打印一个数字的所有因子
void print_factors(int n) {
    // 打印提示信息
    printf("The factors of %d are: ", n);
    // 遍历所有因子
    for (int i = 1; i <= n; ++i) {
        // 如果因子存在，则打印出来
        if (n % i == 0) {
            printf("%d ", i);
        }
    }
    // 打印换行符
    printf("\n");
}

#endif
