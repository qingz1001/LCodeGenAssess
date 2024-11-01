#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_P 10000

int main() {
    int N, Pi;
    scanf("%d %d", &N, &Pi);

    int items[MAX_N];
    int types[MAX_N];
    int values[MAX_N][2];

    for (int i = 0; i < N; i++) {
        scanf("%d", &items[i]);
        if (items[i] <= Pi) {
            types[i] = 0; // 普通物品
            values[i][0] = items[i];
            values[i][1] = 0;
        } else {
            types[i] = 1; // 魔法物品
            scanf("%d %d", &values[i][0], &values[i][1]);
        }
    }

    int dp[MAX_P + 1];
    for (int i = 0; i <= MAX_P; i++) {
        dp[i] = 0;
    }

    for (int i = 0; i < N; i++) {
        if (types[i] == 0) {
            for (int j = MAX_P; j >= items[i]; j--) {
                dp[j] = dp[j] > dp[j - items[i]] + items[i] ? dp[j] : dp[j - items[i]] + items[i];
            }
        } else {
            for (int j = MAX_P; j >= values[i][0]; j--) {
                dp[j] = dp[j] > dp[j - values[i][0]] + values[i][1] ? dp[j] : dp[j - values[i][0]] + values[i][1];
            }
        }
    }

    printf("%d\n", dp[MAX_P]);

    return 0;
}