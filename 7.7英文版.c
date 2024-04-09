#include <stdio.h>
#include <time.h>

/**
 * Calculates the time difference between two clock ticks.
 * 
 * @param start The starting clock tick.
 * @param end The ending clock tick.
 * @return The time difference in seconds.
 */
double calculate_time(clock_t start, clock_t end) {
    double diff = ((double)end - start) / CLOCKS_PER_SEC;
    return diff;
}

/**
 * Performs addition operation up to a given number.
 * 
 * @param n The number up to which addition is performed.
 */
void add_operation(int n) {
    int result = 0;
    for(int i = 0; i < n; i++) {
        result += i;
    }
}

/**
 * Performs subtraction operation up to a given number.
 * 
 * @param n The number up to which subtraction is performed.
 */
void subtract_operation(int n) {
    int result = 0;
    for(int i = 0; i < n; i++) {
        result -= i;
    }
}

/**
 * Performs multiplication operation up to a given number.
 * 
 * @param n The number up to which multiplication is performed.
 */
void multiply_operation(int n) {
    int result = 1;
    for(int i = 1; i <= n; i++) {
        result *= i;
    }
}

/**
 * Performs division operation up to a given number.
 * 
 * @param n The number up to which division is performed.
 */
void divide_operation(int n) {
    double result = 1.0;
    for(int i = 1; i <= n; i++) {
        result /= i;
    }
}

/**
 * Performs increment operation up to a given number.
 * 
 * @param n The number up to which increment is performed.
 */
void increment_operation(int n) {
    int result = 0;
    for(int i = 0; i < n; i++) {
        result++;
    }
}

/**
 * Performs decrement operation up to a given number.
 * 
 * @param n The number up to which decrement is performed.
 */
void decrement_operation(int n) {
    int result = 0;
    for(int i = 0; i < n; i++) {
        result--;
    }
}

/**
 * Performs modulus operation up to a given number.
 * 
 * @param n The number up to which modulus is performed.
 */
void modulus_operation(int n) {
    int result = n;
    for(int i = 1; i < n; i++) {
        result = result % i;
    }
}

/**
 * Performs address operation up to a given number.
 * 
 * @param n The number up to which address is taken.
 */
void address_operation(int n) {
    int* result = &n;
    for(int i = 0; i < n; i++) {
        result = &i;
    }
}

int main() {
    int n = 100000000; // Number of operations

    printf("Number of operations: %d\n", n);

    clock_t start, end;

    start = clock();
    add_operation(n);
    end = clock();
    printf("Addition operation time: %f\n", calculate_time(start, end));

    start = clock();
    subtract_operation(n);
    end = clock();
    printf("Subtraction operation time: %f\n", calculate_time(start, end));

    start = clock();
    multiply_operation(n);
    end = clock();
    printf("Multiplication operation time: %f\n", calculate_time(start, end));

    start = clock();
    divide_operation(n);
    end = clock();
    printf("Division operation time: %f\n", calculate_time(start, end));

    start = clock();
    increment_operation(n);
    end = clock();
    printf("Increment operation time: %f\n", calculate_time(start, end));

    start = clock();
    decrement_operation(n);
    end = clock();
    printf("Decrement operation time: %f\n", calculate_time(start, end));

    start = clock();
    modulus_operation(n);
    end = clock();
    printf("Modulus operation time: %f\n", calculate_time(start, end));

    start = clock();
    address_operation(n);
    end = clock();
    printf("Address operation time: %f\n", calculate_time(start, end));

    return 0;
}