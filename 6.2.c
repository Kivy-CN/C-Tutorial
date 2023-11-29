#include <stdio.h>
#define DIAMETER 10   
#define NEWLINE '\n' 
int main()
{
    //Declare a variable to store the area of circle
    int area;  
    const float PI = 3.141593;
    //Calculate the area of circle using the formula
    area = PI *( DIAMETER /2) * ( DIAMETER /2 );
    //Print the area of circle usingprintf
    printf("value of area : %d", area);
    //Print a new line character
    printf("%c", NEWLINE);
    return 0;
}