#include <stdio.h>
#include <math.h>

#define MAX_N 1000000
#define MAX_K 60

long long g[MAX_N + 1];
double f[MAX_N + 1];

void precompute() {
    for (int k = 2; k <= MAX_K; k++) {
        for (long long i = 2, p = 1; p <= MAX_N; i++) {
            p = pow(i, k);
            if (p > MAX_N) break;
            g[p]++;
        }
    }

    f[2] = g[2] / 2.0;
    for (int i = 3; i <= MAX_N; i++) {
        f[i] = f[i-1] + (double)g[i] / i;
    }
}

double solve(long long n) {
    if (n <= MAX_N) return f[n];
    
    double result = f[MAX_N];
    for (long long i = MAX_N + 1; i <= n; i++) {
        long long count = 0;
        for (int k = 2; k <= MAX_K; k++) {
            long long root = round(pow(i, 1.0 / k));
            if (pow(root, k) == i) count++;
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
        printf("%.14f\n", solve(n));
    }
    
    return 0;
}