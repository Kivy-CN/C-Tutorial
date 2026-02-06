/*
 * file: branch_prediction.c
 * -------------------------
 * 这个程序展示了 C 语言的流程控制结构，并介绍了一个高级概念：分支预测优化。
 * 
 * 知识点：
 * 1. 基本的 if-else 和 switch-case
 * 2. 循环结构 (for, while)
 * 3. 编译器分支预测提示 (likely/unlikely)
 *
 * 编译命令:
 *   clang branch_prediction.c -o branch_prediction
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 宏定义：告诉编译器某个分支发生的概率很大或很小
// 这有助于编译器生成更优化的汇编代码（调整指令顺序）
#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

void basic_flow_control() {
    printf("=== 基本流程控制 ===\n");
    int score = 85;

    // if-else
    if (score >= 90) {
        printf("成绩: A\n");
    } else if (score >= 80) {
        printf("成绩: B\n");
    } else {
        printf("成绩: C\n");
    }

    // switch-case
    char grade = 'B';
    switch (grade) {
        case 'A': printf("优秀\n"); break;
        case 'B': printf("良好\n"); break;
        default:  printf("未知\n"); break;
    }

    // while loop
    int i = 0;
    while (i < 3) {
        printf("Count: %d\n", i++);
    }
}

void branch_prediction_demo() {
    printf("\n=== 分支预测提示 Demo ===\n");
    printf("这个例子展示了如何告诉编译器哪个分支更有可能执行。\n");
    
    srand(time(NULL));
    int random_val = rand() % 100;

    // 假设我们在处理正常业务，错误情况很少发生
    // 使用 unlikely 标记错误分支
    if (unlikely(random_val < 5)) {
        // 只有 5% 的概率进入这里
        printf("发生了罕见的错误 (Value: %d)\n", random_val);
    } else {
        // 95% 的概率进入这里
        // 编译器会把这部分代码紧接在判断指令之后，减少跳转开销
        printf("系统运行正常 (Value: %d)\n", random_val);
    }
}

int main() {
    basic_flow_control();
    branch_prediction_demo();
    return 0;
}
