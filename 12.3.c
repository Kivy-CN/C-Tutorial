// 插入排序
#include <stdio.h>
void insertion_sort(int arr[], int len) {
    // 插入排序
    int i, j, key;
    for (i = 1; i < len; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
int main() {
    // 定义一个数组
    int arr[] = { 11, 24, 3, 32, 82, 55, 89, 90, 37, 5, 64, 35, 9, 70 };
    // 计算数组的长度
    int len = (int) sizeof(arr) / sizeof(*arr);
    // 调用插入排序函数
    insertion_sort(arr, len);
    // 打印排序后的数组
    int i;
    for (i = 0; i < len; i++)
        printf("%d ", arr[i]);
    return 0;
}