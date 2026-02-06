/*
 * file: clib_math.c
 * -----------------
 * 这是一个简单的 C 库，将被编译为动态链接库 (Shared Library)，
 * 并由 Python 通过 ctypes 调用。
 * 
 * 编译命令:
 *   Windows (PowerShell):
 *     clang -shared clib_math.c -o clib_math.dll
 *   Linux/macOS:
 *     clang -shared -fPIC clib_math.c -o clib_math.so
 */

#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

// 一个简单的加法函数
DLLEXPORT int add(int a, int b) {
    return a + b;
}

// 字符串处理函数
// Python 传入 bytes, C 修改缓冲区内容 (注意缓冲区溢出风险)
DLLEXPORT void hello_msg(char *buffer, int size) {
    // 简单地将字符串复制到 buffer
    // 实际生产中应使用更安全的 snprintf
    const char *msg = "Hello from C Library!";
    int i;
    for (i = 0; i < size - 1 && msg[i] != '\0'; i++) {
        buffer[i] = msg[i];
    }
    buffer[i] = '\0';
}
