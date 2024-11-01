#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 20

int compare(char *a, char *b) {
    int len_a = strlen(a), len_b = strlen(b);
    if (len_a != len_b) return len_a - len_b;
    return strcmp(a, b);
}

void to_string(long long n, char *str) {
    sprintf(str, "%lld", n);
}

long long solve(long long K, long long M) {
    char K_str[MAX_DIGITS];
    to_string(K, K_str);
    
    long long left = K, right = 1e18;
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        char mid_str[MAX_DIGITS];
        to_string(mid, mid_str);
        
        long long count = 0;
        for (long long i = 1; i <= mid; i++) {
            char i_str[MAX_DIGITS];
            to_string(i, i_str);
            if (compare(i_str, K_str) < 0) count++;
        }
        
        if (count == M - 1) return mid;
        if (count < M - 1) left = mid + 1;
        else right = mid - 1;
    }
    
    return 0;
}

int main() {
    long long K, M;
    scanf("%lld %lld", &K, &M);
    
    long long result = solve(K, M);
    printf("%lld\n", result);
    
    return 0;
}