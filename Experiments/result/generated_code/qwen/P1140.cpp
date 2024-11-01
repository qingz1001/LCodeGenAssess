#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define INF -1000000

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int n1, n2;
    char seq1[MAX_N + 1], seq2[MAX_N + 1];
    scanf("%d %s", &n1, seq1);
    scanf("%d %s", &n2, seq2);

    int dp[MAX_N + 1][MAX_N + 1];
    for (int i = 0; i <= n1; i++) {
        for (int j = 0; j <= n2; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else {
                int match = (seq1[i - 1] == seq2[j - 1]) ? 5 : -1;
                dp[i][j] = max(max(dp[i - 1][j - 1] + match, dp[i - 1][j] - 3), dp[i][j - 1] - 3);
            }
        }
    }

    printf("%d\n", dp[n1][n2]);
    return 0;
}