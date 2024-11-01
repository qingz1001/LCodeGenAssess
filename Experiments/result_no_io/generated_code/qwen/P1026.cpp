#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 20
#define MAX_WORD_COUNT 6
#define MAX_PARTS 40

int dp[MAX_PARTS + 1][MAX_LINE_LENGTH + 1];
char line[MAX_LINE_LENGTH + 1];
char words[MAX_WORD_COUNT][MAX_LINE_LENGTH + 1];

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int p, k, s;
    scanf("%d %d", &p, &k);
    for (int i = 0; i < p; i++) {
        scanf("%s", line);
    }
    scanf("%d", &s);
    for (int i = 0; i < s; i++) {
        scanf("%s", words[i]);
    }

    memset(dp, -1, sizeof(dp));
    dp[0][0] = 0;

    for (int part = 1; part <= k; part++) {
        for (int i = 0; i <= p * MAX_LINE_LENGTH; i++) {
            if (dp[part - 1][i] == -1) continue;
            for (int j = 0; j < s; j++) {
                char *pos = strstr(line + i, words[j]);
                if (pos != NULL) {
                    int len = strlen(words[j]);
                    dp[part][i + len] = max(dp[part][i + len], dp[part - 1][i] + 1);
                }
            }
        }
    }

    int result = 0;
    for (int i = 0; i <= p * MAX_LINE_LENGTH; i++) {
        result = max(result, dp[k][i]);
    }

    printf("%d\n", result);

    return 0;
}