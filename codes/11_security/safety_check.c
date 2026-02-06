/*
 * file: safety_check.c
 * --------------------
 * 这个程序演示了 C 语言中常见的缓冲区溢出安全漏洞，以及如何防范。
 * 同时介绍了 AddressSanitizer (ASan) 的使用。
 * 
 * 知识点：
 * 1. 缓冲区溢出 (Buffer Overflow) 原理
 * 2. 危险函数 (strcpy) vs 安全函数 (snprintf)
 * 3. 编译时检测工具 (AddressSanitizer)
 *
 * 编译命令 (开启 ASan 检测):
 *   clang -fsanitize=address -g safety_check.c -o safety_check
 */

#include <stdio.h>
#include <string.h>

void unsafe_copy(const char *input) {
    char buffer[10]; // 仅分配 10 字节
    
    printf("\n[Unsafe] 尝试复制: '%s' 到 10 字节 buffer\n", input);
    
    // DANGER: strcpy 不检查目标缓冲区大小
    // 如果 input 长度超过 9 (保留1字节给 \0)，就会发生溢出
    // 可能会覆盖栈上的返回地址，导致程序崩溃或被攻击
    strcpy(buffer, input); 
    
    printf("[Unsafe] 复制成功: %s\n", buffer);
}

void safe_copy(const char *input) {
    char buffer[10];
    
    printf("\n[Safe] 尝试复制: '%s' 到 10 字节 buffer\n", input);
    
    // RECOMMENDED: snprintf 限制写入的最大字节数 (包括结尾的 \0)
    // 即使 input 很长，也只会复制 sizeof(buffer)-1 个字符
    snprintf(buffer, sizeof(buffer), "%s", input);
    
    printf("[Safe] 复制结果: %s\n", buffer);
}

int main() {
    const char *short_str = "Hi";
    const char *long_str = "This string is too long for the buffer";

    // 1. 安全演示
    safe_copy(short_str);
    safe_copy(long_str);

    // 2. 危险演示
    // 注意：如果你开启了 ASan，运行到这里会报错并终止程序
    // 报错信息示例: AddressSanitizer: stack-buffer-overflow ...
    unsafe_copy(short_str); // OK
    
    printf("\n即将执行危险操作 (Buffer Overflow)...\n");
    printf("如果编译时未开启 ASan，程序可能会崩溃或静默破坏内存。\n");
    unsafe_copy(long_str);  // BOOM!

    return 0;
}
