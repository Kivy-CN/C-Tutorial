# 接下来，我们在Python中使用`ctypes`库来加载和调用这个.so文件：

import ctypes
import os

# 获取当前Python源代码文件所在的路径
current_path = os.path.abspath(__file__)
# 获取当前Python源代码文件所在的文件夹路径
current_dir = os.path.dirname(os.path.abspath(__file__))

# 加载.so文件
factors = ctypes.CDLL(current_dir +'\\factors.so')

# 设置参数类型
factors.print_factors.argtypes = [ctypes.c_int]

# 调用函数
factors.print_factors(30)


# 在这个Python代码中，我们首先加载了.so文件，然后设置了`print_factors`函数的参数类型，最后调用了这个函数。

# 请注意，这只是一个基本示例。在实际使用中，你可能需要处理更复杂的情况，比如错误处理、内存管理等。
# 此外，这个示例假设你的C函数只有一个整数参数，并且你的Python代码和.so文件在同一目录下。如果你的情况有所不同，你可能需要进行相应的调整。