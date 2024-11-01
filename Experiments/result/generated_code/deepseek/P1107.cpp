#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 2000
#define MAXH 2000

int N, H, Delta;
int tree[MAXN][MAXH];
int dp[MAXN][MAXH];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d %d", &N, &H, &Delta);

    memset(tree, 0, sizeof(tree));
    memset(dp, 0, sizeof(dp));

    for (int i = 0; i < N; i++) {
        int Ni;
        scanf("%d", &Ni);
        for (int j = 0; j < Ni; j++) {
            int height;
            scanf("%d", &height);
            tree[i][height]++;
        }
    }

    for (int h = H; h >= 0; h--) {
        for (int i = 0; i < N; i++) {
            dp[i][h] = tree[i][h];
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
                dp[i][h] = max(dp[i][h], tree[i][h] + max_jump);
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