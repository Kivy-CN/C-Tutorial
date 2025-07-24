# 凯撒密码的C语言实现和Python调用的完整过程

## 1. C语言实现凯撒密码

````c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* magic(const char* input, int shift) {
    if (input == NULL) return NULL;
    
    int len = strlen(input);
    char* result = (char*)malloc((len + 1) * sizeof(char));
    
    if (result == NULL) return NULL;
    
    for (int i = 0; i < len; i++) {
        char c = input[i];
        
        if (c >= 'a' && c <= 'z') {
            // 小写字母处理
            result[i] = ((c - 'a' + shift + 26) % 26) + 'a';
        } else if (c >= 'A' && c <= 'Z') {
            // 大写字母处理
            result[i] = ((c - 'A' + shift + 26) % 26) + 'A';
        } else {
            // 非字母字符保持不变
            result[i] = c;
        }
    }
    
    result[len] = '\0';
    return result;
}

// 测试函数
int main() {
    char* encrypted = magic("chen", -1);
    printf("Encrypted: %s\n", encrypted);
    
    // 解密：使用相反的移位值
    char* decrypted = magic(encrypted, 1);
    printf("Decrypted: %s\n", decrypted);
    
    free(encrypted);
    free(decrypted);
    
    return 0;
}
````

**解密原理**：凯撒密码的解密可以通过使用相反的移位值来实现。如果加密时移位值为`n`，那么解密时使用移位值`-n`即可。

## 2. 编译为SO文件和Python调用

首先编译C代码为共享库：

````bash
gcc -shared -fPIC -o libcaesar.so caesar.c
````

Python调用代码：

````python
import ctypes
import time

# 加载共享库
lib = ctypes.CDLL('./libcaesar.so')

# 设置函数签名
lib.magic.argtypes = [ctypes.c_char_p, ctypes.c_int]
lib.magic.restype = ctypes.c_char_p

def caesar_c(text, shift):
    """调用C语言实现的凯撒密码"""
    result = lib.magic(text.encode('utf-8'), shift)
    if result:
        return result.decode('utf-8')
    return None

# 使用示例（请替换为你的姓名和学号）
name = "zhangsan"  # 替换为你的姓名全拼
student_id_last_digit = 5  # 替换为你学号的最后一位

print(f"原文: {name}")
encrypted = caesar_c(name, student_id_last_digit)
print(f"加密后: {encrypted}")

# 解密
decrypted = caesar_c(encrypted, -student_id_last_digit)
print(f"解密后: {decrypted}")
````

## 3. Python版本实现和性能对比

````python
import ctypes
import time

# 加载C共享库
lib = ctypes.CDLL('./libcaesar.so')
lib.magic.argtypes = [ctypes.c_char_p, ctypes.c_int]
lib.magic.restype = ctypes.c_char_p

def caesar_c(text, shift):
    """C语言版本"""
    result = lib.magic(text.encode('utf-8'), shift)
    if result:
        return result.decode('utf-8')
    return None

def caesar_python(text, shift):
    """Python版本的凯撒密码"""
    result = []
    for c in text:
        if 'a' <= c <= 'z':
            result.append(chr((ord(c) - ord('a') + shift) % 26 + ord('a')))
        elif 'A' <= c <= 'Z':
            result.append(chr((ord(c) - ord('A') + shift) % 26 + ord('A')))
        else:
            result.append(c)
    return ''.join(result)

# 测试数据
name = "zhangsan"  # 替换为你的姓名
shift_value = 5    # 替换为你学号最后一位
test_text = name * 1000  # 创建较长的测试字符串

# 性能测试
def benchmark(func, text, shift, iterations=10000):
    start_time = time.time()
    for _ in range(iterations):
        result = func(text, shift)
    end_time = time.time()
    return end_time - start_time, result

print("=== 功能测试 ===")
print(f"原文: {name}")

# C版本测试
c_encrypted = caesar_c(name, shift_value)
c_decrypted = caesar_c(c_encrypted, -shift_value)
print(f"C版本 - 加密: {c_encrypted}, 解密: {c_decrypted}")

# Python版本测试
py_encrypted = caesar_python(name, shift_value)
py_decrypted = caesar_python(py_encrypted, -shift_value)
print(f"Python版本 - 加密: {py_encrypted}, 解密: {py_decrypted}")

print(f"结果一致性: {c_encrypted == py_encrypted}")

print("\n=== 性能测试 ===")
# 性能对比
c_time, _ = benchmark(caesar_c, test_text, shift_value)
py_time, _ = benchmark(caesar_python, test_text, shift_value)

print(f"C语言版本耗时: {c_time:.4f} 秒")
print(f"Python版本耗时: {py_time:.4f} 秒")
print(f"Python版本比C语言版本慢 {py_time/c_time:.2f} 倍")
````

## 使用步骤

1. **编译C代码**：
   ```bash
   gcc -shared -fPIC -o libcaesar.so caesar.c
   ```

2. **运行Python测试**：
   ```bash
   python caesar_comparison.py
   ```

3. **记得修改**：
   - 将 `"zhangsan"` 替换为你的姓名全拼
   - 将 `5` 替换为你学号的最后一位数字

这个实现展示了：
- 凯撒密码的加密和解密（使用相反移位值）
- C语言和Python的性能差异
- 跨语言调用的方法

通常C语言版本会比Python版本快很多，特别是在处理大量数据时。