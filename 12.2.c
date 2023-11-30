// 选择排序
#include <stdio.h>
void selection_sort(int arr[], int len) {
    // 定义变量i,j,min_idx,temp
    int i, j, min_idx, temp;
    // 外层循环，从0开始，到len-1结束
    for (i = 0; i < len - 1; i++) {
        // 定义最小值索引min_idx
        min_idx = i;
        // 内层循环，从i+1开始，到len结束
        for (j = i + 1; j < len; j++)
            // 如果arr[j]小于arr[min_idx]
            if (arr[j] < arr[min_idx])
                // 更新最小值索引min_idx
                min_idx = j;
        // 交换arr[min_idx]和arr[i]
        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}
int main() {
    // 定义数组arr，初始值为11,24,3,32,82,55,89,90,37,5,64,35,9,70
    int arr[] = { 11, 24, 3, 32, 82, 55, 89, 90, 37, 5, 64, 35, 9, 70 };
    // 计算数组arr的长度
    int len = (int) sizeof(arr) / sizeof(*arr);
    // 调用选择排序函数
    selection_sort(arr, len);
    // 定义变量i
    int i;
    // 打印排序后的数组arr
    for (i = 0; i < len; i++)
        printf("%d ", arr[i]);
    return 0;
}