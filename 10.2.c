// 共用体只允许一个数据成员有值
#include <stdio.h>
#include <string.h>
 
union Data
{
   int i;
   float f;
   char  str[20];
};
 
int main( )
{
   union Data data;        
 
   // Assign the value 10 to the integer variable i
   data.i = 10;
   // Print the value of the integer variable i
   printf( "data.i : %d\n", data.i);
   
   // Assign the value 220.5 to the float variable f
   data.f = 220.5;
   // Print the value of the float variable f
   printf( "data.f : %f\n", data.f);
   
   // Copy the string "C Programming" into the character array str
   strcpy( data.str, "C Programming");
   // Print the value of the integer variable i
   printf( "data.i : %d\n", data.i);
   // Print the value of the float variable f
   printf( "data.f : %f\n", data.f);
   // Print the value of the character array str
   printf( "data.str : %s\n", data.str);
 
   return 0;
}