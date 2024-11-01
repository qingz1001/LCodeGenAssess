#include <stdio.h>
#include <string.h>

#define MAXN 100005

int n, m, q;
int row[MAXN], col[MAXN];

int main() {
    scanf("%d %d %d", &n, &m, &q);

    memset(row, 0, sizeof(row));
    memset(col, 0, sizeof(col));

    while (q--) {
        int op;
        scanf("%d", &op);

        if (op == 1) {
            int x, y;
            scanf("%d %d", &x, &y);
            row[x] ^= 1;
            col[y] ^= 1;
        } else {
            int x1, y1, x2, y2;
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            int count = 0;
            for (int i = x1; i <= x2; i++) {
                for (int j = y1; j <= y2; j++) {
                    if (row[i] ^ col[j]) {
                        count++;
                    }
                }
            }
            printf("%d\n", count);
        }
    }

    return 0;
}