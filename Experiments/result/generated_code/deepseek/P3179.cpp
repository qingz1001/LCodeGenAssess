#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_K 100
#define MAX_W 100

bool has_winning_strategy(int n, int w, int white_indices[]) {
    bool dp[n + 1];
    memset(dp, false, sizeof(dp));

    for (int i = 0; i < w; ++i) {
        int x = white_indices[i];
        for (int k = 1; k * x <= n; ++k) {
            dp[k * x] = true;
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (!dp[i]) {
            return true;
        }
    }

    return false;
}

int main() {
    int n, k;
    scanf("%d", &n);
    scanf("%d", &k);

    for (int i = 0; i < k; ++i) {
        int w;
        scanf("%d", &w);
        int white_indices[MAX_W];
        for (int j = 0; j < w; ++j) {
            scanf("%d", &white_indices[j]);
        }

        if (has_winning_strategy(n, w, white_indices)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}