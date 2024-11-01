#include <stdio.h>
#include <string.h>

#define MAXN 15
#define MAXV 10000

int N, K;
int stamps[MAXN];
int dp[MAXV];
int max_value;

void dfs(int depth, int last) {
    if (depth == K) {
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        int i, j, k;
        for (i = 0; i < K; i++) {
            for (j = 0; j <= max_value; j++) {
                if (dp[j]) {
                    for (k = 1; k <= N && j + k * stamps[i] <= max_value; k++) {
                        dp[j + k * stamps[i]] = 1;
                    }
                }
            }
        }
        for (i = 1; i <= max_value; i++) {
            if (!dp[i]) {
                if (i - 1 > max_value) {
                    max_value = i - 1;
                    for (j = 0; j < K; j++) {
                        printf("%d ", stamps[j]);
                    }
                    printf("\nMAX=%d\n", max_value);
                }
                break;
            }
        }
        return;
    }
    
    for (int i = last + 1; i < MAXV; i++) {
        stamps[depth] = i;
        dfs(depth + 1, i);
    }
}

int main() {
    scanf("%d %d", &N, &K);
    dfs(0, 0);
    return 0;
}