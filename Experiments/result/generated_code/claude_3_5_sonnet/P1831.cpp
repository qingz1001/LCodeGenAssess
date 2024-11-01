#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_DIGITS 19

long long power10[MAX_DIGITS];

void precompute_power10() {
    power10[0] = 1;
    for (int i = 1; i < MAX_DIGITS; i++) {
        power10[i] = power10[i-1] * 10;
    }
}

bool is_lever_number(long long num) {
    char str[MAX_DIGITS + 1];
    sprintf(str, "%lld", num);
    int len = strlen(str);

    for (int pivot = 0; pivot < len; pivot++) {
        long long left_sum = 0, right_sum = 0;
        
        for (int i = 0; i < pivot; i++) {
            left_sum += (str[i] - '0') * (pivot - i);
        }
        
        for (int i = pivot + 1; i < len; i++) {
            right_sum += (str[i] - '0') * (i - pivot);
        }
        
        if (left_sum == right_sum) {
            return true;
        }
    }
    return false;
}

int count_lever_numbers(long long x, long long y) {
    int count = 0;
    for (long long i = x; i <= y; i++) {
        if (is_lever_number(i)) {
            count++;
        }
    }
    return count;
}

int main() {
    precompute_power10();
    
    long long x, y;
    scanf("%lld %lld", &x, &y);
    
    int result = count_lever_numbers(x, y);
    printf("%d\n", result);
    
    return 0;
}