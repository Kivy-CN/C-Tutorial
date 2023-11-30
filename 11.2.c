// 引用方式传递，数值变化在函数内部，也在外部
#include <stdio.h>
 
/* 函数声明 */
int swap(int *x, int *y);

/* 函数定义 */
int swap(int *x, int *y)
{
   int temp;

   temp = *x; /* 保存 x 的值 */
   *x = *y;    /* 把 y 赋值给 x */
   *y = temp; /* 把 temp 赋值给 y */

   
   printf("函数内，*x 的值： %d\n", *x );
   printf("函数内，*y 的值： %d\n", *y );
  
   return 0 ;
}
 
int main ()
{
   /* 局部变量定义 */
   int a = 100;
   int b = 200;
 
   printf("交换前，a 的值： %d\n", a );
   printf("交换前，b 的值： %d\n", b );
 
   /* 调用函数来交换值 */
   swap(&a,& b);
 
   printf("交换后，a 的值： %d\n", a );
   printf("交换后，b 的值： %d\n", b );
 
   return 0;
}