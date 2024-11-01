#include <stdio.h>
#include <stdlib.h>

#define MAX_N 2000001

long long phi[MAX_N];
long long sum[MAX_N];

void compute_phi() {
    for (int i = 1; i < MAX_N; i++) {
        phi[i] = i;
    }
    for (int i = 2; i < MAX_N; i++) {
        if (phi[i] == i) {
            for (int j = i; j < MAX_N; j += i) {
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
}

void compute_sum() {
    for (int i = 1; i < MAX_N; i++) {
        sum[i] = sum[i-1] + phi[i];
    }
}

long long solve(int n) {
    long long result = 0;
    for (int i = 1; i <= n; i++) {
        result += i * (sum[n/i] - sum[1]);
    }
    return (result + n) / 2;
}

int main() {
    int n;
    scanf("%d", &n);
    
    compute_phi();
    compute_sum();
    
    long long answer = solve(n);
    printf("%lld\n", answer);
    
    return 0;
}