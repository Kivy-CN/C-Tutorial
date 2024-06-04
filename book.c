#include <stdio.h>

// 定义Book结构体
struct Book {
    int book_id;        // 书号
    char title[101];    // 书名，假设不超过100个字符
    float price;        // 价格
};
int main() {
    // 创建Book类型的变量
    struct Book book;

    // 输入书号、书名和价格
    printf("请输入书号：");
    scanf("%d", &book.book_id);
    printf("请输入书名：");
    scanf("%s", book.title); // 注意：这里使用%s仅能读取一个单词，即遇到空格会停止
    printf("请输入价格：");
    scanf("%f", &book.price);

    // 打印书号、书名和价格
    printf("书号：%d\n书名：%s\n价格：%.2f\n", book.book_id, book.title, book.price);

    return 0;
}



