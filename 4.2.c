#include <stdio.h> 
int main()
{
   printf("当前平台 int 类型的大小是 : %lu \n", sizeof(int));   
   printf("当前平台 char 类型的大小是 : %lu \n", sizeof(char));
   printf("当前平台 short 类型的大小是 : %lu \n", sizeof(short));
   printf("当前平台 long 类型的大小是 : %lu \n", sizeof(long));
   printf("当前平台 float 类型的大小是 : %lu \n", sizeof(float));
   printf("当前平台 double 类型的大小是 : %lu \n", sizeof(double));
   return 0;
}