import ctypes

# 加载.so文件
factors = ctypes.CDLL('./factors2.so')

# 设置参数类型
factors.print_factors.argtypes = [ctypes.c_int]

# 调用函数
a = factors.print_factors(10)

print('value of a is ',a)