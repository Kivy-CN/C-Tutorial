#include <stdio.h>

int main()
{
    int a = 21;
    int c ;

    // 赋值运算符
    c =  a;
    // 运算符后，c 的值为 21
    printf("Line 1  =  运算符后，c 的值 = %d\n", c );

    // 叠加加法运算符
    c += a;
    // 运算符后，c 的值为 42
    printf("Line 2  += 运算符后，c 的值 = %d\n", c );

    // 叠加减法运算符
    c -= a;
    // 运算符后，c 的值为 21
    printf("Line 3  -= 运算符后，c 的值 = %d\n", c );

    // 叠加乘法运算符
    c *= a;
    // 运算符后，c 的值为 441
    printf("Line 4  *= 运算符后，c 的值 = %d\n", c );

    // 叠加除法运算符
    c /= a;
    // 运算符后，c 的值为 21
    printf("Line 5  /= 运算符后，c 的值 = %d\n", c );

    // 叠加求余运算符
    c = 200;
    c %= a;
    // 运算符后，c 的值为 0
    printf("Line 6  %%= 运算符后，c 的值 = %d\n", c );
}