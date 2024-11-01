#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 1001
#define MAX_M 1001
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int n, m;
int a[MAX_N], b[MAX_N];
int dp[2][1 << 10];
int combination[MAX_M][10];
int size[MAX_M], c1[MAX_M], c2[MAX_M];

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
        scanf("%d %d %d", &size[i], &c1[i], &c2[i]);
        for (int j = 0; j < size[i]; j++) {
            scanf("%d", &combination[i][j]);
            combination[i][j]--;
        }
    }
    
    int max_state = 1 << n;
    for (int state = 0; state < max_state; state++) {
        int sum_a = 0, sum_b = 0;
        for (int i = 0; i < n; i++) {
            if (state & (1 << i)) {
                sum_a += a[i];
            } else {
                sum_b += b[i];
            }
        }
        
        for (int i = 0; i < m; i++) {
            int flag_a = 1, flag_b = 1;
            for (int j = 0; j < size[i]; j++) {
                if (!(state & (1 << combination[i][j]))) {
                    flag_a = 0;
                }
                if (state & (1 << combination[i][j])) {
                    flag_b = 0;
                }
            }
            if (flag_a) sum_a += c1[i];
            if (flag_b) sum_b += c2[i];
        }
        
        dp[0][state] = sum_a;
        dp[1][state] = sum_b;
    }
    
    int result = 0;
    for (int state = 0; state < max_state; state++) {
        result = MAX(result, dp[0][state] + dp[1][((1 << n) - 1) ^ state]);
    }
    
    printf("%d\n", result);
    
    return 0;
}