#include <stdio.h>
#include <limits.h>

int main() {
    long long ll_value;
    
    printf("请输入一个整数: ");
    
    // 直接使用scanf读取整数
    int scan_result = scanf("%lld", &ll_value);
    
    // 检查输入是否成功
    if (scan_result != 1) {
        printf("无法存储成整数值\n");
        return 1;
    }
    
    // 检查适合哪种整数类型
    if (ll_value >= SHRT_MIN && ll_value <= SHRT_MAX) {
        short s_value = (short)ll_value;
        printf("类型: short\n");
        printf("内存占用: %d 字节\n", (int)sizeof(short));
        printf("值: %hd\n", s_value);
    } else if (ll_value >= INT_MIN && ll_value <= INT_MAX) {
        int i_value = (int)ll_value;
        printf("类型: int\n");
        printf("内存占用: %d 字节\n", (int)sizeof(int));
        printf("值: %d\n", i_value);
    } else if (ll_value >= LONG_MIN && ll_value <= LONG_MAX) {
        long l_value = (long)ll_value;
        printf("类型: long int\n");
        printf("内存占用: %d 字节\n", (int)sizeof(long));
        printf("值: %ld\n", l_value);
    } else {
        printf("类型: long long int\n");
        printf("内存占用: %d 字节\n", (int)sizeof(long long));
        printf("值: %lld\n", ll_value);
    }
    
    return 0;
}