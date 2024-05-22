#include <stdio.h>

struct info {
    char subject[20];
    int score;
};

// 冒泡排序
void bubble_sort(struct info arr[], int len) {
    // 定义两个指针，分别指向数组头尾
    int i, j;
    struct info temp;
    // 外层循环，控制比较的轮数
    for (i = 0; i < len - 1; i++)
        // 内层循环，控制每轮比较的次数
        for (j = 0; j < len - 1 - i; j++)
            // 如果前一个数大于后一个数，则交换位置
            if (arr[j].score > arr[j + 1].score ) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

int main() {
    // 定义一个结构体数组，用于存放需要排序的数据
    int N = 3;
    struct info info_arr[N];

    // 输入结构体数据
    for (int i = 0; i < N; i++) {
        printf("请输入科目和分数（例如：Math 90）：");
        scanf("%s %d", info_arr[i].subject, &info_arr[i].score);
    }

    // 对score进行冒泡排序
    bubble_sort(info_arr, N);

    // 打印排序后的结果
    printf("排序后的结果：\n");
    for (int i = 0; i < N; i++) {
        printf("%s %d\n", info_arr[i].subject, info_arr[i].score);
    }

    return 0;
}