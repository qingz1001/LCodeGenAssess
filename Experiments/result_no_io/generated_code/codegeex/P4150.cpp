#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 100005

int n, q;
int a[6][MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < 6; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    scanf("%d", &q);

    while (q--) {
        int op, x1, y1, x2, y2, c;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d%d", &x1, &y1, &c);
            a[x1-1][y1] = c;
        } else if (op == 2) {
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            int minDistance = 0;
            // Calculate the minimum distance between (x1, y1) and (x2, y2)
            minDistance = abs(y1 - y2);
            if (x1 != x2) {
                minDistance += 2;
            }
            printf("%d\n", minDistance);
        }
    }
    return 0;
}