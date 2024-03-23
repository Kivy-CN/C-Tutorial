#include <stdio.h>

// 全局变量声明，生命周期从声明开始到程序结束
int globalVar = 10;

void modifyVariables() {
    // 尝试修改全局变量
    globalVar = 30;
    printf("在函数内部修改后的全局变量值: %d\n", globalVar);

    // 尝试修改局部变量
    int localVar = 20;
    localVar = 40;
    printf("在函数内部修改后的主函数内局部变量值: %d\n", localVar);
}

int main() {
    // 局部变量定义，生命周期从声明开始到函数结束
    int localVar = 20;

    // 访问全局变量
    printf("全局变量初始值: %d\n", globalVar);

    // 访问局部变量
    printf("主函数内局部变量初始值: %d\n", localVar);

    // 调用函数，尝试修改全局变量和局部变量的值
    modifyVariables();

    // 再次访问全局变量和局部变量，查看它们的值是否已被修改
    printf("函数调用后的全局变量值: %d\n", globalVar);
    printf("函数调用后的主函数内局部变量值: %d\n", localVar);

    return 0;
}