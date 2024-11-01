#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_M 500
#define MAX_K 500

int m, k;
int books[MAX_M + 1];
int dp[MAX_M + 1][MAX_K + 1];
int split[MAX_M + 1][MAX_K + 1];

int max(int a, int b) {
    return a > b ? a : b;
}

void calculate_dp() {
    int i, j, x;
    long long sum;

    for (i = 1; i <= m; i++) {
        dp[i][1] = dp[i-1][1] + books[i];
        split[i][1] = 1;
    }

    for (j = 2; j <= k; j++) {
        for (i = j; i <= m; i++) {
            dp[i][j] = INT_MAX;
            sum = 0;
            for (x = i; x >= j; x--) {
                sum += books[x];
                if (max(dp[x-1][j-1], (int)sum) < dp[i][j]) {
                    dp[i][j] = max(dp[x-1][j-1], (int)sum);
                    split[i][j] = x;
                }
            }
        }
    }
}

void print_result() {
    int i = m, j = k;
    int end, start;

    while (j > 0) {
        end = i;
        start = split[i][j];
        printf("%d %d\n", start, end);
        i = start - 1;
        j--;
    }
}

int main() {
    int i;

    scanf("%d %d", &m, &k);
    for (i = 1; i <= m; i++) {
        scanf("%d", &books[i]);
    }

    calculate_dp();
    print_result();

    return 0;
}