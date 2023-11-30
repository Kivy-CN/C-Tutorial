// 给出一个整数，打印输出因子
#include <stdio.h>

void print_factors(int num) {
    // 定义一个变量i
    int i;
    // 遍历从1到num的每一个数
    for(i = 1; i <= num; ++i) {
        // 如果num能被i整除，则输出i
        if (num % i == 0) {
            printf("%d ", i);
        }
    }
}