#include<stdio.h>

// 这是一个很不好的答案，这种答案就是完全按照题意写的，面向考试编程

// 定义联系人结构体
typedef struct contacts {
    char name[11]; // 姓名
    char birthday[11]; // 生日
    char gender; // 性别  注意性别是gender，不是sex，sex是另外的一种含义。。。
    char fixedPhoneNumber[17]; // 固定电话号码 这里改成16就会跟你之前一样报错第二个测试
    char mobilePhoneNumber[17]; // 手机号码 这里改成16就会跟你之前一样报错第二个测试
} Contacts;

int main(void) {
    int N;
    scanf("%d", &N);

    // 联系人信息录入
    Contacts contacts[10]; // 创建联系人数组 这里用了10就是面向测试编程
    for (int i = 0; i < N; i++) {
        scanf("%s %s %c %s %s", contacts[i].name, contacts[i].birthday, &contacts[i].gender, contacts[i].fixedPhoneNumber, contacts[i].mobilePhoneNumber);
    }

    int K;
    scanf("%d", &K);

    // 采集用户想要查询的编号
    int choices[10];
    for (int i = 0; i < K; i++) {
        scanf("%d", &choices[i]);
    }

    // 按题目要求格式输出联系人信息
    for (int i = 0; i < K; i++) {
        if (choices[i] >= N || choices[i] < 0) {
            printf("Not Found\n");
        } else {
            printf("%s %s %s %c %s\n", contacts[choices[i]].name, contacts[choices[i]].fixedPhoneNumber, contacts[choices[i]].mobilePhoneNumber, contacts[choices[i]].gender, contacts[choices[i]].birthday);
        }
    }

    return 0;
}