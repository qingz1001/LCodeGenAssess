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
        int num;
        scanf("%d", &num);
        for (int j = 0; j < num; j++) {
            int height;
            scanf("%d", &height);
            tree[i][height] = 1;
        }
    }

    memset(dp, -1, sizeof(dp));
    
    for (int i = 0; i < N; i++) {
        dp[i][H] = tree[i][H];
    }

    int result = 0;
    for (int h = H; h > 0; h--) {
        for (int i = 0; i < N; i++) {
            if (dp[i][h] == -1) continue;

            result = max(result, dp[i][h]);

            if (h > 1) {
                dp[i][h-1] = max(dp[i][h-1], dp[i][h] + tree[i][h-1]);
            }

            for (int j = 0; j < N; j++) {
                if (i == j) continue;
                int newH = max(1, h - Delta);
                dp[j][newH] = max(dp[j][newH], dp[i][h] + tree[j][newH]);
            }
        }
    }

    printf("%d\n", result);

    return 0;
}