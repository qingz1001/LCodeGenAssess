#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 501

char input[MAX_LEN];
int len;
int dp[MAX_LEN];
int prev[MAX_LEN];

bool is_greater(char *a, int len_a, char *b, int len_b) {
    if (len_a != len_b) return len_a > len_b;
    return strcmp(a, b) > 0;
}

void solve() {
    memset(dp, 0, sizeof(dp));
    memset(prev, -1, sizeof(prev));

    for (int i = 0; i < len; i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (is_greater(input + j + 1, i - j, input + prev[j] + 1, j - prev[j])) {
                if (dp[j] + 1 > dp[i] || (dp[j] + 1 == dp[i] && is_greater(input, j + 1, input, prev[i] + 1))) {
                    dp[i] = dp[j] + 1;
                    prev[i] = j;
                }
            }
        }
    }

    int last = len - 1;
    while (last > 0 && is_greater(input, last + 1, input + prev[last] + 1, last - prev[last])) {
        last = prev[last];
    }

    int result[MAX_LEN], count = 0;
    while (last != -1) {
        result[count++] = last;
        last = prev[last];
    }

    for (int i = count - 1; i >= 0; i--) {
        if (i < count - 1) printf(",");
        for (int j = (i == count - 1 ? 0 : result[i + 1] + 1); j <= result[i]; j++) {
            printf("%c", input[j]);
        }
    }
    printf("\n");
}

int main() {
    scanf("%s", input);
    len = strlen(input);
    solve();
    return 0;
}