import time
import math
import platform
import sys

ITERATIONS = 100000000  # 测试迭代次数

# 使用ASCII字符，避免中文显示问题
def print_results(operation, elapsed_time):
    print(f"{operation}: {elapsed_time:.6f} seconds")

# 获取高精度时间（单位：秒）
def get_time():
    return time.perf_counter()

# 测试整数运算
def test_integer_operations():
    a = 123456789
    b = 987654321
    c = 0
    
    # 测试整数加法
    start = get_time()
    for i in range(ITERATIONS):
        c = a + b
    end = get_time()
    print_results("Integer Addition", end - start)
    
    # 测试整数减法
    start = get_time()
    for i in range(ITERATIONS):
        c = a - b
    end = get_time()
    print_results("Integer Subtraction", end - start)
    
    # 测试整数乘法
    start = get_time()
    for i in range(ITERATIONS):
        c = a * b
    end = get_time()
    print_results("Integer Multiplication", end - start)
    
    # 测试整数除法
    start = get_time()
    for i in range(ITERATIONS):
        c = a // (b // 1000)  # 避免除以太大的数，使用整数除法
    end = get_time()
    print_results("Integer Division", end - start)

# 测试浮点数运算
def test_floating_operations():
    a = 123456.789
    b = 987.654321
    c = 0.0
    
    # 测试浮点数加法
    start = get_time()
    for i in range(ITERATIONS):
        c = a + b
    end = get_time()
    print_results("Float Addition", end - start)
    
    # 测试浮点数减法
    start = get_time()
    for i in range(ITERATIONS):
        c = a - b
    end = get_time()
    print_results("Float Subtraction", end - start)
    
    # 测试浮点数乘法
    start = get_time()
    for i in range(ITERATIONS):
        c = a * b
    end = get_time()
    print_results("Float Multiplication", end - start)
    
    # 测试浮点数除法
    start = get_time()
    for i in range(ITERATIONS):
        c = a / b
    end = get_time()
    print_results("Float Division", end - start)

# 测试数学函数
def test_math_functions():
    a = 0.5
    result = 0.0
    
    # 测试sin函数
    start = get_time()
    for i in range(ITERATIONS):
        result = math.sin(a)
    end = get_time()
    print_results("sin() function ", end - start)
    
    # 测试cos函数
    start = get_time()
    for i in range(ITERATIONS):
        result = math.cos(a)
    end = get_time()
    print_results("cos() function ", end - start)
    
    # 测试sqrt函数
    start = get_time()
    for i in range(ITERATIONS):
        result = math.sqrt(a)
    end = get_time()
    print_results("sqrt() function ", end - start)
    
    # 测试log函数
    start = get_time()
    for i in range(ITERATIONS):
        result = math.log(a)
    end = get_time()
    print_results("log() function ", end - start)
    
    # 测试exp函数
    start = get_time()
    for i in range(ITERATIONS):
        result = math.exp(a)
    end = get_time()
    print_results("exp() function ", end - start)

def main():
    print(f"PERFORMANCE TEST STARTING (iterations: {ITERATIONS})\n")
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