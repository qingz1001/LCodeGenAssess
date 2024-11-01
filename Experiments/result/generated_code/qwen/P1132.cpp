#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM_LENGTH 6
#define MAX_QUERY 50000

int min_operations(char *s, char *t) {
    int len_s = strlen(s);
    int len_t = strlen(t);
    if (len_s != len_t) return -1;

    int dp[len_s][len_s];
    memset(dp, 0xff, sizeof(dp));

    for (int i = 0; i < len_s; ++i) {
        dp[i][i] = 0;
    }

    for (int l = 2; l <= len_s; ++l) {
        for (int i = 0; i <= len_s - l; ++i) {
            int j = i + l - 1;
            for (int k = i; k < j; ++k) {
                if ((s[k] > s[j] && s[i] < s[j]) || (s[k] < s[j] && s[i] > s[j])) {
                    int cost = (dp[i][k] == -1 ? INT_MAX : dp[i][k]) +
                               (dp[k + 1][j] == -1 ? INT_MAX : dp[k + 1][j]) + 1;
                    if (cost < dp[i][j]) {
                        dp[i][j] = cost;
                    }
                }
            }
        }
    }

    return dp[0][len_s - 1];
}

int main() {
    char s[MAX_NUM_LENGTH];
    scanf("%s", s);

    int m;
    scanf("%d", &m);

    char queries[MAX_QUERY][MAX_NUM_LENGTH];
    for (int i = 0; i < m; ++i) {
        scanf("%s", queries[i]);
    }

    for (int i = 0; i < m; ++i) {
        printf("%d\n", min_operations(s, queries[i]));
    }

    return 0;
}