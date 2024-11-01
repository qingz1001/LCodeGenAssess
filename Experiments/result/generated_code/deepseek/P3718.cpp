#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXN 100005

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n, k;
    char s[MAXN];
    scanf("%d %d", &n, &k);
    scanf("%s", s);

    int dp[MAXN][2];
    int max_len = 0;

    // Initialize dp array
    dp[0][0] = (s[0] == 'N') ? 1 : 0;
    dp[0][1] = (s[0] == 'F') ? 1 : 0;

    for (int i = 1; i < n; i++) {
        if (s[i] == 'N') {
            dp[i][0] = dp[i-1][0] + 1;
            dp[i][1] = 0;
        } else {
            dp[i][1] = dp[i-1][1] + 1;
            dp[i][0] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        max_len = max(max_len, dp[i][0]);
        max_len = max(max_len, dp[i][1]);
    }

    if (k == 0) {
        printf("%d\n", max_len);
        return 0;
    }

    int left = 0, right = 0;
    int count_N = (s[0] == 'N') ? 1 : 0;
    int count_F = (s[0] == 'F') ? 1 : 0;
    int min_ugliness = INT_MAX;

    while (right < n) {
        int current_max = max(count_N, count_F);
        if (current_max <= max_len) {
            min_ugliness = min(min_ugliness, current_max);
        }

        if (current_max <= max_len && right - left + 1 < n) {
            right++;
            if (s[right] == 'N') count_N++;
            else count_F++;
        } else {
            if (s[left] == 'N') count_N--;
            else count_F--;
            left++;
        }
    }

    printf("%d\n", min_ugliness);
    return 0;
}