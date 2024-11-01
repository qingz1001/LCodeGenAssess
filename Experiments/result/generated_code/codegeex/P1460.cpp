#include <stdio.h>
#include <stdlib.h>

int main() {
    int v, g;
    scanf("%d", &v);
    int* req = (int*)malloc(v * sizeof(int));
    for (int i = 0; i < v; i++) {
        scanf("%d", &req[i]);
    }

    scanf("%d", &g);
    int** feed = (int**)malloc(g * sizeof(int*));
    for (int i = 0; i < g; i++) {
        feed[i] = (int*)malloc(v * sizeof(int));
        for (int j = 0; j < v; j++) {
            scanf("%d", &feed[i][j]);
        }
    }

    int* dp = (int*)calloc(1 << v, sizeof(int));
    int* pre = (int*)calloc(1 << v, sizeof(int));

    for (int i = 0; i < (1 << v); i++) {
        for (int j = 0; j < g; j++) {
            int new_mask = i;
            for (int k = 0; k < v; k++) {
                if ((i & (1 << k)) == 0 && feed[j][k] > 0) {
                    new_mask |= (1 << k);
                }
            }
            if (dp[new_mask] > dp[i] + 1 || (dp[new_mask] == dp[i] + 1 && j < pre[i])) {
                dp[new_mask] = dp[i] + 1;
                pre[new_mask] = j;
            }
        }
    }

    int mask = (1 << v) - 1;
    printf("%d ", dp[mask]);
    int* result = (int*)malloc(dp[mask] * sizeof(int));
    for (int i = 0; mask > 0; i++) {
        result[i] = pre[mask] + 1;
        mask ^= (1 << (v - 1 - i));
    }

    for (int i = 0; i < dp[mask]; i++) {
        printf("%d ", result[i]);
    }

    free(req);
    for (int i = 0; i < g; i++) {
        free(feed[i]);
    }
    free(feed);
    free(dp);
    free(pre);
    free(result);

    return 0;
}