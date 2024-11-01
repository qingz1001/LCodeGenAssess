#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 1001
#define MAX_M 1001
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int n, m;
int a[MAX_N], b[MAX_N];
int k[MAX_M], c1[MAX_M], c2[MAX_M];
int combination[MAX_M][MAX_N];
int dp[2][1 << 10];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
    }
    
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &k[i], &c1[i], &c2[i]);
        for (int j = 0; j < k[i]; j++) {
            int crop;
            scanf("%d", &crop);
            combination[i][crop-1] = 1;
        }
    }
    
    int all = (1 << n) - 1;
    for (int mask = 0; mask <= all; mask++) {
        int sum_a = 0, sum_b = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                sum_a += a[i];
            } else {
                sum_b += b[i];
            }
        }
        for (int i = 0; i < m; i++) {
            int flag_a = 1, flag_b = 1;
            for (int j = 0; j < n; j++) {
                if (combination[i][j]) {
                    if (!(mask & (1 << j))) flag_a = 0;
                    if (mask & (1 << j)) flag_b = 0;
                }
            }
            if (flag_a) sum_a += c1[i];
            if (flag_b) sum_b += c2[i];
        }
        dp[0][mask] = sum_a;
        dp[1][mask] = sum_b;
    }
    
    int result = 0;
    for (int mask = 0; mask <= all; mask++) {
        result = MAX(result, dp[0][mask] + dp[1][all ^ mask]);
    }
    
    printf("%d\n", result);
    
    return 0;
}