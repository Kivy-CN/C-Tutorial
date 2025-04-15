#include <stdio.h>
#include <limits.h>

int main() {
    int a;
    
    printf("请输入一个整数: ");
    
    // 直接使用scanf读取整数
    scanf("%d", &a);
    
    // 检查适合哪种整数类型
    if (a >= SHRT_MIN && a <= SHRT_MAX) {
        short s_value = (short)a;
        printf("类型: short\n");
        printf("内存占用: %d 字节\n", (int)sizeof(short));
        printf("值: %hd\n", s_value);
    } else if (a >= INT_MIN && a <= INT_MAX) {
        int i_value = (int)a;
        printf("类型: int\n");
        printf("内存占用: %d 字节\n", (int)sizeof(int));
        printf("值: %d\n", i_value);
    } 
    
    return 0;
}