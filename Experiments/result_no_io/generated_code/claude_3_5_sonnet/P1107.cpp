#include <stdio.h>
#include <string.h>

#define MAX_N 2000
#define MAX_H 2000

int N, H, Delta;
int tree[MAX_N][MAX_H + 1];
int dp[MAX_N][MAX_H + 1];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d %d", &N, &H, &Delta);

    memset(tree, 0, sizeof(tree));
    for (int i = 0; i < N; i++) {
        int num_persimmons;
        scanf("%d", &num_persimmons);
        for (int j = 0; j < num_persimmons; j++) {
            int height;
            scanf("%d", &height);
            tree[i][height] = 1;
        }
    }

    memset(dp, 0, sizeof(dp));

    for (int h = H; h >= 0; h--) {
        for (int i = 0; i < N; i++) {
            if (h == H) {
                dp[i][h] = tree[i][h];
            } else {
                dp[i][h] = dp[i][h+1] + tree[i][h];
                for (int j = 0; j < N; j++) {
                    if (i != j && h + Delta <= H) {
                        dp[i][h] = max(dp[i][h], dp[j][h+Delta] + tree[i][h]);
                    }
                }
            }
        }
    }

    int result = 0;
    for (int i = 0; i < N; i++) {
        result = max(result, dp[i][0]);
    }

    printf("%d\n", result);

    return 0;
}