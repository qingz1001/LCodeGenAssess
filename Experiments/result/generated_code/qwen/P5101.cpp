#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000005
#define MAXM 10005

int N, M;
int C[MAXN];
int dp[MAXM][MAXM];

void merge(int *a, int *b, int *c, int size) {
    int i = 0, j = 0, k = 0;
    while (i < size && j < size) {
        if (a[i] <= b[j]) {
            c[k++] = a[i++];
        } else {
            c[k++] = b[j++];
        }
    }
    while (i < size) {
        c[k++] = a[i++];
    }
    while (j < size) {
        c[k++] = b[j++];
    }
}

int min_cost(int color) {
    for (int i = 0; i <= N; i++) {
        dp[i][0] = 0;
    }
    for (int i = 1; i <= N; i++) {
        if (C[i-1] == color) {
            dp[i][1] = dp[i-1][1] + 1;
        } else {
            dp[i][1] = dp[i-1][1];
        }
        for (int j = 2; j <= i; j++) {
            dp[i][j] = dp[i-1][j] + (C[i-1] != color ? j : 0);
        }
    }
    return dp[N][1];
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &C[i]);
    }
    for (int i = 1; i <= M; i++) {
        printf("%d\n", min_cost(i));
    }
    return 0;
}