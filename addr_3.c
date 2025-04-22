// 代码3  通过指针修改变量值
#include <stdio.h>

int main() {
    int x = 10;
    int y = 20;
    int *p = &x;  // p指向x   
    printf("初始值: x = %d, y = %d\n", x, y);   
    *p = 30;      // 修改x的值为30
    printf("修改后: x = %d, y = %d\n", x, y);   
    p = &y;       // p现在指向y
    *p = 40;      // 修改y的值为40
    printf("再次修改: x = %d, y = %d\n", x, y);   
    return 0;
}