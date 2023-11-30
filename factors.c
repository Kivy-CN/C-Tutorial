// 首先，我们需要创建一个C语言函数并将其编译为共享对象（.so）文件。
// 然后，我们可以在Python中使用`ctypes`库来调用这个.so文件。
// 以下是一个示例：
// 首先，我们创建一个名为`factors.c`的C文件，内容如下：


#include <stdio.h>

void print_factors(int num) {
    int i;
    for(i = 1; i <= num; ++i) {
        if (num % i == 0) {
            printf("%d ", i);
        }
    }
}



// 然后，我们可以使用以下命令将其编译为.so文件：

// ```bash
// gcc -shared -o factors.so factors.c
// ```