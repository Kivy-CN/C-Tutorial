#include <stdio.h> // 预处理命令，包含一下 stdio.h 文件，用<>就表明从系统库中寻找头文件
#include "tools.h" // 预处理命令，包含一下 tools.h 文件，用""就表明从当前目录寻找头文件
int main() // 函数的声明，告诉编译器有一个名字叫做main的函数，接收0个参数，返回int类型
{ // 函数的定义，告诉编译器这个函数内部的具体运算过程
    /* 在终端中输出 Hello World */
    //Prints the string "Hello, World!" to the console
    printf("Hello, World! \n");  // 打印输出对应文字
    return 0; // 返回一个int类型的值，0表示成功
}