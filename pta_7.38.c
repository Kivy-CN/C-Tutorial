#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <string.h>
/*
给定某数字A（1≤A≤9）以及非负整数N（0≤N≤100000），求数列之和S=A+AA+AAA+⋯+AA⋯A（N个A）。
例如A=1, N=3时，S=1+11+111=123。
输入数字A与非负整数N。
输出格式

*/

int  main()
{
    int p[100002] = {0};
    int a,n;
    int i,j;
    int t,fd=0; //中间转换变量 ，之前进位的数

    scanf("%d %d",&a,&n);
    if ( n==0 ){
        printf("0\n");
        return 0;
    }
    j = 0;
    for( i=n; i>0; i--,j++){
        t = i*a + fd;
        fd = t/10;
        p[j] = t%10;
    }
    if( fd!=0 ){
        printf("%d",fd);
    }
    for( i=j-1; i>=0; i--){
        printf("%d",p[i]);
    }
    return 0;
}