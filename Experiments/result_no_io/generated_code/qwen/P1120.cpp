#include <stdio.h>
#include <stdlib.h>

#define MAX_N 65
#define MAX_LENGTH 50

int n;
int sticks[MAX_N];
int dp[MAX_N][MAX_LENGTH * MAX_N];

int min(int a, int b) {
    return (a < b) ? a : b;
}

int solve(int start, int end) {
    if (dp[start][end] != -1) return dp[start][end];
    if (start == end) return sticks[start];

    int result = INT_MAX;
    for (int i = start; i < end; i++) {
        result = min(result, solve(start, i) + solve(i + 1, end));
    }
    dp[start][end] = result;
    return result;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &sticks[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = -1;
        }
    }

    printf("%d\n", solve(0, n - 1));

    return 0;
}