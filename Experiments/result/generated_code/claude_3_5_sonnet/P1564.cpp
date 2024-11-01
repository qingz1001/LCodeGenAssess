#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 2501

int n, m;
int students[MAX_N];
int dp[MAX_N];

int abs(int x) {
    return x > 0 ? x : -x;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int isValid(int start, int end) {
    int count1 = 0, count2 = 0;
    for (int i = start; i <= end; i++) {
        if (students[i] == 1) count1++;
        else count2++;
    }
    return count1 == end - start + 1 || count2 == end - start + 1 || abs(count1 - count2) <= m;
}

int solve() {
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = i; j >= 1; j--) {
            if (isValid(j, i)) {
                dp[i] = min(dp[i], dp[j-1] + 1);
            }
        }
    }

    return dp[n];
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &students[i]);
    }

    int result = solve();
    printf("%d\n", result);

    return 0;
}