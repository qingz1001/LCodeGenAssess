#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 100005
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int n;
int a[MAX_N][3];
int dp[MAX_N][3];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &a[i][0], &a[i][1], &a[i][2]);
    }

    // Initialize dp array
    memset(dp, -1, sizeof(dp));
    
    // Base cases
    for (int i = 0; i < 3; i++) {
        dp[0][i] = a[0][i];
    }

    // Dynamic programming
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (j != k) {
                    if (dp[i-1][k] != -1) {
                        dp[i][j] = MAX(dp[i][j], dp[i-1][k] + a[i][j]);
                    }
                }
            }
        }
    }

    // Check the last tree with the first tree
    int result = -1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i != j) {
                if (dp[n-1][i] != -1 && dp[0][j] != -1) {
                    result = MAX(result, dp[n-1][i]);
                }
            }
        }
    }

    printf("%d\n", result);
    return 0;
}