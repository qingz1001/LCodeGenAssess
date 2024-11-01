#include <stdio.h>
#include <string.h>

#define MAXN 200
#define MAXS 200000
#define MAXE 10

int n, m;
char elements[MAXN][MAXE];
char sequence[MAXS];

int dp[MAXS + 1];

int main() {
    int len = 0;
    while (scanf("%s", elements[n]) == 1 && strcmp(elements[n], ".") != 0) {
        n++;
    }

    char buffer[80];
    while (fgets(buffer, sizeof(buffer), stdin)) {
        for (int i = 0; buffer[i]; i++) {
            if (buffer[i] == '\n') break;
            sequence[len++] = buffer[i];
        }
    }

    memset(dp, -1, sizeof(dp));
    dp[0] = 0;

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < n; j++) {
            int e_len = strlen(elements[j]);
            if (i >= e_len && strcmp(sequence + i - e_len, elements[j]) == 0) {
                dp[i + 1] = dp[i + 1] > dp[i - e_len] + e_len ? dp[i + 1] : dp[i - e_len] + e_len;
            }
        }
    }

    printf("%d\n", dp[len]);

    return 0;
}