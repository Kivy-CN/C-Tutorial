#include <stdio.h>

// 定义Student结构体
struct Student {
    int id;        // 学号
    char name[51]; // 姓名，假设不超过50个字符
};

int main() {
    // 创建Student类型的变量
    struct Student student;

    // 输入学号和姓名
    printf("请输入学号：");
    scanf("%d", &student.id);
    printf("请输入姓名：");
    scanf("%s", student.name); // 注意：这里使用%s仅能读取一个单词，即遇到空格会停止

    // 打印学号和姓名
    printf("学号：%d\n姓名：%s\n", student.id, student.name);

    return 0;
}




