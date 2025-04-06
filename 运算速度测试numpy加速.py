import time
import math
import platform
import numpy as np

ITERATIONS = 100000000  # 测试迭代次数

# 使用ASCII字符，避免中文显示问题
def print_results(operation, elapsed_time):
    print(f"{operation}: {elapsed_time:.6f} seconds")

# 获取高精度时间（单位：秒）
def get_time():
    return time.perf_counter()

# 测试整数运算 - NumPy向量化版本
def test_integer_operations():
    a = 123456789
    b = 987654321
    
    # 使用NumPy数组进行批量运算
    a_array = np.full(ITERATIONS, a, dtype=np.int32)
    b_array = np.full(ITERATIONS, b, dtype=np.int32)
    
    # 测试整数加法
    start = get_time()
    c = a_array + b_array
    end = get_time()
    print_results("Integer Addition", end - start)
    
    # 测试整数减法
    start = get_time()
    c = a_array - b_array
    end = get_time()
    print_results("Integer Subtraction", end - start)
    
    # 测试整数乘法
    start = get_time()
    c = a_array * b_array
    end = get_time()
    print_results("Integer Multiplication", end - start)
    
    # 测试整数除法
    b_scaled = b_array // 1000  # 避免除以太大的数
    start = get_time()
    c = a_array // b_scaled
    end = get_time()
    print_results("Integer Division", end - start)

# 测试浮点数运算 - NumPy向量化版本
def test_floating_operations():
    a = 123456.789
    b = 987.654321
    
    a_array = np.full(ITERATIONS, a, dtype=np.float64)
    b_array = np.full(ITERATIONS, b, dtype=np.float64)
    
    # 测试浮点数加法
    start = get_time()
    c = a_array + b_array
    end = get_time()
    print_results("Float Addition", end - start)
    
    # 测试浮点数减法
    start = get_time()
    c = a_array - b_array
    end = get_time()
    print_results("Float Subtraction", end - start)
    
    # 测试浮点数乘法
    start = get_time()
    c = a_array * b_array
    end = get_time()
    print_results("Float Multiplication", end - start)
    
    # 测试浮点数除法
    start = get_time()
    c = a_array / b_array
    end = get_time()
    print_results("Float Division", end - start)

# 测试数学函数 - NumPy向量化版本
def test_math_functions():
    a = 0.5
    a_array = np.full(ITERATIONS, a, dtype=np.float64)
    
    # 测试sin函数
    start = get_time()
    result = np.sin(a_array)
    end = get_time()
    print_results("sin() function ", end - start)
    
    # 测试cos函数
    start = get_time()
    result = np.cos(a_array)
    end = get_time()
    print_results("cos() function ", end - start)
    
    # 测试sqrt函数
    start = get_time()
    result = np.sqrt(a_array)
    end = get_time()
    print_results("sqrt() function ", end - start)
    
    # 测试log函数
    start = get_time()
    result = np.log(a_array)
    end = get_time()
    print_results("log() function ", end - start)
    
    # 测试exp函数
    start = get_time()
    result = np.exp(a_array)
    end = get_time()
    print_results("exp() function ", end - start)

def main():
    print(f"NUMPY PERFORMANCE TEST STARTING (size: {ITERATIONS})\n")
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