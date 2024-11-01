#include <stdio.h>
#include <stdbool.h>

#define MAX_N 8

int n;
int sectors[MAX_N];
bool used[MAX_N + 1];
int max_i = 0;
int results[MAX_N][MAX_N];
int result_count = 0;

bool can_form_sequence(int i) {
    bool dp[MAX_N * MAX_N + 1] = {false};
    dp[0] = true;
    for (int j = 0; j < n; j++) {
        for (int k = i; k >= sectors[j]; k--) {
            if (dp[k - sectors[j]]) {
                dp[k] = true;
            }
        }
    }
    for (int j = 1; j <= i; j++) {
        if (!dp[j]) return false;
    }
    return true;
}

void dfs(int index, int sum) {
    if (index == n) {
        if (can_form_sequence(sum)) {
            if (sum > max_i) {
                max_i = sum;
                result_count = 0;
            }
            if (sum == max_i) {
                for (int i = 0; i < n; i++) {
                    results[result_count][i] = sectors[i];
                }
                result_count++;
            }
        }
        return;
    }
    for (int i = 1; i <= n * n; i++) {
        if (!used[i]) {
            used[i] = true;
            sectors[index] = i;
            dfs(index + 1, sum + i);
            used[i] = false;
        }
    }
}

int main() {
    scanf("%d", &n);
    dfs(0, 0);
    printf("%d\n", max_i);
    for (int i = 0; i < result_count; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", results[i][j]);
        }
        printf("\n");
    }
    return 0;
}