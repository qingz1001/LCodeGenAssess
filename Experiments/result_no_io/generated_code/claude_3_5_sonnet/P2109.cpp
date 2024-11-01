#include <stdio.h>
#include <string.h>

#define MOD 65521
#define MAXN 1005

int n, k;
int f[MAXN][MAXN];

void add(int *a, int b) {
    *a += b;
    if (*a >= MOD) *a -= MOD;
}

int main() {
    scanf("%d%d", &k, &n);
    
    f[1][0] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < i && j <= k; j++) {
            for (int p = 0; p < i-1 && p <= k; p++) {
                if (j == p + 1) {
                    add(&f[i][j], f[i-1][p]);
                } else if (j == 0 && p != 0) {
                    add(&f[i][j], f[i-1][p]);
                }
            }
        }
    }
    
    int ans = 0;
    for (int j = 0; j <= k; j++) {
        add(&ans, f[n][j]);
    }
    
    printf("%d\n", ans);
    
    return 0;
}