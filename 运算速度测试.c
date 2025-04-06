#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <locale.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>  // For Windows high-performance timer
    #define IS_WINDOWS 1
#else
    #include <sys/time.h>  // For non-Windows systems (Unix/Linux/Mac)
    #define IS_WINDOWS 0
#endif

#define ITERATIONS 100000000   // 测试迭代次数

// 使用ASCII字符，避免中文显示问题
void print_results(const char* operation, double time) {
    printf("%s: %.6f seconds\n", operation, time);
}

// 获取高精度时间（单位：秒）
double get_time() {
    #ifdef _WIN32
        LARGE_INTEGER frequency, count;
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&count);
        return (double)count.QuadPart / (double)frequency.QuadPart;
    #else
        struct timeval tv;
        gettimeofday(&tv, NULL);
        return tv.tv_sec + tv.tv_usec / 1000000.0;
    #endif
}

// 测试整数运算
void test_integer_operations() {
    int a = 123456789;
    int b = 987654321;
    int c = 0;
    
    double start, end;
    
    // 测试整数加法
    start = get_time();
    for (long i = 0; i < ITERATIONS; i++) {
        c = a + b;
    }
    end = get_time();
    print_results("Integer Addition", end - start);
    
    // 测试整数减法
    start = get_time();
    for (long i = 0; i < ITERATIONS; i++) {
        c = a - b;
    }
    end = get_time();
    print_results("Integer Subtraction", end - start);
    
    // 测试整数乘法
    start = get_time();
    for (long i = 0; i < ITERATIONS; i++) {
        c = a * b;
    }
    end = get_time();
    print_results("Integer Multiplication", end - start);
    
    // 测试整数除法
    start = get_time();
    for (long i = 0; i < ITERATIONS; i++) {
        c = a / (b / 1000);  // 避免除以太大的数
    }
    end = get_time();
    print_results("Integer Division", end - start);
}

// 测试浮点数运算
void test_floating_operations() {
    double a = 123456.789;
    double b = 987.654321;
    double c = 0.0;
    
    double start, end;
    
    // 测试浮点数加法
    start = get_time();
    for (long i = 0; i < ITERATIONS; i++) {
        c = a + b;
    }
    end = get_time();
    print_results("Float Addition", end - start);
    
    // 测试浮点数减法
    start = get_time();
    for (long i = 0; i < ITERATIONS; i++) {
        c = a - b;
    }
    end = get_time();
    print_results("Float Subtraction", end - start);
    
    // 测试浮点数乘法
    start = get_time();
    for (long i = 0; i < ITERATIONS; i++) {
        c = a * b;
    }
    end = get_time();
    print_results("Float Multiplication", end - start);
    
    // 测试浮点数除法
    start = get_time();
    for (long i = 0; i < ITERATIONS; i++) {
        c = a / b;
    }
    end = get_time();
    print_results("Float Division", end - start);
}

// 测试数学函数
void test_math_functions() {
    double a = 0.5;
    double result = 0.0;
    
    double start, end;
    
    // 测试sin函数
    start = get_time();
    for (long i = 0; i < ITERATIONS ; i++) {  // 数学函数运算较慢，减少迭代次数
        result = sin(a);
    }
    end = get_time();
    print_results("sin() function ", end - start);
    
    // 测试cos函数
    start = get_time();
    for (long i = 0; i < ITERATIONS ; i++) {
        result = cos(a);
    }
    end = get_time();
    print_results("cos() function ", end - start);
    
    // 测试sqrt函数
    start = get_time();
    for (long i = 0; i < ITERATIONS ; i++) {
        result = sqrt(a);
    }
    end = get_time();
    print_results("sqrt() function ", end - start);
    
    // 测试log函数
    start = get_time();
    for (long i = 0; i < ITERATIONS ; i++) {
        result = log(a);
    }
    end = get_time();
    print_results("log() function ", end - start);
    
    // 测试exp函数
    start = get_time();
    for (long i = 0; i < ITERATIONS ; i++) {
        result = exp(a);
    }
    end = get_time();
    print_results("exp() function ", end - start);
}

int main() {
    printf("PERFORMANCE TEST STARTING (iterations: %d)\n\n", ITERATIONS);
    printf("Current system: %s\n\n", IS_WINDOWS ? "Windows" : "Non-Windows");
    
    printf("=== INTEGER OPERATIONS TEST ===\n");
    test_integer_operations();
    printf("\n");
    
    printf("=== FLOATING POINT OPERATIONS TEST ===\n");
    test_floating_operations();
    printf("\n");
    
    printf("=== MATH FUNCTIONS TEST ===\n");
    test_math_functions();
    
    return 0;
}