/*
 * file: stack_and_call.c
 * ----------------------
 * 这个程序展示了 C 语言函数调用的核心机制。
 * 
 * 知识点：
 * 1. 值传递 (Pass by Value) vs 指针传递 (Pass by Pointer/Reference)
 * 2. 栈帧 (Stack Frame) 与 递归
 * 3. 静态局部变量 (Static Local Variables)
 *
 * 编译命令:
 *   clang stack_and_call.c -o stack_and_call
 */

#include <stdio.h>

// 1. 值传递：修改形参不会影响实参
void swap_by_value(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    printf("[Inside Value Swap] a=%d, b=%d\n", a, b);
}

// 2. 指针传递：通过地址修改实参
void swap_by_pointer(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    printf("[Inside Pointer Swap] *a=%d, *b=%d\n", *a, *b);
}

// 3. 递归与栈帧演示
// 每次函数调用都会在栈上创建一个新的栈帧，保存局部变量和返回地址
void recursive_depth(int depth) {
    int local_var = depth; // 这个变量在每一层递归中都有独立的存储空间
    printf("递归深度: %d, 局部变量地址: %p\n", depth, (void*)&local_var);
    
    if (depth > 0) {
        recursive_depth(depth - 1);
    }
}

// 4. 静态变量
void counter() {
    // static 变量只初始化一次，并在函数调用之间保持值
    // 它存储在全局数据区，而不是栈上
    static int count = 0;
    count++;
    printf("函数被调用次数: %d\n", count);
}

int main() {
    printf("=== 值传递 vs 指针传递 ===\n");
    int x = 10, y = 20;
    
    swap_by_value(x, y);
    printf("After swap_by_value: x=%d, y=%d (未变)\n", x, y);
    
    swap_by_pointer(&x, &y);
    printf("After swap_by_pointer: x=%d, y=%d (已变)\n", x, y);

    printf("\n=== 栈帧增长演示 (地址通常向低地址增长) ===\n");
    recursive_depth(3);

    printf("\n=== 静态变量演示 ===\n");
    counter();
    counter();
    counter();

    return 0;
}
