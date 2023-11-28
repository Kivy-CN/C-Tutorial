# C语言程序设计

# 1 基础知识

## 1.1 什么是程序设计语言？

在没有大语言模型以前，计算机无法理解人类语言。
人类要控制计算机做出某些运算，就要用机器语言。
最开始的机器语言是纸片打孔形式的，
后来有了汇编语言，用助记符代替机器指令。
然后，又有了更高级的程序设计语言，提高了抽象层次。
高级语言比机器语言抽象层次更高，更接近人类语言，有C、C++、Java、Python等。

下面是一个简单的汇编程序，它将两个数相加并将结果存储在第一个数中：

```ASM
section .data
    // 定义变量num1，类型为双字，值为10
    num1 dd 10
    // 定义变量num2，类型为双字，值为20
    num2 dd 20

section .text
    // 定义全局变量_start
    global _start

_start:
    // 将num1的值赋给eax
    mov eax, [num1]
    // 将num2的值加到eax上
    add eax, [num2]
    // 将eax的值赋给num1
    mov [num1], eax
    // 将eax的值赋为1
    mov eax, 1
    // 将ebx的值赋为0
    xor ebx, ebx
    // 调用int 0x80，执行系统调用
    int 0x80
```

上面的汇编代码将 num1 和 num2 两个数相加，并将结果存储在 num1 中。这个程序使用 Linux 系统调用来退出程序.
该过程的 C 语言版本：

```C
#include <stdio.h>

int main() {
    int num1 = 10;
    int num2 = 20;
    num1 += num2;
    printf("%d\n", num1);
    return 0;
}
```

上面的C语言代码将 num1 和 num2 两个数相加，并将结果存储在 num1 中。这个程序使用 printf 函数来输出结果。
再改写成Python代码如下：

```Python
num1 = 10
num2 = 20
num1 += num2
print(num1)
```

抽象层次越来越高，代码复杂度越来越低，人类阅读理解和编写也都越来越简洁。

但为什么不直接学Python，还是要学一下C语言呢？

* Python语法简单易学，适合快速开发原型和小型项目；有很多强大的库和框架，可以快速实现各种功能。
* C语言可以直接访问计算机的硬件资源，可实现高效代码，用于系统编程、嵌入式系统和操作系统等领域。

各有各的好处，先都学着了解一下，后续根据需求自行深入探索。

## 1.2 程序开发的步骤


这部分的英语单词需要熟悉，可能以后要常常用到。
|单词|含义|解释|
|---|---|---|
|Analysis|分析|程序的用途|
|Design|设计|如何来实现|
|Edit|编辑|具体写代码|
|Compile|编译|编译到目标文件|
|Link|链接|生成可执行文件|
|Run|运行|运行可执行文件|
|Debug|调试|修改错误重来|

Compile 和 Link 这两步骤是针对不同操作系统平台的，生成对应的目标文件和可执行文件。
其他步骤都是跨平台的。
也就是说，同样的一份 C 语言代码，可以在 Windows、Linux、MacOS 平台上编译运行。
代码是完全相同的情况下，不同操作系统上编译出来的目标文件、链接出来的可执行文件各自不同。

### 1.2.1 需求分析
需求分析是程序开发的第一步，也是最重要的一步。
需求分析的目的是得到软件开发的目标，并形成文档。
要写什么样的程序，要做啥事情。

### 1.2.2 设计
设计是程序开发的中间阶段，也是最重要的阶段。
设计是程序开发的关键，设计的好坏直接影响程序的性能和开发周期。
怎么去做到，如何来实现。

### 1.2.3 编码
编码是程序开发的最核心阶段，也是最耗时和最困难的一步。
编码阶段，需要程序员对程序进行编码，包括程序的编写和测试。
按照设计一步步编写代码，从人类语言转化为程序设计语言。

### 1.3.4 编译、链接、运行、调试。
编译器读取源代码，编译出来目标文件，再由链接器链接成可执行文件。
可执行文件就能拿来运行，如果有错误就进行修改，这个过程教易出错，需要调试。


## 1.3 程序运行的过程

程序运行有很多种方式。

### 按照运行方式：

* 编译型语言，是先翻译成机器语言，再由机器执行。C、C++，Swift，Go
* 解释型语言，是先翻译成机器语言，再由机器逐行解释执行。Python、JavaScript
* 混合型语言，将源代码转换为机器代码，然后在一个环境中执行机器代码。C#，Java，Scala，Kotlin

C语言是编译型语言。

## 1.4 C语言的特性

### 1.4.1 访问范围广：

* 可访问物理内存的语言：C、C++、Rust
* 只可访问堆的语言：C#、JavaScript
* 只可访问栈的语言：Java、Python

堆和栈都是计算机内存的一部分。
堆的分配和释放需要由开发者手动完成。
栈的分配和释放是由编译器自动完成的。

能访问物理内存的语言，适合操作系统以及驱动程序的开发。
这些任务 Python 很难胜任。

## 1.4.2 运行速度快：

* 静态类型语言：变量的类型必须在编译时确定，先声明，后使用；
* 动态类型语言：变量的类型可以在运行时确定，随时用，可更改。

C语言是静态类型语言，速度快。
Python是动态类型语言，速度慢。

## 1.4.3 跨平台性：

C语言被当今几乎所有主流操作系统所支持；
C语言编写的程序基本可以运行在任何操作系统上。

# 2 代码上手

第一个程序，一般都是 Hello World。
```C
#include <stdio.h>
int main()
{
    /* 在终端中输出 Hello World */
    //Prints the string "Hello, World!" to the console
    printf("Hello, World! \n"); 
    return 0;
}
```



下是一个更复杂的例子，它将使用C语言和Python计算斐波那契数列的前100个数字：

C语言代码：

```C
#include <stdio.h>
#include <time.h>

int main() {
    int n = 100, i, t1 = 0, t2 = 1, nextTerm;
    printf("Fibonacci Series: ");

    clock_t start = clock();
    for (i = 1; i <= n; ++i) {
        printf("%d, ", t1);
        nextTerm = t1 + t2;
        t1 = t2;
        t2 = nextTerm;
    }
    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nTime taken: %f seconds\n", time_spent);

    return 0;
}
```

Python代码：

```Python
import time

n = 100
t1, t2 = 0, 1
print("Fibonacci Series: ", end=" ")
start = time.time()
for i in range(n):
    print(t1, end=" ")
    nextTerm = t1 + t2
    t1 = t2
    t2 = nextTerm
end = time.time()

time_spent = end - start
print("\nTime taken: ", time_spent, " seconds")
```

这两个程序都计算斐波那契数列的前100个数字。
C语言程序的执行速度通常比Python程序快得多。
C语言程序使用了`<time.h>`库中的`clock()`函数来测量程序的执行时间。
Python程序使用了`time`库中的`time()`函数来测量程序的执行时间。
`time_spent`变量来存储程序的执行时间，并在程序结束时打印出来。


