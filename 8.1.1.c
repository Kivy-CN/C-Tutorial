// if
#include <stdio.h>
 
int main ()
{
   /* 局部变量定义 */
   int a = 10;
   scanf("%d", &a); // 读取用户输入的整数值

   if(a > 2147483647) // 检查输入值是否超过 int 的最大值
   {
       printf("溢出了，请重新输入\n");
       return 1; // 返回错误代码
   }
   
   /* 如果输入值在范围内，则继续执行 */
 
   /* 使用 if 语句检查布尔条件 */
   if( a < 20 )
   {
       /* 如果条件为真，则输出下面的语句 */
       printf("a 小于 20\n" );
   }
   printf("a 的值是 %d\n", a);
 
   return 0;
}