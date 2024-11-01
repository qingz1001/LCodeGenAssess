#include <stdio.h>
#include <stdlib.h>

#define MAXN 10005

int N, M;
int A[MAXN];
int dp[MAXN][MAXN];

void preprocess() {
    for (int i = 1; i <= N; i++) {
        dp[i][1] = i;
        for (int j = 2; j <= i; j++) {
            dp[i][j] = -1;
            for (int k = 1; k < i; k++) {
                if (A[k] < A[i] && (dp[i][j] == -1 || dp[k][j-1] < dp[i][j])) {
                    dp[i][j] = dp[k][j-1];
                }
            }
            if (dp[i][j] != -1) {
                dp[i][j]++;
            }
        }
    }
}

int find_lis(int length) {
    int result = -1;
    for (int i = 1; i <= N; i++) {
        if (dp[i][length] != -1 && (result == -1 || dp[i][length] < result)) {
            result = dp[i][length];
        }
    }
    return result;
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }
    scanf("%d", &M);

    preprocess();

    for (int i = 0; i < M; i++) {
        int L;
        scanf("%d", &L);
        int result = find_lis(L);
        if (result != -1) {
            printf("%d\n", result);
        } else {
            printf("Impossible\n");
        }
    }

    return 0;
}