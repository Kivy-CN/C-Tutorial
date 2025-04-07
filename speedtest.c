#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <locale.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>  // For Windows high-performance timer
    #define IS_WINDOWS 1
    #define EXPORT __declspec(dllexport)
#else
    #include <sys/time.h>  // For non-Windows systems (Unix/Linux/Mac)
    #define IS_WINDOWS 0
    #define EXPORT
#endif

// 结果结构体
typedef struct {
    double int_add;
    double int_sub;
    double int_mul;
    double int_div;
    double float_add;
    double float_sub;
    double float_mul;
    double float_div;
    double sin_func;
    double cos_func;
    double sqrt_func;
    double log_func;
    double exp_func;
} BenchmarkResults;

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
void test_integer_operations(long iterations, BenchmarkResults* results) {
    int a = 123456789;
    int b = 987654321;
    int c = 0;
    
    double start, end;
    
    // 测试整数加法
    start = get_time();
    for (long i = 0; i < iterations; i++) {
        c = a + b;
    }
    end = get_time();
    results->int_add = end - start;
    print_results("Integer Addition", results->int_add);
    
    // 测试整数减法
    start = get_time();
    for (long i = 0; i < iterations; i++) {
        c = a - b;
    }
    end = get_time();
    results->int_sub = end - start;
    print_results("Integer Subtraction", results->int_sub);
    
    // 测试整数乘法
    start = get_time();
    for (long i = 0; i < iterations; i++) {
        c = a * b;
    }
    end = get_time();
    results->int_mul = end - start;
    print_results("Integer Multiplication", results->int_mul);
    
    // 测试整数除法
    start = get_time();
    for (long i = 0; i < iterations; i++) {
        c = a / (b / 1000);  // 避免除以太大的数
    }
    end = get_time();
    results->int_div = end - start;
    print_results("Integer Division", results->int_div);
}

// 测试浮点数运算
void test_floating_operations(long iterations, BenchmarkResults* results) {
    double a = 123456.789;
    double b = 987.654321;
    double c = 0.0;
    
    double start, end;
    
    // 测试浮点数加法
    start = get_time();
    for (long i = 0; i < iterations; i++) {
        c = a + b;
    }
    end = get_time();
    results->float_add = end - start;
    print_results("Float Addition", results->float_add);
    
    // 测试浮点数减法
    start = get_time();
    for (long i = 0; i < iterations; i++) {
        c = a - b;
    }
    end = get_time();
    results->float_sub = end - start;
    print_results("Float Subtraction", results->float_sub);
    
    // 测试浮点数乘法
    start = get_time();
    for (long i = 0; i < iterations; i++) {
        c = a * b;
    }
    end = get_time();
    results->float_mul = end - start;
    print_results("Float Multiplication", results->float_mul);
    
    // 测试浮点数除法
    start = get_time();
    for (long i = 0; i < iterations; i++) {
        c = a / b;
    }
    end = get_time();
    results->float_div = end - start;
    print_results("Float Division", results->float_div);
}

// 测试数学函数
void test_math_functions(long iterations, BenchmarkResults* results) {
    double a = 0.5;
    double result = 0.0;
    
    double start, end;
    
    // 测试sin函数
    start = get_time();
    for (long i = 0; i < iterations; i++) {
        result = sin(a);
    }
    end = get_time();
    results->sin_func = end - start;
    print_results("sin() function ", results->sin_func);
    
    // 测试cos函数
    start = get_time();
    for (long i = 0; i < iterations; i++) {
        result = cos(a);
    }
    end = get_time();
    results->cos_func = end - start;
    print_results("cos() function ", results->cos_func);
    
    // 测试sqrt函数
    start = get_time();
    for (long i = 0; i < iterations; i++) {
        result = sqrt(a);
    }
    end = get_time();
    results->sqrt_func = end - start;
    print_results("sqrt() function ", results->sqrt_func);
    
    // 测试log函数
    start = get_time();
    for (long i = 0; i < iterations; i++) {
        result = log(a);
    }
    end = get_time();
    results->log_func = end - start;
    print_results("log() function ", results->log_func);
    
    // 测试exp函数
    start = get_time();
    for (long i = 0; i < iterations; i++) {
        result = exp(a);
    }
    end = get_time();
    results->exp_func = end - start;
    print_results("exp() function ", results->exp_func);
}

// 导出函数，可被Python调用
EXPORT BenchmarkResults run_benchmark(long iterations) {
    BenchmarkResults results = {0};
    
    printf("PERFORMANCE TEST STARTING (iterations: %ld)\n\n", iterations);
    printf("Current system: %s\n\n", IS_WINDOWS ? "Windows" : "Non-Windows");
    
    printf("=== INTEGER OPERATIONS TEST ===\n");
    test_integer_operations(iterations, &results);
    printf("\n");
    
    printf("=== FLOATING POINT OPERATIONS TEST ===\n");
    test_floating_operations(iterations, &results);
    printf("\n");
    
    printf("=== MATH FUNCTIONS TEST ===\n");
    test_math_functions(iterations, &results);
    
    return results;
}

// 保留主函数用于独立测试
int main() {
    BenchmarkResults results = run_benchmark(100000000);
    return 0;
}