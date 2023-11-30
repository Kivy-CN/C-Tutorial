// 字符串定义
#include <stdio.h>
 
int main ()
{
  //Declare a character array of size 6 and assign it to the variable 'words'
   char words[6] = {'H', 'E', 'L', 'L', 'O', '\0'}; 
   //Print the contents of the array to the console
   printf("The Computer Says: %s\n", words);
   //Return 0 to indicate successful execution
   return 0;
}