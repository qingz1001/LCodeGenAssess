#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 2000
#define MAXH 2000

int N, H, Delta;
int trees[MAXN][MAXH];
int dp[MAXN][MAXH];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d %d", &N, &H, &Delta);

    memset(trees, 0, sizeof(trees));
    memset(dp, 0, sizeof(dp));

    for (int i = 0; i < N; i++) {
        int Ni;
        scanf("%d", &Ni);
        for (int j = 0; j < Ni; j++) {
            int height;
            scanf("%d", &height);
            trees[i][height]++;
        }
    }

    for (int h = H; h >= 0; h--) {
        for (int i = 0; i < N; i++) {
            dp[i][h] = trees[i][h];
            if (h + 1 <= H) {
                dp[i][h] += dp[i][h + 1];
            }
            if (h + Delta <= H) {
                int max_jump = 0;
                for (int j = 0; j < N; j++) {
                    if (j != i) {
                        max_jump = max(max_jump, dp[j][h + Delta]);
                    }
                }
                dp[i][h] = max(dp[i][h], trees[i][h] + max_jump);
            }
        }
    }

    int max_fruits = 0;
    for (int i = 0; i < N; i++) {
        max_fruits = max(max_fruits, dp[i][0]);
    }

    printf("%d\n", max_fruits);

    return 0;
}