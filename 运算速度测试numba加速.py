import time
import math
import platform
import numba
from numba import njit

ITERATIONS = 100000000  # 测试迭代次数

# 使用ASCII字符，避免中文显示问题
def print_results(operation, elapsed_time):
    print(f"{operation}: {elapsed_time:.6f} seconds")

# 获取高精度时间（单位：秒）
def get_time():
    return time.perf_counter()

# 测试整数运算 - Numba JIT编译版本
@njit
def integer_add(iterations, a, b):
    c = 0
    for i in range(iterations):
        c = a + b
    return c

@njit
def integer_subtract(iterations, a, b):
    c = 0
    for i in range(iterations):
        c = a - b
    return c

@njit
def integer_multiply(iterations, a, b):
    c = 0
    for i in range(iterations):
        c = a * b
    return c

@njit
def integer_divide(iterations, a, b):
    c = 0
    for i in range(iterations):
        c = a // (b // 1000)
    return c

def test_integer_operations():
    a = 123456789
    b = 987654321
    
    # 预热JIT编译器（第一次运行会包括编译时间）
    integer_add(1, a, b)
    integer_subtract(1, a, b)
    integer_multiply(1, a, b)
    integer_divide(1, a, b)
    
    # 测试整数加法
    start = get_time()
    integer_add(ITERATIONS, a, b)
    end = get_time()
    print_results("Integer Addition", end - start)
    
    # 测试整数减法
    start = get_time()
    integer_subtract(ITERATIONS, a, b)
    end = get_time()
    print_results("Integer Subtraction", end - start)
    
    # 测试整数乘法
    start = get_time()
    integer_multiply(ITERATIONS, a, b)
    end = get_time()
    print_results("Integer Multiplication", end - start)
    
    # 测试整数除法
    start = get_time()
    integer_divide(ITERATIONS, a, b)
    end = get_time()
    print_results("Integer Division", end - start)

# 测试浮点数运算 - Numba JIT编译版本
@njit
def float_add(iterations, a, b):
    c = 0.0
    for i in range(iterations):
        c = a + b
    return c

@njit
def float_subtract(iterations, a, b):
    c = 0.0
    for i in range(iterations):
        c = a - b
    return c

@njit
def float_multiply(iterations, a, b):
    c = 0.0
    for i in range(iterations):
        c = a * b
    return c

@njit
def float_divide(iterations, a, b):
    c = 0.0
    for i in range(iterations):
        c = a / b
    return c

def test_floating_operations():
    a = 123456.789
    b = 987.654321
    
    # 预热JIT编译器
    float_add(1, a, b)
    float_subtract(1, a, b)
    float_multiply(1, a, b)
    float_divide(1, a, b)
    
    # 测试浮点数加法
    start = get_time()
    float_add(ITERATIONS, a, b)
    end = get_time()
    print_results("Float Addition", end - start)
    
    # 测试浮点数减法
    start = get_time()
    float_subtract(ITERATIONS, a, b)
    end = get_time()
    print_results("Float Subtraction", end - start)
    
    # 测试浮点数乘法
    start = get_time()
    float_multiply(ITERATIONS, a, b)
    end = get_time()
    print_results("Float Multiplication", end - start)
    
    # 测试浮点数除法
    start = get_time()
    float_divide(ITERATIONS, a, b)
    end = get_time()
    print_results("Float Division", end - start)

# 测试数学函数 - Numba JIT编译版本
@njit
def math_sin(iterations, a):
    result = 0.0
    for i in range(iterations):
        result = math.sin(a)
    return result

@njit
def math_cos(iterations, a):
    result = 0.0
    for i in range(iterations):
        result = math.cos(a)
    return result

@njit
def math_sqrt(iterations, a):
    result = 0.0
    for i in range(iterations):
        result = math.sqrt(a)
    return result

@njit
def math_log(iterations, a):
    result = 0.0
    for i in range(iterations):
        result = math.log(a)
    return result

@njit
def math_exp(iterations, a):
    result = 0.0
    for i in range(iterations):
        result = math.exp(a)
    return result

def test_math_functions():
    a = 0.5
    
    # 预热JIT编译器
    math_sin(1, a)
    math_cos(1, a)
    math_sqrt(1, a)
    math_log(1, a)
    math_exp(1, a)
    
    # 测试sin函数
    start = get_time()
    math_sin(ITERATIONS, a)
    end = get_time()
    print_results("sin() function ", end - start)
    
    # 测试cos函数
    start = get_time()
    math_cos(ITERATIONS, a)
    end = get_time()
    print_results("cos() function ", end - start)
    
    # 测试sqrt函数
    start = get_time()
    math_sqrt(ITERATIONS, a)
    end = get_time()
    print_results("sqrt() function ", end - start)
    
    # 测试log函数
    start = get_time()
    math_log(ITERATIONS, a)
    end = get_time()
    print_results("log() function ", end - start)
    
    # 测试exp函数
    start = get_time()
    math_exp(ITERATIONS, a)
    end = get_time()
    print_results("exp() function ", end - start)

def main():
    print(f"NUMBA PERFORMANCE TEST STARTING (iterations: {ITERATIONS})\n")
    print(f"Current system: {platform.system()}\n")
    
    print("=== INTEGER OPERATIONS TEST ===")
    test_integer_operations()
    print()
    
    print("=== FLOATING POINT OPERATIONS TEST ===")
    test_floating_operations()
    print()
    
    print("=== MATH FUNCTIONS TEST ===")
    test_math_functions()

if __name__ == "__main__":
    main()