#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 501

int compare(const char *a, const char *b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    if (len_a != len_b) return len_a - len_b;
    return strcmp(a, b);
}

void split_sequence(char *s) {
    int n = strlen(s);
    char **dp = (char **)malloc((n + 1) * sizeof(char *));
    int **prev = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        dp[i] = (char *)malloc((n + 1) * sizeof(char));
        prev[i] = (int *)malloc((n + 1) * sizeof(int));
        memset(dp[i], 0, (n + 1) * sizeof(char));
        memset(prev[i], -1, (n + 1) * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        dp[i][i + 1] = 1;
        prev[i][i + 1] = i;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len <= n; i++) {
            int j = i + len;
            dp[i][j] = 0;
            for (int k = i + 1; k < j; k++) {
                if (dp[i][k] && dp[k][j] && compare(&s[i], &s[k]) < 0) {
                    if (!dp[i][j] || compare(&s[prev[i][j]], &s[k]) < 0) {
                        dp[i][j] = 1;
                        prev[i][j] = k;
                    }
                }
            }
        }
    }

    int i = 0, j = n;
    while (i < j) {
        int k = prev[i][j];
        if (k != -1) {
            printf("%.*s,", k - i, &s[i]);
            i = k;
        } else {
            break;
        }
    }
    printf("%s\n", &s[i]);

    for (int i = 0; i <= n; i++) {
        free(dp[i]);
        free(prev[i]);
    }
    free(dp);
    free(prev);
}

int main() {
    char s[MAX_LEN];
    scanf("%s", s);
    split_sequence(s);
    return 0;
}