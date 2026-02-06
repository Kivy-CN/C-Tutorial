/*
 * file: hello_world.c
 * -------------------
 * 这个程序展示了 C 语言程序的基本结构。
 * 包含：头文件引入、主函数入口、参数传递、标准输出和返回值。
 *
 * 编译命令:
 *   clang hello_world.c -o hello_world
 */

#include <stdio.h>  // 引入标准输入输出库，用于使用 printf 函数
#include <stdlib.h> // 引入标准库，用于使用 exit 等函数 (本例虽未直接使用，但是常用习惯)

/*
 * main 函数: 程序的入口点
 * -----------------------
 * int argc:     Arguments Count，命令行参数的个数 (程序本身算 1 个)
 * char *argv[]: Arguments Vector，命令行参数的字符串数组
 */
int main(int argc, char *argv[]) {
    // 打印问候语到标准输出 (stdout)
    // \n 是换行符
    printf("Hello, Clang World!\n");

    // 打印命令行参数信息
    printf("程序名称: %s\n", argv[0]);
    if (argc > 1) {
        printf("传入了 %d 个额外参数:\n", argc - 1);
        for (int i = 1; i < argc; i++) {
            printf("  参数 %d: %s\n", i, argv[i]);
        }
    } else {
        printf("没有传入额外参数。\n");
    }

    // 返回 0 给操作系统，表示程序正常结束
    // 非 0 值通常表示发生了错误
    return 0;
}
