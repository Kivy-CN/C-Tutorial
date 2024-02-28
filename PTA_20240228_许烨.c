#include<stdio.h>
#include<stdlib.h>

// 定义电话结构体
struct telephone{
    char name[11]; // 姓名
    char sex[11]; // 性别
    char birth[11]; // 出生日期
    char spnum[17]; // 手机号码 你最开始的代码出错很大部分就是这里导致的
    char telnum[17]; // 电话号码 你最开始的代码出错很大部分就是这里导致的
};

int main(){
    int N,i;
    scanf("%d",&N);
    // 动态分配内存空间
    struct telephone* tel = (struct telephone*)malloc(N * sizeof(struct telephone));
    for(i=0;i<N;i++){
        scanf("%s %s %s %s %s", tel[i].name, tel[i].birth, tel[i].sex, tel[i].spnum, tel[i].telnum);
    }
    int K,f;
    scanf("%d",&K);
    for(i=0;i<K;i++){
        scanf("%d",&f);
        if(f<N&&f>=0){
            // 输出符合条件的电话信息
            printf("%s %s %s %s %s\n",tel[f].name,tel[f].spnum,tel[f].telnum,tel[f].sex,tel[f].birth);
        }
        else{
            // 输出未找到信息
            printf("Not Found\n");
        }
    }
    // 释放动态分配的内存空间
    free(tel);
    return 0;
}