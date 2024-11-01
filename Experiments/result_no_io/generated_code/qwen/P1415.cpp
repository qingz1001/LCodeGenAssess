#include <stdio.h>
#include <string.h>

#define MAX_LEN 505

void splitSequence(char *input) {
    int len = strlen(input);
    char result[MAX_LEN];
    int dp[len][len];
    int path[len][len];

    for (int i = 0; i < len; i++) {
        dp[i][i] = 1;
        path[i][i] = -1;
    }

    for (int l = 2; l <= len; l++) {
        for (int i = 0; i + l - 1 < len; i++) {
            int j = i + l - 1;
            dp[i][j] = 0;
            for (int k = i; k < j; k++) {
                if (dp[i][k] && (k == j || input[k] < input[j])) {
                    if (dp[i][j] < dp[i][k] + dp[k + 1][j]) {
                        dp[i][j] = dp[i][k] + dp[k + 1][j];
                        path[i][j] = k;
                    }
                }
            }
        }
    }

    int start = 0, end = len - 1;
    while (start <= end) {
        int mid = path[start][end];
        if (mid != -1) {
            printf("%.*s,", mid - start + 1, input + start);
            start = mid + 1;
        } else {
            printf("%.*s", end - start + 1, input + start);
            break;
        }
    }
}

int main() {
    char input[MAX_LEN];
    scanf("%s", input);
    splitSequence(input);
    return 0;
}