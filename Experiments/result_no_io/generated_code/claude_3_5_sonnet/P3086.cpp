#include <stdio.h>
#include <string.h>

#define MAX_N 300
#define MAX(a, b) ((a) > (b) ? (a) : (b))

char marble[MAX_N][MAX_N + 1];
int n;
long long dp[MAX_N][MAX_N][MAX_N];

long long solve() {
    long long result = -1;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = j; k < n; k++) {
                if (i == 0) {
                    dp[i][j][k] = (marble[i][j] == '.' && marble[i][k] == '.') ? (k - j + 1) : 0;
                } else {
                    if (marble[i][j] == '.' && marble[i][k] == '.') {
                        dp[i][j][k] = dp[i-1][j][k] + k - j + 1;
                    } else {
                        dp[i][j][k] = 0;
                    }
                }
            }
        }
    }

    for (int i = 1; i < n - 1; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = j; k < n; k++) {
                if (dp[i][j][k] == 0) continue;
                
                long long top_area = dp[i][j][k];
                
                for (int bottom_start = i + 1; bottom_start < n; bottom_start++) {
                    for (int bottom_end = bottom_start; bottom_end < n; bottom_end++) {
                        if (dp[n-1][bottom_start][bottom_end] - dp[i][bottom_start][bottom_end] == 0) continue;
                        
                        if (bottom_start > k || bottom_end < j) continue;
                        
                        long long bottom_area = dp[n-1][bottom_start][bottom_end] - dp[i][bottom_start][bottom_end];
                        result = MAX(result, top_area * bottom_area);
                    }
                }
            }
        }
    }

    return result;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", marble[i]);
    }

    long long result = solve();
    printf("%lld\n", result);

    return 0;
}