import ctypes

# 加载.so文件
factors = ctypes.CDLL('./factors3.so')

# 设置参数类型和返回类型
factors.get_factors.argtypes = [ctypes.c_int, ctypes.POINTER(ctypes.c_int)]
factors.get_factors.restype = ctypes.POINTER(ctypes.c_int)
factors.free_factors.argtypes = [ctypes.POINTER(ctypes.c_int)]

# 调用函数
num = 10
count = ctypes.c_int()
factors_list = factors.get_factors(num, ctypes.byref(count))

# 将因子列表转换为Python列表
factors_py = [factors_list[i] for i in range(count.value)]

# 释放内存
factors.free_factors(factors_list)

# 打印因子列表
print(factors_py)
