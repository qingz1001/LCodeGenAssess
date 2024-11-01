#include <stdio.h>
#include <stdbool.h>

#define MAX_N 30
#define MAX_V 20000

int min(int a, int b) {
    return (a < b) ? a : b;
}

bool canFit(int V, int n, int volumes[], int capacity) {
    bool dp[MAX_N + 1][MAX_V + 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= capacity; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = (j == 0);
            } else if (volumes[i - 1] > j) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - volumes[i - 1]];
            }
        }
    }
    return dp[n][capacity];
}

int main() {
    int V, n;
    scanf("%d %d", &V, &n);
    int volumes[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d", &volumes[i]);
    }

    int best_capacity = 0;
    for (int i = 0; i <= V; i++) {
        if (canFit(V, n, volumes, i)) {
            best_capacity = i;
        }
    }

    printf("%d\n", V - best_capacity);

    return 0;
}