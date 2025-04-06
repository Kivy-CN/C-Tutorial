/**
 * @file constants_example.c
 * @brief 演示C语言中常量定义的不同方式及其区别
 * 
 * 本程序展示了使用 #define 和 const 关键字定义常量的不同特性，
 * 并通过实例说明它们在类型检查、内存使用和作用域等方面的区别。
 */

#include <stdio.h>

/**
 * 使用预处理指令 #define 定义的符号常量
 * 特点：
 * 1. 在预处理阶段进行简单的文本替换
 * 2. 没有类型信息
 * 3. 没有内存分配
 * 4. 作用域从定义处开始到文件结尾
 */
#define PI 3.14159
#define MAX_ARRAY_SIZE 100
#define ERROR_CODE -1

/**
 * 使用 const 关键字定义的变量常量
 * 特点：
 * 1. 是真正的变量，有类型信息
 * 2. 编译器会进行类型检查
 * 3. 会分配内存
 * 4. 遵循普通变量的作用域规则
 */

int main() {
    /**
     * @var const double E
     * 自然对数的底数，使用 const 定义的常量
     */
    const double E = 2.71828;
    
    /**
     * @var const int MAX_USERS
     * 系统支持的最大用户数，使用 const 定义的整型常量
     */
    const int MAX_USERS = 50;
    
    printf("常量演示:\n");
    printf("PI = %f (使用 #define 定义)\n", PI);
    printf("E = %f (使用 const 定义)\n", E);
    printf("MAX_ARRAY_SIZE = %d (使用 #define 定义)\n", MAX_ARRAY_SIZE);
    printf("MAX_USERS = %d (使用 const 定义)\n", MAX_USERS);
    
    /**
     * @var int numbers
     * 存储整数的数组，大小由常量决定
     */
    int numbers[MAX_ARRAY_SIZE]; // 使用 #define 定义的常量作为数组大小
    
    /**
     * @var char usernames
     * 存储用户名的二维数组，大小由常量决定
     */
    char usernames[MAX_USERS][50]; // 使用 const 定义的常量作为数组大小
    
    /**
     * @var const char* ERROR_MESSAGE
     * 错误信息字符串常量
     */
    const char* ERROR_MESSAGE = "操作失败";
    
    // 以下代码将导致编译错误，因为不能修改 const 变量
    // E = 3.0; // 错误：不能修改 const 变量
    
    // 而 #define 定义的常量没有类型检查
    printf("\n#define 和 const 的区别演示:\n");
    
    /**
     * @var const double* ptrToConst
     * 指向常量的指针
     */
    const double* ptrToConst = &E;
    printf("指向 const 变量的指针: %f\n", *ptrToConst);
    
    // *ptrToConst = 3.0; // 错误：不能通过指针修改 const 变量
    
    /**
     * @var int errorCode
     * 使用 #define 定义的错误代码
     */
    int errorCode = ERROR_CODE;
    printf("错误代码: %d (使用 #define 定义)\n", errorCode);
    
    return 0;
}