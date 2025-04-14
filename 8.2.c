#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <errno.h>
#include <math.h>

int main() {
    char input[100];
    char *endptr;
    
    printf("请输入一个数值: ");
    fgets(input, sizeof(input), stdin);
    
    // 移除输入中的换行符
    size_t len = strlen(input);
    if (len > 0 && input[len-1] == '\n') {
        input[len-1] = '\0';
    }
    
    // 检查输入是否包含小数点
    int has_decimal = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '.') {
            has_decimal = 1;
            break;
        }
    }
    
    if (has_decimal) {
        // 尝试转换为浮点数
        errno = 0;
        double value = strtod(input, &endptr);
        
        // 检查转换是否成功
        if (*endptr != '\0' || errno == ERANGE) {
            printf("无法存储成数值\n");
            return 1;
        }
        
        // 检查是否符合float范围
        float f_value = (float)value;
        double diff = fabs(value - (double)f_value);
        double rel_diff = (value != 0) ? diff / fabs(value) : diff;
        
        if (fabs(value) <= FLT_MAX && rel_diff < 1e-6) {
            printf("类型: float\n");
            printf("内存占用: %zu 字节\n", sizeof(float));
            printf("值: %f\n", f_value);
        } else if (fabs(value) <= DBL_MAX) {
            printf("类型: double\n");
            printf("内存占用: %zu 字节\n", sizeof(double));
            printf("值: %lf\n", value);
        } else {
            printf("无法存储成数值\n");
        }
    } else {
        // 尝试转换为整数
        errno = 0;
        long long ll_value = strtoll(input, &endptr, 10);
        
        // 检查转换是否成功
        if (*endptr != '\0' || errno == ERANGE) {
            printf("无法存储成数值\n");
            return 1;
        }
        
        // 检查适合哪种整数类型
        if (ll_value >= SHRT_MIN && ll_value <= SHRT_MAX) {
            short s_value = (short)ll_value;
            printf("类型: short\n");
            printf("内存占用: %zu 字节\n", sizeof(short));
            printf("值: %hd\n", s_value);
        } else if (ll_value >= INT_MIN && ll_value <= INT_MAX) {
            int i_value = (int)ll_value;
            printf("类型: int\n");
            printf("内存占用: %zu 字节\n", sizeof(int));
            printf("值: %d\n", i_value);
        } else if (ll_value >= LONG_MIN && ll_value <= LONG_MAX) {
            long l_value = (long)ll_value;
            printf("类型: long int\n");
            printf("内存占用: %zu 字节\n", sizeof(long));
            printf("值: %ld\n", l_value);
        } else if (ll_value >= LLONG_MIN && ll_value <= LLONG_MAX) {
            printf("类型: long long int\n");
            printf("内存占用: %zu 字节\n", sizeof(long long));
            printf("值: %lld\n", ll_value);
        } else {
            printf("无法存储成数值\n");
        }
    }
    
    return 0;
}