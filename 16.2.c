// 数组越界赋值
#include <stdio.h>

struct my_struct {
    int arr1[5];
    int arr2[5];
};

int main() {
    // 定义一个结构体变量s，其中arr1和arr2分别是一个长度为5的数组
    struct my_struct s = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}};
    int i;
    // 将arr1中的每一个元素都置为0
    for (i = 0; i <= 5; i++) {
        s.arr1[i] = 0;
    }
    // 遍历arr1，打印每一个元素
    for (i = 0; i < 5; i++) {
        printf("%d ", s.arr1[i]);
    }
    printf("\n");
    // 遍历arr2，打印每一个元素
    for (i = 0; i < 5; i++) {
        printf("%d ", s.arr2[i]);
    }
    return 0;
}