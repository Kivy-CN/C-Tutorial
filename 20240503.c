#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int k=2;char c='B';
    do{
        switch(c++)
        {
            case 'A':
                printf("case 'A', k (%d) ", k);
                k++; 
                printf("++ = %d\t", k);
                break;
            case 'B':
                printf("case 'B', k (%d) ", k);
                k--;
                printf("-- = %d\t", k);
                break;
            case 'C':
                printf("case 'C', k (%d) ", k);
                k += 2;
                printf(" + 2 = %d\t", k);
                break;
            case 'D':
                printf("case 'D', k (%d) ", k);
                k = k%2;
                printf("%% 2 = %d\t", k);
                continue;
            case 'E':
                printf("case 'E', k (%d) ", k);
                k *= 2; 
                printf("* 2 = %d\t", k);
                break;
            default:
                printf("default case, k (%d) ", k);
                k = k / 3;
                printf("/3 = %d\t", k);
        }
        printf("k (%d) ", k);
        k++;
        printf("++ = %d\n", k);

    } 
    while (c <= 'F');
    printf("Finally k now %d\n", k);
    return 0;
}