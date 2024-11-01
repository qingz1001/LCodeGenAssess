#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 1005
#define INF 0x3f3f3f3f

int N, T[MAXN], B[MAXN];
int f[MAXN][8], g[MAXN][8];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int C;
    scanf("%d", &C);
    while (C--) {
        scanf("%d", &N);
        for (int i = 1; i <= N; i++) {
            scanf("%d %d", &T[i], &B[i]);
        }
        
        memset(f, 0x3f, sizeof(f));
        f[0][0] = 0;
        
        for (int i = 1; i <= N; i++) {
            for (int j = 0; j <= 7; j++) {
                for (int k = 0; k <= min(j, B[i]); k++) {
                    if (f[i-1][k] == INF) continue;
                    int time = (T[i] | g[i-1][k]) - (T[i] & g[i-1][k]);
                    if (k == 0) time = 0;
                    if (f[i-1][k] + time < f[i][j]) {
                        f[i][j] = f[i-1][k] + time;
                        g[i][j] = T[i];
                    }
                }
            }
        }
        
        int ans = INF;
        for (int j = 0; j <= 7; j++) {
            ans = min(ans, f[N][j]);
        }
        printf("%d\n", ans);
    }
    return 0;
}