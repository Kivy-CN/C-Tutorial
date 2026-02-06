/*
 * file: memory_alignment.c
 * ------------------------
 * 这个程序深入探讨了结构体在内存中的布局。
 * 
 * 知识点：
 * 1. 结构体 (Struct) 定义与初始化
 * 2. 内存对齐 (Memory Alignment) 与填充 (Padding)
 * 3. 联合体 (Union) 的共用内存特性
 *
 * 编译命令:
 *   clang memory_alignment.c -o memory_alignment
 */

#include <stdio.h>
#include <stddef.h> // 用于 offsetof 宏

// 简单的结构体
struct Student {
    int id;
    char name[20];
    float score;
};

// 演示内存对齐的结构体
// CPU 为了访问效率，通常要求数据地址是其大小的倍数
struct Aligned {
    char a;     // 1 byte
    // 3 bytes padding (为了让 int 从 4 字节边界开始)
    int b;      // 4 bytes
    char c;     // 1 byte
    // 3 bytes padding (为了让结构体总大小是最大成员 int(4) 的倍数)
} ;

// 紧凑的结构体 (使用编译器属性取消对齐，通常用于网络协议或文件格式)
struct Packed {
    char a;
    int b;
    char c;
} __attribute__((packed));

// 联合体：所有成员共享同一块内存
union Data {
    int i;
    float f;
    char str[4];
};

int main() {
    printf("=== 结构体基础 ===\n");
    struct Student s1 = {1, "Alice", 95.5f};
    printf("ID: %d, Name: %s, Score: %.1f\n", s1.id, s1.name, s1.score);

    printf("\n=== 内存对齐演示 ===\n");
    printf("struct Aligned 大小: %zu bytes\n", sizeof(struct Aligned));
    printf("  Offset of a: %zu\n", offsetof(struct Aligned, a));
    printf("  Offset of b: %zu\n", offsetof(struct Aligned, b));
    printf("  Offset of c: %zu\n", offsetof(struct Aligned, c));
    
    printf("struct Packed 大小:  %zu bytes (1+4+1)\n", sizeof(struct Packed));

    printf("\n=== 联合体 (Union) 演示 ===\n");
    union Data data;
    data.i = 0x41424344; // Hex for 'ABCD' (in little-endian: D C B A)
    
    printf("data.i (hex): %X\n", data.i);
    printf("data.f: %f (解释为 float)\n", data.f);
    // 注意：x86 是小端序，低位字节在低地址
    printf("data.str: %c %c %c %c\n", data.str[0], data.str[1], data.str[2], data.str[3]);

    return 0;
}
