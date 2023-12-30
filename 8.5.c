#include <stdio.h>
#include <time.h>

#define N 100000000

int main() {
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    for(int i = 0; i < N; i++) {
        int result = 2 * i + 3; // Example computation
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time used in normal loop: %f\n", cpu_time_used);

    start = clock();
    for(int i = 0; i < N; i+=4) {
        int result1 = 2 * i + 3; // Example computation
        int result2 = 2 * (i + 1) + 3; // Example computation
        int result3 = 2 * (i + 2) + 3; // Example computation
        int result4 = 2 * (i + 3) + 3; // Example computation
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time used in unrolled loop: %f\n", cpu_time_used);

    return 0;
}