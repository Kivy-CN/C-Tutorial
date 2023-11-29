#include <stdio.h>
 
int main()
{
   int a = 21;
   int b = 10;
   int c ;
 
   // 加法
   c = a + b;
   printf("Line 1 - c 的值是 %d\n", c );
   // 减法
   c = a - b;
   printf("Line 2 - c 的值是 %d\n", c );
   // 乘法
   c = a * b;
   printf("Line 3 - c 的值是 %d\n", c );
   // 除法
   c = a / b;
   printf("Line 4 - c 的值是 %d\n", c );
   // 求余数
   c = a % b;
   printf("Line 5 - c 的值是 %d\n", c );
   // 先赋值，再加 1
   c = a++;  // 赋值后再加 1 ，c 为 21，a 为 22
   printf("Line 6 - c 的值是 %d a的值是 %d\n", c,a );
   // 先赋值，再减 1
   c = a--;  // 赋值后再减 1 ，c 为 22 ，a 为 21
   printf("Line 7 - c 的值是 %d a的值是 %d\n", c,a );
   // 先加 1，再赋值
   c = ++a;  // 先加 1，再赋值 ，a 原来为 21，a 自己先加一得到22，然后赋值给c，c也就是22了
   printf("Line 8 - c 的值是 %d a的值是 %d\n", c,a );
   // 先减 1，再赋值
   c = --a;  // 先减 1，再赋值 ，a 原来为 22，a 自己先减一得到21，然后赋值给c，c也就是21了
   printf("Line 9 - c 的值是 %d a的值是 %d\n", c,a );
}