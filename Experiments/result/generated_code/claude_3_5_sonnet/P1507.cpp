#include <stdio.h>
#include <string.h>

#define MAX_N 51
#define MAX_H 401
#define MAX_T 401

int dp[MAX_H][MAX_T];
int h[MAX_N], t[MAX_N], k[MAX_N];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int H, T, n;
    
    scanf("%d %d", &H, &T);
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d", &h[i], &t[i], &k[i]);
    }
    
    memset(dp, 0, sizeof(dp));
    
    for (int i = 1; i <= n; i++) {
        for (int j = H; j >= h[i]; j--) {
            for (int l = T; l >= t[i]; l--) {
                dp[j][l] = max(dp[j][l], dp[j-h[i]][l-t[i]] + k[i]);
            }
        }
    }
    
    printf("%d\n", dp[H][T]);
    
    return 0;
}