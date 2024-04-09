#include<stdio.h>

// 定义学生结构体，包含姓名、学号和其他未明确的属性
struct student
{
    char z[20];  // 学生姓名
    int s;  // 学生学号
    int k;  // 其他属性
};

int main()
{
    int i,j,n,m,k;
    scanf("%d\n",&n);  // 读取学生数量

    struct student a[1001];  // 定义学生数组，最多1001个学生

    // 读取每个学生的信息
    for(i=0;i<n;i++)
            scanf("%s %d %d\n",a[i].z,&a[i].s,&a[i].k);

    scanf("%d\n",&m);  // 读取需要查询的学生数量

    // 对于每个需要查询的学生
    for(i=0;i<m;i++)
    {
        scanf("%d",&k);  // 读取需要查询的学生的学号

        // 在所有学生中查找该学号的学生
        for(j=0;j<n;j++)
        if(a[j].s==k)
            printf("%s %d\n",a[j].z,a[j].k);  // 打印找到的学生的姓名和其他属性
    }

    return 0;
}