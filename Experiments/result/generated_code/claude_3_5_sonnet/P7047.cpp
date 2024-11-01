#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_N 1501

char input[MAX_N];
char output[MAX_N];
int n;

typedef unsigned __int128 uint128_t;

uint128_t binary_to_decimal(char *s, int len) {
    uint128_t result = 0;
    for (int i = 0; i < len; i++) {
        result = (result << 1) | (s[i] - '0');
    }
    return result;
}

double calculate_variance(uint128_t *values, int count) {
    double sum = 0, mean, variance = 0;
    for (int i = 0; i < count; i++) {
        sum += (double)values[i];
    }
    mean = sum / count;
    
    for (int i = 0; i < count; i++) {
        double diff = (double)values[i] - mean;
        variance += diff * diff;
    }
    return variance / count;
}

int compare(const void *a, const void *b) {
    return memcmp(a, b, n);
}

void generate_and_check(int index) {
    if (index == n) {
        uint128_t substrings[MAX_N];
        for (int i = 0; i <= n; i++) {
            char temp[MAX_N];
            strncpy(temp, input + i, n);
            strncpy(temp + n - i, output, i);
            substrings[i] = binary_to_decimal(temp, n);
        }
        
        double variance = calculate_variance(substrings, n + 1);
        
        static double min_variance = 1e9;
        static char solutions[MAX_N][MAX_N];
        static int solution_count = 0;
        
        if (fabs(variance - min_variance) < 1e-9) {
            strcpy(solutions[solution_count++], output);
        } else if (variance < min_variance) {
            min_variance = variance;
            solution_count = 0;
            strcpy(solutions[solution_count++], output);
        }
        
        if (index == n - 1) {
            qsort(solutions, solution_count, sizeof(solutions[0]), compare);
            for (int i = 0; i < solution_count; i++) {
                printf("%s\n", solutions[i]);
            }
        }
        return;
    }
    
    output[index] = '0';
    generate_and_check(index + 1);
    output[index] = '1';
    generate_and_check(index + 1);
}

int main() {
    scanf("%s", input);
    n = strlen(input);
    generate_and_check(0);
    return 0;
}