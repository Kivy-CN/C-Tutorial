# C语言和Python的字符串拆分和重组功能

## 1. C语言实现

首先创建C语言源文件：

````c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 计算UTF-8字符的字节数
int utf8_char_len(unsigned char byte) {
    if (byte < 0x80) return 1;
    if ((byte >> 5) == 0x06) return 2;
    if ((byte >> 4) == 0x0e) return 3;
    if ((byte >> 3) == 0x1e) return 4;
    return 1;
}

// 获取UTF-8字符串的字符数量
int utf8_strlen(const char *str) {
    int count = 0;
    int i = 0;
    while (str[i]) {
        i += utf8_char_len((unsigned char)str[i]);
        count++;
    }
    return count;
}

// 获取第n个UTF-8字符的起始位置
int utf8_char_pos(const char *str, int n) {
    int pos = 0;
    int count = 0;
    while (str[pos] && count < n) {
        pos += utf8_char_len((unsigned char)str[pos]);
        count++;
    }
    return pos;
}

// magic函数：拆分字符串为n份
char* magic(const char* input, int n) {
    if (input == NULL || n <= 0) return NULL;
    
    int char_count = utf8_strlen(input);
    if (char_count == 0) return NULL;
    
    int chars_per_part = char_count / n;
    int remainder = char_count % n;
    
    // 计算结果字符串的最大长度
    int max_len = strlen(input) + (n - 1) * 3 + 1; // 添加分隔符"、"的空间
    char* result = (char*)malloc(max_len);
    if (result == NULL) return NULL;
    
    result[0] = '\0';
    
    int current_pos = 0;
    for (int i = 0; i < n; i++) {
        int part_size = chars_per_part + (i < remainder ? 1 : 0);
        
        if (i > 0) {
            strcat(result, "、");
        }
        
        int start_byte = utf8_char_pos(input, current_pos);
        int end_byte = utf8_char_pos(input, current_pos + part_size);
        
        // 提取子字符串
        char temp[1024];
        int len = end_byte - start_byte;
        strncpy(temp, input + start_byte, len);
        temp[len] = '\0';
        
        strcat(result, temp);
        current_pos += part_size;
    }
    
    return result;
}

// 解密函数：将用"、"分隔的字符串重新组合
char* decrypt(const char* input) {
    if (input == NULL) return NULL;
    
    int len = strlen(input);
    char* result = (char*)malloc(len + 1);
    if (result == NULL) return NULL;
    
    char* temp = (char*)malloc(len + 1);
    strcpy(temp, input);
    
    result[0] = '\0';
    char* token = strtok(temp, "、");
    
    while (token != NULL) {
        strcat(result, token);
        token = strtok(NULL, "、");
    }
    
    free(temp);
    return result;
}

// 测试函数
int main() {
    const char* test_str = "孙悟空真厉害爱吃桃";
    int n = 3;
    
    printf("原字符串: %s\n", test_str);
    printf("拆分值: %d\n", n);
    
    char* result = magic(test_str, n);
    if (result) {
        printf("拆分结果: %s\n", result);
        
        // 测试解密
        char* decrypted = decrypt(result);
        if (decrypted) {
            printf("解密结果: %s\n", decrypted);
            free(decrypted);
        }
        
        free(result);
    }
    
    return 0;
}
````

## 2. 编译为共享库并创建Python调用代码

创建头文件：

````c
#ifndef MAGIC_H
#define MAGIC_H

char* magic(const char* input, int n);
char* decrypt(const char* input);

#endif
````

编译命令：

````bash
gcc -shared -fPIC -o magic.so magic.c
````

创建Python调用代码：

````python
import ctypes
import time
from ctypes import c_char_p, c_int

# 加载共享库
lib = ctypes.CDLL('./magic.so')

# 设置函数参数和返回类型
lib.magic.argtypes = [c_char_p, c_int]
lib.magic.restype = c_char_p

lib.decrypt.argtypes = [c_char_p]
lib.decrypt.restype = c_char_p

