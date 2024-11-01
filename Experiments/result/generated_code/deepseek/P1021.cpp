#include <stdio.h>
#include <stdlib.h>

#define MAX_N 15
#define MAX_K 15

int N, K;
int max_value = 0;
int best_values[MAX_K];
int current_values[MAX_K];

int dp[MAX_N * MAX_K];

void dfs(int depth, int last_value) {
    if (depth == K) {
        for (int i = 0; i < MAX_N * MAX_K; i++) {
            dp[i] = MAX_N + 1;
        }
        dp[0] = 0;

        for (int i = 0; i < K; i++) {
            for (int j = current_values[i]; j < MAX_N * MAX_K; j++) {
                dp[j] = (dp[j] < dp[j - current_values[i]] + 1) ? dp[j] : dp[j - current_values[i]] + 1;
            }
        }

        int max_possible = 0;
        while (dp[max_possible] <= N) {
            max_possible++;
        }
        max_possible--;

        if (max_possible > max_value) {
            max_value = max_possible;
            for (int i = 0; i < K; i++) {
                best_values[i] = current_values[i];
            }
        }
        return;
    }

    for (int i = last_value + 1; i <= 1000; i++) {
        current_values[depth] = i;
        dfs(depth + 1, i);
    }
}

int main() {
    scanf("%d %d", &N, &K);

    dfs(0, 0);

    for (int i = 0; i < K; i++) {
        printf("%d ", best_values[i]);
    }
    printf("\nMAX=%d\n", max_value);

    return 0;
}