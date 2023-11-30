// 冒泡排序
#include <stdio.h>
void bubble_sort(int arr[], int len) {
    // 定义两个指针，分别指向数组头尾
    int i, j, temp;
    // 外层循环，控制比较的轮数
    for (i = 0; i < len - 1; i++)
        // 内层循环，控制每轮比较的次数
        for (j = 0; j < len - 1 - i; j++)
            // 如果前一个数大于后一个数，则交换位置
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}
int main() {
    // 定义一个数组，用于存放需要排序的数字
    int arr[] = { 11, 24, 3, 32, 82, 55, 89, 90, 37, 5, 64, 35, 9, 70 };
    // 计算数组的长度
    int len = (int) sizeof(arr) / sizeof(*arr);
    // 调用冒泡排序函数，对数组进行排序
    bubble_sort(arr, len);
    // 定义一个指针，用于指向数组
    int i;
    // 遍历数组，输出排序后的结果
    for (i = 0; i < len; i++)
        printf("%d ", arr[i]);
    return 0;
}