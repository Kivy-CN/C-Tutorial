#include <stdio.h>  // 引入标准输入输出库
#include <time.h>   // 引入时间库

// 计时函数
double calculate_time(clock_t start, clock_t end) {
    double diff = ((double)end - start) / CLOCKS_PER_SEC;  // 计算时间差，并转换为秒
    return diff;  // 返回时间差
}

// `CLOCKS_PER_SEC`是C语言中的一个宏定义，它在`<time.h>`头文件中定义。这个宏表示的是每秒钟的时钟数，用于将`clock()`函数返回的时钟数转换为秒数。

// 加法操作
void add_operation(int n) {
    int result = 0;  // 初始化结果为0
    for(int i = 0; i < n; i++) {  // 循环n次
        result += i;  // 每次将i加到结果上
    }
}

// 减法操作
void subtract_operation(int n) {
    int result = 0;  // 初始化结果为0
    for(int i = 0; i < n; i++) {  // 循环n次
        result -= i;  // 每次从结果中减去i
    }
}

// 乘法操作
void multiply_operation(int n) {
    int result = 1;  // 初始化结果为1
    for(int i = 1; i <= n; i++) {  // 循环n次
        result *= i;  // 每次将结果乘以i
    }
}

// 除法操作
void divide_operation(int n) {
    double result = 1.0;  // 初始化结果为1.0
    for(int i = 1; i <= n; i++) {  // 循环n次
        result /= i;  // 每次将结果除以i
    }
}

// 自增操作
void increment_operation(int n) {
    int result = 0;  // 初始化结果为0
    for(int i = 0; i < n; i++) {  // 循环n次
        result++;  // 每次将结果自增1
    }
}

// 自减操作
void decrement_operation(int n) {
    int result = 0;  // 初始化结果为0
    for(int i = 0; i < n; i++) {  // 循环n次
        result--;  // 每次将结果自减1
    }
}

// 求余操作
void modulus_operation(int n) {
    int result = n;  // 初始化结果为n
    for(int i = 1; i < n; i++) {  // 循环n次
        result = result % i;  // 每次将结果对i取余
    }
}

// 取地址操作
void address_operation(int n) {
    int* result = &n;  // 初始化结果为n的地址
    for(int i = 0; i < n; i++) {  // 循环n次
        result = &i;  // 每次将结果设置为i的地址
    }
}

int main() {
    int n = 100000000; // 设置运算次数为100000000

    printf("运算次数: %d\n", n);  // 打印运算次数

    clock_t start, end;  // 定义开始和结束时间

    start = clock();  // 获取开始时间
    add_operation(n);  // 执行加法操作
    end = clock();  // 获取结束时间
    printf("加法运算时间: %f\n", calculate_time(start, end));  // 打印加法运算时间

    start = clock();  // 获取开始时间
    subtract_operation(n);  // 执行减法操作
    end = clock();  // 获取结束时间
    printf("减法运算时间: %f\n", calculate_time(start, end));  // 打印减法运算时间

    start = clock();  // 获取开始时间
    multiply_operation(n);  // 执行乘法操作
    end = clock();  // 获取结束时间
    printf("乘法运算时间: %f\n", calculate_time(start, end));  // 打印乘法运算时间

    start = clock();  // 获取开始时间
    divide_operation(n);  // 执行除法操作
    end = clock();  // 获取结束时间
    printf("除法运算时间: %f\n", calculate_time(start, end));  // 打印除法运算时间

    start = clock();  // 获取开始时间
    increment_operation(n);  // 执行自增操作
    end = clock();  // 获取结束时间
    printf("自增运算时间: %f\n", calculate_time(start, end));  // 打印自增运算时间

    start = clock();  // 获取开始时间
    decrement_operation(n);  // 执行自减操作
    end = clock();  // 获取结束时间
    printf("自减运算时间: %f\n", calculate_time(start, end));  // 打印自减运算时间

    start = clock();  // 获取开始时间
    modulus_operation(n);  // 执行求余操作
    end = clock();  // 获取结束时间
    printf("求余运算时间: %f\n", calculate_time(start, end));  // 打印求余运算时间

    start = clock();  // 获取开始时间
    address_operation(n);  // 执行取地址操作
    end = clock();  // 获取结束时间
    printf("取地址运算时间: %f\n", calculate_time(start, end));  // 打印取地址运算时间

    return 0;  // 程序结束，返回0
}

//哪个最慢？哪个第二慢？哪个最快？为什么？

// 不同的运算在计算机中的实现方式和复杂度不同。

// 1. 除法运算：在大多数的处理器架构中，除法运算是最复杂的基本算术运算。它需要更多的处理器周期来完成，因此通常比加法、减法和乘法要慢。

// 2. 求余运算：求余运算通常涉及到除法运算。在大多数的处理器架构中，求余运算是通过先进行除法运算，然后返回余数来实现的。因此，求余运算的速度通常和除法运算相近。

// 3. 取地址运算：取地址运算非常简单，它只需要返回变量在内存中的地址，不涉及任何复杂的计算。因此，它通常比其他的算术运算要快。

// 实际的运算速度还会受到许多其他因素的影响，包括处理器的架构、编译器的优化等等。