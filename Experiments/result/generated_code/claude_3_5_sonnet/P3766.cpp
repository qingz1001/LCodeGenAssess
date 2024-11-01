#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_N 1000000
#define MAX_K 60

long long g[MAX_N + 1];
double f[MAX_N + 1];

void precompute() {
    for (int k = 2; k <= MAX_K; k++) {
        long long p = 1;
        while (p <= MAX_N) {
            g[p]++;
            p *= k;
        }
    }
    
    f[2] = 0.5;
    for (int i = 3; i <= MAX_N; i++) {
        f[i] = f[i-1] + (double)g[i] / i;
    }
}

double calculate(long long n) {
    if (n <= MAX_N) {
        return f[n];
    }
    
    double result = f[MAX_N];
    for (long long i = MAX_N + 1; i <= n; i++) {
        int count = 0;
        for (int k = 2; k <= MAX_K; k++) {
            long long root = round(pow(i, 1.0 / k));
            if (root * root * root == i || (root - 1) * (root - 1) * (root - 1) == i || (root + 1) * (root + 1) * (root + 1) == i) {
                count++;
            }
        }
        result += (double)count / i;
    }
    
    return result;
}

int main() {
    precompute();
    
    int T;
    scanf("%d", &T);
    
    while (T--) {
        long long n;
        scanf("%lld", &n);
        printf("%.14f\n", calculate(n));
    }
    
    return 0;
}