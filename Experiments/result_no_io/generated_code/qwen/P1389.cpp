#include <stdio.h>
#include <stdlib.h>

#define MAXN 151

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int N;
    scanf("%d", &N);
    int V[MAXN], A[MAXN];
    for (int i = 0; i < N; i++) {
        scanf("%d", &V[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    int dp[MAXN][MAXN];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dp[i][j] = 0;
        }
    }

    for (int length = 1; length <= N; length++) {
        for (int start = 0; start + length - 1 < N; start++) {
            int end = start + length - 1;
            if (length == 1) {
                dp[start][end] = V[length - 1];
            } else {
                dp[start][end] = -1e9;
                for (int mid = start; mid < end; mid++) {
                    if (mid == start || mid == end || (A[mid] > A[mid - 1] && A[mid] > A[mid + 1])) {
                        dp[start][end] = max(dp[start][end], dp[start][mid] + dp[mid + 1][end] + V[length - 1]);
                    }
                }
            }
        }
    }

    printf("%d\n", dp[0][N - 1]);

    return 0;
}