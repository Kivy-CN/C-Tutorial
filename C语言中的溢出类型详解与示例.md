## 1. 整数溢出

整数溢出发生在算术运算结果超出数据类型能表示的范围时。

````c
#include <stdio.h>
#include <limits.h>

int main() {
    int max_int = INT_MAX;  // 2,147,483,647
    printf("INT_MAX: %d\n", max_int);
    
    int overflow = max_int + 1;  // 整数溢出
    printf("溢出后: %d\n", overflow);  // 输出: -2,147,483,648
    
    unsigned int unsigned_overflow = UINT_MAX + 1;  // 无符号整数溢出
    printf("无符号溢出: %u\n", unsigned_overflow);  // 输出: 0
    return 0;
}
````

## 2. 浮点溢出

浮点溢出发生在浮点运算结果超出浮点类型的表示范围时。

````c
#include <stdio.h>
#include <float.h>

int main() {
    float max_float = FLT_MAX;  // 大约 3.4e+38
    printf("FLT_MAX: %e\n", max_float);
    
    float overflow = max_float * 10.0f;  // 浮点溢出
    printf("溢出后: %e\n", overflow);  // 输出: inf (无穷大)
    
    double underflow = 1e-400;  // 下溢出
    printf("下溢出: %e\n", underflow);  // 输出: 0.000000e+00
    return 0;
}
````

## 3. 栈溢出

栈溢出通常由无限递归或过大的局部变量引起。

````c
#include <stdio.h>

// 无限递归导致栈溢出
void recursive_function(int n) {
    char large_array[10000];  // 大量局部变量
    printf("递归深度: %d\n", n);
    recursive_function(n + 1);  // 无限递归
}

// 大数组导致栈溢出
void stack_overflow_array() {
    int huge_array[1000000];  // 约4MB的数组，可能超出栈限制
    huge_array[0] = 1;
    printf("创建了大数组\n");
}

int main() {
    // recursive_function(1);  // 会导致栈溢出
    // stack_overflow_array(); // 可能导致栈溢出
    return 0;
}
````

## 4. 堆溢出

堆溢出发生在动态分配的内存超出可用堆空间时。

````c
#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t total_allocated = 0;
    void* ptrs[1000];
    int count = 0;
    
    // 持续分配内存直到堆耗尽
    while (count < 1000) {
        size_t size = 100 * 1024 * 1024;  // 每次分配100MB
        ptrs[count] = malloc(size);
        
        if (ptrs[count] == NULL) {
            printf("堆溢出！无法分配更多内存\n");
            printf("已分配: %zu MB\n", total_allocated / (1024 * 1024));
            break;
        }
        
        total_allocated += size;
        count++;
        printf("已分配 %d 次，总计: %zu MB\n", count, total_allocated / (1024 * 1024));
    }
    
    // 释放已分配的内存
    for (int i = 0; i < count; i++) {
        free(ptrs[i]);
    }
    
    return 0;
}
````

## 5. 数组越界

数组越界是访问数组时使用超出有效范围的索引。

````c
#include <stdio.h>

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    int adjacent_var = 100;
    
    printf("数组内容:\n");
    for (int i = 0; i < 5; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    
    printf("\n越界访问:\n");
    // 读取越界
    printf("arr[5] = %d (越界读取)\n", arr[5]);
    printf("arr[-1] = %d (负索引越界)\n", arr[-1]);
    
    // 写入越界 - 危险操作！
    arr[10] = 999;  // 可能覆盖其他变量的内存
    printf("写入arr[10] = 999\n");
    
    printf("adjacent_var可能被影响: %d\n", adjacent_var);
    
    return 0;
}
````

这些溢出问题在C语言中非常常见，需要程序员格外小心。使用工具如Valgrind、AddressSanitizer等可以帮助检测这些问题。


这个问题涉及到数组定义和字符串存储的区别：

## 数组容量 vs 有效数据

**int数组**：
````c
int arr[50];  // 可以存储50个整数
arr[0] = 1;
arr[1] = 2;
// ...
arr[49] = 50;  // 第50个整数
````

int数组的每个元素都是独立的整数，不需要特殊的结束标记，所以50个位置都可以存放有效数据。

**char数组作为字符串**：
````c
char str[50];  // 作为字符串只能存49个有效字符
strcpy(str, "Hello");  // 实际存储: 'H','e','l','l','o','\0'
````

## 关键区别：字符串的空字符结束符

C语言中的字符串必须以`'\0'`（空字符，ASCII值为0）结尾，这是字符串的标准约定。

````c
#include <stdio.h>
#include <string.h>

int main() {
    // int数组示例
    int numbers[3] = {10, 20, 30};  // 存储3个整数
    printf("int数组:\n");
    for(int i = 0; i < 3; i++) {
        printf("numbers[%d] = %d\n", i, numbers[i]);
    }
    
    // char数组示例
    char text[5];  // 长度为5
    strcpy(text, "abc");  // 只能存3个字符 + 1个'\0'
    
    printf("\nchar数组内容:\n");
    for(int i = 0; i < 5; i++) {
        printf("text[%d] = '%c' (ASCII: %d)\n", i, 
               text[i] ? text[i] : '0', (int)text[i]);
    }
    
    // 尝试存储更多字符
    char full[5] = {'a', 'b', 'c', 'd', '\0'};  // 4个字符 + 结束符
    printf("\n完整使用的char数组: %s\n", full);
    
    // 如果不加'\0'，会出现问题
    char no_null[5] = {'a', 'b', 'c', 'd', 'e'};  // 没有'\0'
    printf("没有空字符的数组: ");
    // 这样打印可能会输出垃圾字符，因为没有结束标记
    // printf("%s\n", no_null);  // 危险！
    
    return 0;
}
````

## 为什么需要空字符？

1. **字符串函数的工作原理**：`strlen()`、`printf("%s")`等函数通过寻找`'\0'`来确定字符串结束位置
2. **内存安全**：防止读取超出字符串边界的内存
3. **标准约定**：C语言字符串的基本规则

````c
char buffer[10];
strcpy(buffer, "123456789");  // 只能复制9个字符，第10个位置必须是'\0'

// 最大有效字符串: "123456789\0"
//                   ^-9个字符-^ ^空字符
````

