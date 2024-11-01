#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int N;
int S[MAX_N], A[MAX_N];
long long dp[MAX_N];

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &S[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    qsort(S, N, sizeof(int), cmp);

    long long sum_A = 0;
    for (int i = 0; i < N; i++) {
        sum_A += A[i];
        dp[i] = sum_A + 2LL * S[N-1];
    }

    for (int i = N-2; i >= 0; i--) {
        long long diff = S[i+1] - S[i];
        for (int j = i; j < N; j++) {
            dp[j] -= diff;
        }
    }

    for (int i = 0; i < N; i++) {
        printf("%lld\n", dp[i]);
    }

    return 0;
}