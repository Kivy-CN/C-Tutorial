# file: call_clib.py
# ------------------
# 这个脚本演示了如何使用 Python 的 ctypes 库调用 C 语言编写的动态链接库。
# 
# 前置条件：
# 请先编译 clib_math.c 生成 clib_math.dll (Windows) 或 clib_math.so (Linux/macOS)

import ctypes
import os
import sys

def main():
    # 1. 加载动态库
    # 根据操作系统确定扩展名
    if sys.platform == 'win32':
        lib_name = 'clib_math.dll'
    else:
        lib_name = 'clib_math.so'
        
    lib_path = os.path.join(os.path.dirname(__file__), lib_name)
    
    if not os.path.exists(lib_path):
        print(f"Error: 找不到库文件 {lib_path}")
        print("请先编译 C 代码: clang -shared clib_math.c -o clib_math.dll")
        return

    try:
        # 加载库
        clib = ctypes.CDLL(lib_path)
    except OSError as e:
        print(f"加载库失败: {e}")
        return

    print(f"成功加载: {lib_name}")

    # 2. 调用 add 函数
    # 指定参数类型和返回值类型 (虽然简单类型 ctypes 能自动推断，但显式指定更安全)
    clib.add.argtypes = [ctypes.c_int, ctypes.c_int]
    clib.add.restype = ctypes.c_int

    a, b = 10, 20
    result = clib.add(a, b)
    print(f"Python 调用 C: add({a}, {b}) = {result}")

    # 3. 调用 hello_msg 函数 (传递字符串缓冲区)
    clib.hello_msg.argtypes = [ctypes.c_char_p, ctypes.c_int]
    clib.hello_msg.restype = None

    # 创建一个可写的 buffer
    buf_size = 50
    buffer = ctypes.create_string_buffer(buf_size)
    
    clib.hello_msg(buffer, buf_size)
    print(f"C 返回的消息: {buffer.value.decode('utf-8')}")

if __name__ == '__main__':
    main()
