#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000001

long long sum[MAXN];

void precompute() {
    for (int i = 1; i < MAXN; i++) {
        for (int j = i; j < MAXN; j += i) {
            sum[j]++;
        }
    }
    for (int i = 1; i < MAXN; i++) {
        sum[i] += sum[i-1];
    }
}

int main() {
    int n;
    precompute();
    scanf("%d", &n);
    printf("%lld\n", sum[n]);
    return 0;
}