import ctypes

# 加载.so文件
factors = ctypes.CDLL('./factors.so')

# 设置参数类型
factors.print_factors.argtypes = [ctypes.c_int]

# 调用函数
factors.print_factors(10)