#include <stdio.h>
#include <stdlib.h>

#define MAXN 10001
#define MAXM 20001

int T, n, m;
int G[MAXN][MAXN];

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        int i, j;
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                G[i][j] = 0;
            }
        }
        for (i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            u--; v--;
            G[u][v] = 1;
            G[v][u] = 1;
        }

        int ok = 1;
        if (n == 1) {
            ok = 1;
        } else if (n == 2) {
            ok = G[0][1];
        } else if (n == 3) {
            ok = G[0][1] || G[0][2] || G[1][2];
        } else {
            for (i = 0; i < n; i++) {
                int cnt = 0;
                for (j = 0; j < n; j++) {
                    cnt += G[i][j];
                }
                if (cnt == 0) {
                    ok = 0;
                    break;
                }
            }
        }

        if (ok) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}