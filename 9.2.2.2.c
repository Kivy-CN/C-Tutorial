// 指针的类型和大小,第二种情况，目标变量是float，用int指针去指向。
#include <stdio.h>
 
int main ()
{
   float  var = 20.0;   /* 实际变量的声明 */
   int  *var_address;        /* 指针变量的声明 */
 
   var_address = &var;  /* 在指针变量中存储 var 的地址 */
 
   printf("var 变量的地址: %p\n", &var  );
 
   /* 在指针变量中存储的地址 */
   printf("var_address变量存储的地址: %p\n", var_address);
 
   /* 使用指针访问值 */
   printf("*var_address变量的值: %d\n", *var_address);
   printf("*var_address变量的值: %f\n", var);
 
   return 0;
}