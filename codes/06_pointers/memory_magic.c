/*
 * file: memory_magic.c
 * --------------------
 * 这个程序涵盖了 C 语言最核心也最危险的部分：指针与内存管理。
 * 
 * 知识点：
 * 1. 指针的基本操作 (*, &)
 * 2. 指针与数组的关系
 * 3. 动态内存分配 (malloc, free)
 * 4. 常见的内存错误 (演示)
 *
 * 编译命令:
 *   clang memory_magic.c -o memory_magic
 */

#include <stdio.h>
#include <stdlib.h>

void pointer_basics() {
    printf("=== 指针基础 ===\n");
    int a = 10;
    int *p = &a; // p 存储了 a 的地址

    printf("a 的值: %d\n", a);
    printf("a 的地址: %p\n", (void*)&a);
    printf("p 的值 (即 a 的地址): %p\n", (void*)p);
    printf("通过 p 访问 a (*p): %d\n", *p);

    *p = 20; // 修改 *p 等同于修改 a
    printf("修改 *p 后 a 的值: %d\n", a);
}

void array_and_pointer() {
    printf("\n=== 数组与指针 ===\n");
    int arr[3] = {100, 200, 300};
    int *ptr = arr; // 数组名本身就是指向首元素的指针

    for (int i = 0; i < 3; i++) {
        // *(ptr + i) 等价于 arr[i]
        printf("arr[%d] = %d, *(ptr + %d) = %d\n", i, arr[i], i, *(ptr + i));
    }
}

void dynamic_memory() {
    printf("\n=== 动态内存分配 ===\n");
    int n = 5;
    // 在堆(Heap)上申请内存
    int *dynamic_arr = (int*)malloc(n * sizeof(int));
    
    if (dynamic_arr == NULL) {
        fprintf(stderr, "内存分配失败！\n");
        return;
    }

    // 使用动态数组
    for (int i = 0; i < n; i++) {
        dynamic_arr[i] = i * 10;
    }

    printf("动态数组内容: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", dynamic_arr[i]);
    }
    printf("\n");

    // 重要：使用完毕必须释放内存，否则会导致内存泄漏
    free(dynamic_arr);
    
    // 释放后，dynamic_arr 变成了 "悬空指针" (Dangling Pointer)
    // 为了安全，通常将其置为 NULL
    dynamic_arr = NULL; 
    printf("内存已释放。\n");
}

int main() {
    pointer_basics();
    array_and_pointer();
    dynamic_memory();
    return 0;
}
