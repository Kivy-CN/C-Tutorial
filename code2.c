#include <stdio.h>  // 预处理命令，包含一下 stdio.h 文件，用<>就表明从系统库中寻找头文件
#include <stdlib.h> // 预处理命令，包含一下 stdlib.h 文件，用<>就表明从系统库中寻找头文件
#include "tools2.h" // 预处理命令，包含一下 tools2.h 文件，用""就表明从当前目录寻找头文件

int main() {
    // 定义一个整型变量n
    int n;
    // 打印提示信息，让用户输入一个正整数
    printf("Enter a positive integer: ");
    // 读取用户输入的正整数
    scanf("%d", &n);
    // 定义一个整型变量num_factors，用于存储因子个数
    int num_factors;
    // 调用函数get_factors，获取因子，并存储在变量factors中
    int* factors = get_factors(n, &num_factors);
    // 打印提示信息，让用户知道因子
    printf("The factors of %d are: ", n);
    // 遍历变量factors，打印每一个因子
    for (int i = 0; i < num_factors; ++i) {
        printf("%d ", factors[i]);
    }
    printf("\n");
    // 调用函数free，释放变量factors占用的内存空间
    free(factors);
    return 0;
}