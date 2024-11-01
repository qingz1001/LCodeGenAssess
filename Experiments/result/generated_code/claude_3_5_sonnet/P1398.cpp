#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXN 155
#define MAXM 505

int n, m;
int a[MAXN][MAXM];
int sum[MAXN][MAXM];
int f[MAXN][MAXM][MAXN][MAXM];

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int getsum(int x1, int y1, int x2, int y2) {
    return sum[x2][y2] - sum[x1-1][y2] - sum[x2][y1-1] + sum[x1-1][y1-1];
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = n; i >= 1; i--)
        for (int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + a[i][j];

    memset(f, 0xc0, sizeof(f));
    
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            for (int k = i; k <= n; k++)
                for (int l = j; l <= m; l++)
                    if (k - i >= 2 && l - j >= 2)
                        f[i][j][k][l] = getsum(i, j, k, l) - getsum(i+1, j+1, k-1, l-1);

    int ans = INT_MIN;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m-11; j++) {
            int N = INT_MIN, O = INT_MIN, I = INT_MIN;
            
            for (int k = j+2; k <= m-9; k++)
                for (int l = i; l <= n; l++)
                    if (l - i >= 2)
                        N = max(N, getsum(i, j, l, j) + getsum(i, j+1, l, k-1) + getsum(l, j, n, k));
            
            for (int k = j+5; k <= m-4; k++)
                for (int l = i; l <= n-2; l++)
                    O = max(O, f[l][k][l+2][k+2]);
            
            for (int k = j+8; k <= m-1; k++)
                for (int l = i; l <= n-2; l++)
                    I = max(I, getsum(l, k, l, k+1) + getsum(l+1, k, l+1, k+1) + getsum(l+2, k, l+2, k+1));
            
            ans = max(ans, N + O + I);
        }
    
    printf("%d\n", ans);
    return 0;
}