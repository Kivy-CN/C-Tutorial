// 给出一个整数，打印输出因子，返回因子个数
#include <stdio.h>

int print_factors(int num) {
    // 定义一个变量i和一个计数器count
    int i, count = 0;
    // 遍历从1到num的每一个数
    for(i = 1; i <= num; ++i) {
        // 如果num能被i整除，则输出i并增加计数器的值
        if (num % i == 0) {
            printf("%d ", i);
            count++;
        }
    }
    // 返回计数器的值
    return count;
}