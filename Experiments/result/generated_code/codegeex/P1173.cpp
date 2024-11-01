#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m, c;
        scanf("%d%d%d", &n, &m, &c);
        int x, y;
        int has_chickens[MAXN][MAXN] = {0};
        for (int i = 0; i < c; i++) {
            scanf("%d%d", &x, &y);
            has_chickens[x][y] = 1;
        }

        // 判断是否已经存在不连通的情况
        int is_disconnected = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (has_chickens[i][j] == 0) {
                    if ((has_chickens[i-1][j] || has_chickens[i+1][j]) && (has_chickens[i][j-1] || has_chickens[i][j+1])) {
                        is_disconnected = 1;
                        break;
                    }
                }
            }
            if (is_disconnected) break;
        }

        if (is_disconnected) {
            printf("0\n");
        } else if (c == 0) {
            if (n * m == 1) {
                printf("-1\n");
            } else {
                printf("1\n");
            }
        } else if (c == 1) {
            if (n * m == 1) {
                printf("-1\n");
            } else if (n * m == 2) {
                printf("1\n");
            } else {
                printf("2\n");
            }
        } else if (c == 2) {
            if (n * m == 1) {
                printf("-1\n");
            } else if (n * m == 2) {
                printf("1\n");
            } else if (n * m == 3) {
                printf("2\n");
            } else {
                printf("3\n");
            }
        } else {
            printf("-1\n");
        }
    }
    return 0;
}