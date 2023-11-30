// 归并排序
#include <stdio.h>
void merge(int arr[], int l, int m, int r) {
    // 定义三个指针，分别指向左右两个数组
    int i, j, k;
    // 计算左右数组的长度
    int n1 = m - l + 1;
    int n2 = r - m;
    // 定义两个临时数组，用来存储左右数组
    int L[n1], R[n2];
    // 将左右数组的值分别存入临时数组中
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    // 定义三个指针，分别指向临时数组的三个位置
    i = 0;
    j = 0;
    k = l;
    // 比较左右数组的值，将较小的值存入arr数组中
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    // 将左数组剩余的值存入arr数组中
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    // 将右数组剩余的值存入arr数组中
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void merge_sort(int arr[], int l, int r) {
    // 如果左数组的值小于右数组的值，则进行归并排序
    if (l < r) {
        // 计算中间值
        int m = l + (r - l) / 2;
        // 递归调用归并排序，对左数组进行排序
        merge_sort(arr, l, m);
        // 递归调用归并排序，对右数组进行排序
        merge_sort(arr, m + 1, r);
        // 将左右数组进行归并
        merge(arr, l, m, r);
    }
}
int main() {
    // 定义一个数组，用来存储输入的值
    int arr[] = { 11, 24, 3, 32, 82, 55, 89, 90, 37, 5, 64, 35, 9, 70 };
    // 计算数组的长度
    int len = (int) sizeof(arr) / sizeof(*arr);
    // 调用归并排序函数，对数组进行排序
    merge_sort(arr, 0, len - 1);
    // 定义一个指针，用来指向数组中的每一个值
    int i;
    // 遍历数组，输出每一个值
    for (i = 0; i < len; i++)
        printf("%d ", arr[i]);
    return 0;
}