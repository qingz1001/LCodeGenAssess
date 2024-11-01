#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_LEN 6000005
#define MAX_P 15

long long dp[MAX_N][MAX_LEN];
int prefix_sum[MAX_N];
char sentences[MAX_N][35];
int n, l, p;
int *lengths;

long long pow_abs(int x, int y) {
    long long res = 1;
    long long base = x;
    while (y) {
        if (y & 1) res *= base;
        base *= base;
        y >>= 1;
    }
    return res;
}

void solve() {
    int max_length = 0;
    for (int i = 1; i <= n; i++) {
        int len = strlen(sentences[i]);
        lengths[i] = len;
        prefix_sum[i] = prefix_sum[i - 1] + len;
        if (len > max_length) max_length = len;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < l + max_length; j++) {
            dp[i][j] = 1e18;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < l + max_length; j++) {
            if (j >= lengths[i]) {
                dp[i][j] = dp[i - 1][j - lengths[i]];
            }
            if (i > 1 && j == 0) {
                dp[i][j] = 0;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < l + max_length; j++) {
            if (dp[i][j] != 1e18) {
                int len = prefix_sum[i] - prefix_sum[i - 1];
                if (j + len <= l + max_length) {
                    dp[i][j + len] = dp[i][j] + pow_abs(abs(j + len - l), p);
                }
            }
        }
    }

    long long min_cost = 1e18;
    int last_split = 0;
    for (int i = 0; i < l + max_length; i++) {
        if (dp[n][i] < min_cost) {
            min_cost = dp[n][i];
            last_split = i;
        }
    }

    if (min_cost > 1e18) {
        printf("Too hard to arrange\n");
    } else {
        printf("%lld\n", min_cost);
        int current_length = 0;
        int last_index = 0;
        for (int i = n; i >= 1; i--) {
            if (dp[i][current_length] == dp[i - 1][current_length - lengths[i]]) {
                for (int j = last_index + 1; j <= i; j++) {
                    printf("%s ", sentences[j]);
                }
                current_length -= lengths[i];
                last_index = i;
            }
        }
        printf("\n");
    }

    printf("--------------------\n");
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &l, &p);
        lengths = (int *)malloc(sizeof(int) * (n + 1));
        for (int i = 1; i <= n; i++) {
            scanf("%s", sentences[i]);
        }
        solve();
        free(lengths);
    }
    return 0;
}