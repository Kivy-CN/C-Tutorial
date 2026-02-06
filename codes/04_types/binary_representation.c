/*
 * file: binary_representation.c
 * -----------------------------
 * 这个程序展示了 C 语言中的基本数据类型、大小以及二进制表示。
 * 重点演示了整数的补码表示和浮点数的精度问题。
 *
 * 编译命令:
 *   clang binary_representation.c -o binary_representation
 */

#include <stdio.h>
#include <limits.h> // 包含整数类型的极值定义

// 辅助函数：打印整数的二进制表示
void print_binary(int n) {
    unsigned int mask = 1 << (sizeof(int) * 8 - 1); // 创建最高位的掩码
    printf("Binary of %d: ", n);
    for (int i = 0; i < sizeof(int) * 8; i++) {
        // 检查当前位是否为 1
        if (n & mask) {
            printf("1");
        } else {
            printf("0");
        }
        // 每 4 位打印一个空格，方便阅读
        if ((i + 1) % 4 == 0) printf(" ");
        
        n <<= 1; // 将数值左移一位
    }
    printf("\n");
}

int main() {
    printf("=== 数据类型大小 (Bytes) ===\n");
    printf("char:   %zu\n", sizeof(char));
    printf("short:  %zu\n", sizeof(short));
    printf("int:    %zu\n", sizeof(int));
    printf("long:   %zu\n", sizeof(long));
    printf("float:  %zu\n", sizeof(float));
    printf("double: %zu\n", sizeof(double));
    printf("void*:  %zu (指针大小)\n", sizeof(void*));
    
    printf("\n=== 整数的二进制表示 (补码) ===\n");
    int pos = 5;
    int neg = -5;
    print_binary(pos);
    print_binary(neg);
    // 观察：-5 是 5 的按位取反加 1 (补码)
    
    printf("\n=== 浮点数精度演示 ===\n");
    float f = 0.1f;
    double d = 0.1;
    
    printf("float 0.1  = %.20f\n", f);
    printf("double 0.1 = %.20lf\n", d);
    
    if (f == 0.1) {
        printf("0.1f 等于 0.1 (double常量)\n");
    } else {
        printf("0.1f 不等于 0.1 (double常量) -> 精度丢失导致！\n");
    }

    return 0;
}
