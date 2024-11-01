#include <stdio.h>
#include <stdlib.h>

#define MAX_N 2500

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int students[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d", &students[i]);
    }

    int dp[MAX_N];
    dp[0] = 1;

    for (int i = 1; i < n; i++) {
        dp[i] = i + 1;
        int count1 = 0, count2 = 0;

        for (int j = i; j >= 0; j--) {
            if (students[j] == 1) count1++;
            else count2++;

            if (count1 == 0 || count2 == 0 || abs(count1 - count2) <= m) {
                dp[i] = min(dp[i], (j == 0 ? 0 : dp[j - 1]) + 1);
            }
        }
    }

    printf("%d\n", dp[n - 1]);

    return 0;
}