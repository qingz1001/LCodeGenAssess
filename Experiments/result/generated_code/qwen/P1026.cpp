#include <stdio.h>
#include <string.h>

#define MAX_LEN 201
#define MAX_WORDS 7

int dp[MAX_LEN][MAX_LEN];
char str[MAX_LEN];
char words[MAX_WORDS][MAX_LEN];

int min(int a, int b) {
    return (a < b) ? a : b;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int p, k, s;
    scanf("%d %d", &p, &k);
    for (int i = 0; i < p; ++i) {
        scanf("%s", str + i * 20);
    }
    scanf("%d", &s);
    for (int i = 0; i < s; ++i) {
        scanf("%s", words[i]);
    }

    memset(dp, -1, sizeof(dp));
    dp[0][0] = 0;

    for (int i = 0; i <= p * 20; ++i) {
        if (dp[i][0] != -1) {
            for (int j = 0; j < s; ++j) {
                int len = strlen(words[j]);
                if (i + len <= p * 20 && dp[i][0] + 1 >= dp[i + len][j + 1]) {
                    dp[i + len][j + 1] = dp[i][0] + 1;
                }
            }
        }
    }

    int result = 0;
    for (int i = 0; i <= p * 20; ++i) {
        result = max(result, dp[i][k]);
    }

    printf("%d\n", result);

    return 0;
}