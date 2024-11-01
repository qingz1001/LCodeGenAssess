#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_N 1500
#define MAX_SOLUTIONS 1000000

typedef unsigned __int128 uint128_t;

char input[MAX_N + 1];
char output[MAX_SOLUTIONS][MAX_N + 1];
int n, solution_count = 0;

uint128_t binary_value(const char* str) {
    uint128_t value = 0;
    for (int i = 0; i < n; i++) {
        value = (value << 1) | (str[i] - '0');
    }
    return value;
}

double calculate_variance(const char* str) {
    double sum = 0, sum_sq = 0;
    uint128_t values[MAX_N + 1];
    
    for (int i = 0; i <= n; i++) {
        values[i] = binary_value(str + i);
        sum += values[i];
        sum_sq += (double)values[i] * values[i];
    }
    
    double mean = sum / (n + 1);
    return (sum_sq / (n + 1)) - (mean * mean);
}

int compare(const void* a, const void* b) {
    return memcmp(a, b, n);
}

void generate_solutions(int index, char* current) {
    if (index == n) {
        char full_str[2 * MAX_N + 1];
        strcpy(full_str, input);
        strcat(full_str, current);
        
        static double min_variance = 1e100;
        double variance = calculate_variance(full_str);
        
        if (fabs(variance - min_variance) < 1e-9) {
            strcpy(output[solution_count++], current);
        } else if (variance < min_variance) {
            min_variance = variance;
            solution_count = 0;
            strcpy(output[solution_count++], current);
        }
        return;
    }
    
    current[index] = '0';
    generate_solutions(index + 1, current);
    current[index] = '1';
    generate_solutions(index + 1, current);
}

int main() {
    scanf("%s", input);
    n = strlen(input);
    
    char current[MAX_N + 1] = {0};
    generate_solutions(0, current);
    
    qsort(output, solution_count, sizeof(output[0]), compare);
    
    for (int i = 0; i < solution_count; i++) {
        printf("%s\n", output[i]);
    }
    
    return 0;
}