def call_c_magic(input_str, n):
    # 将字符串编码为UTF-8字节
    input_bytes = input_str.encode('utf-8')
    result = lib.magic(input_bytes, n)
    if result:
        return result.decode('utf-8')
    return None

def call_c_decrypt(input_str):
    input_bytes = input_str.encode('utf-8')
    result = lib.decrypt(input_bytes)
    if result:
        return result.decode('utf-8')
    return None

# 使用示例（请根据你的姓名和学号修改）
name = "zhangsan"  # 替换为你的姓名全拼
student_id_last_digit = 5  # 替换为你学号的最后一位

print("=== C语言共享库调用测试 ===")
print(f"输入姓名: {name}")
print(f"拆分值: {student_id_last_digit}")

# 测试C语言函数
start_time = time.time()
c_result = call_c_magic(name, student_id_last_digit)
c_time = time.time() - start_time

if c_result:
    print(f"C语言拆分结果: {c_result}")
    
    # 测试解密
    start_time = time.time()
    c_decrypt_result = call_c_decrypt(c_result)
    c_decrypt_time = time.time() - start_time
    
    if c_decrypt_result:
        print(f"C语言解密结果: {c_decrypt_result}")
    
    print(f"C语言执行时间: {c_time:.6f}秒")
    print(f"C语言解密时间: {c_decrypt_time:.6f}秒")

print("\n" + "="*50)

# Python版本实现
def python_magic(input_str, n):
    if not input_str or n <= 0:
        return None
    
    char_count = len(input_str)
    if char_count == 0:
        return None
    
    chars_per_part = char_count // n
    remainder = char_count % n
    
    result_parts = []
    current_pos = 0
    
    for i in range(n):
        part_size = chars_per_part + (1 if i < remainder else 0)
        part = input_str[current_pos:current_pos + part_size]
        result_parts.append(part)
        current_pos += part_size
    
    return "、".join(result_parts)

def python_decrypt(input_str):
    if not input_str:
        return None
    return input_str.replace("、", "")

print("=== Python版本测试 ===")

# 测试Python版本
start_time = time.time()
py_result = python_magic(name, student_id_last_digit)
py_time = time.time() - start_time

if py_result:
    print(f"Python拆分结果: {py_result}")
    
    # 测试解密
    start_time = time.time()
    py_decrypt_result = python_decrypt(py_result)
    py_decrypt_time = time.time() - start_time
    
    if py_decrypt_result:
        print(f"Python解密结果: {py_decrypt_result}")
    
    print(f"Python执行时间: {py_time:.6f}秒")
    print(f"Python解密时间: {py_decrypt_time:.6f}秒")

print("\n" + "="*50)
print("=== 性能对比 ===")
if c_result and py_result:
    print(f"结果一致性: {'✓' if c_result == py_result else '✗'}")
    print(f"C语言总时间: {c_time + c_decrypt_time:.6f}秒")
    print(f"Python总时间: {py_time + py_decrypt_time:.6f}秒")
    speedup = (py_time + py_decrypt_time) / (c_time + c_decrypt_time)
    print(f"C语言相对于Python的加速比: {speedup:.2f}x")
````

## 使用说明

1. **编译C代码**：
   ```bash
   gcc -shared -fPIC -o magic.so magic.c
   ```

2. **运行Python测试**：
   ```bash
   python test_magic.py
   ```

3. **修改参数**：请在`test_magic.py`中修改以下变量：
   - `name`: 改为你的姓名全拼
   - `student_id_last_digit`: 改为你学号的最后一位数字

## 关键特性

1. **UTF-8支持**：C代码正确处理中文字符的UTF-8编码
2. **内存管理**：使用malloc分配内存，调用者需要释放
3. **解密功能**：利用相同的逻辑可以通过字符串替换实现解密
4. **性能对比**：Python版本通常会比C版本慢，但具体差异取决于字符串长度和系统性能

运行后会显示两个版本的执行结果和性能对比，通常C语言版本会有更好的性能表现。