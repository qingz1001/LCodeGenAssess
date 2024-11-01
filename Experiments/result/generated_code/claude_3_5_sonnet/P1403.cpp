#include <stdio.h>

#define MAXN 1000001

int f[MAXN];
long long sum[MAXN];

void precompute() {
    int i, j;
    for (i = 1; i < MAXN; i++) {
        for (j = i; j < MAXN; j += i) {
            f[j]++;
        }
    }
    for (i = 1; i < MAXN; i++) {
        sum[i] = sum[i-1] + f[i];
    }
}

int main() {
    int n;
    precompute();
    scanf("%d", &n);
    printf("%lld\n", sum[n]);
    return 0;
}