#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_N 1000000

long long n;
int k[MAX_N + 1];
int max_k = 0;

void calculate_k() {
    for (int i = 1; i <= MAX_N; i++) {
        k[i] = i;
    }
    
    for (int i = 1; i * i <= MAX_N; i++) {
        for (int j = i * i; j <= MAX_N; j++) {
            if (k[j - i * i] < j && k[j] > k[j - i * i]) {
                k[j] = k[j - i * i];
            }
        }
    }
    
    for (int i = 1; i <= MAX_N; i++) {
        if (k[i] == i) k[i] = 0;
        max_k = (k[i] > max_k) ? k[i] : max_k;
    }
}

long long get_k(long long x) {
    if (x <= MAX_N) return k[x];
    for (int i = 1; i <= max_k; i++) {
        long long sum = 0, j = i;
        while (sum < x && j > 0) {
            sum += j * j;
            j--;
        }
        if (sum == x) return i;
    }
    return -1;
}

int main() {
    scanf("%lld", &n);
    calculate_k();
    
    long long k_n = get_k(n);
    if (k_n == -1) {
        printf("- ");
    } else {
        printf("%lld ", k_n);
    }
    
    int count = 0;
    long long max_k_so_far = 0;
    for (long long i = n; i >= 1; i--) {
        long long k_i = get_k(i);
        if (k_i > max_k_so_far) {
            max_k_so_far = k_i;
            count++;
        }
    }
    
    printf("%d\n", count);
    
    return 0;
}