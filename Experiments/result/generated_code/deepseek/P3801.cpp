#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n, m, q;
int row[MAXN], col[MAXN];

int main() {
    scanf("%d %d %d", &n, &m, &q);
    
    for (int i = 0; i < q; i++) {
        int op, x, y, x1, y1, x2, y2;
        scanf("%d", &op);
        
        if (op == 1) {
            scanf("%d %d", &x, &y);
            row[x]++;
            col[y]++;
        } else if (op == 2) {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            int count = 0;
            for (int r = x1; r <= x2; r++) {
                count += col[r];
            }
            for (int c = y1; c <= y2; c++) {
                count += row[c];
            }
            printf("%d\n", count);
        }
    }
    
    return 0;
}