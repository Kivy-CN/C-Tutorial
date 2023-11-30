// 缓冲区溢出攻击
#include <stdio.h>
#include <string.h>

struct user {
    char name[5];
    char email[10];
};

int main() {
    // 定义一个struct类型的变量u
    struct user u;
    // 打印提示信息，让用户输入名字
    printf("Enter your name: ");
    // 使用gets函数获取用户输入的名字，并赋值给u.name
    gets(u.name);
    // 打印提示信息，让用户输入邮箱
    printf("Enter your email: ");
    // 使用gets函数获取用户输入的邮箱，并赋值给u.email
    gets(u.email);
    // 打印出用户输入的名字和邮箱
    printf("Hello, %s \n", u.name);
    printf("Your email is %s.\n",u.email);
    return 0;
}
