// 用指针指向已有变量，然后输出地址
#include <stdio.h>
 
int main ()
{
   int var_a = 10; // 定义一个变量
   int *p;              // 定义指针变量，注意这里的类型要和所指目标一致，确定指针长度用
   p = &var_a;     // 建立指向关系，实际上就是将 var_a 在内存中的地址赋值给 p
   printf("var_a 变量的地址： %p\n", p);
   return 0;
}