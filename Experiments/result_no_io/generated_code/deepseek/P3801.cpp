#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n, m, q;
int row[MAXN], col[MAXN];

int main() {
    scanf("%d %d %d", &n, &m, &q);
    
    for (int i = 0; i < q; i++) {
        int op;
        scanf("%d", &op);
        
        if (op == 1) {
            int x, y;
            scanf("%d %d", &x, &y);
            row[x]++;
            col[y]++;
        } else if (op == 2) {
            int x1, y1, x2, y2;
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            
            int count = 0;
            for (int r = x1; r <= x2; r++) {
                if (row[r] > 0) {
                    count += (y2 - y1 + 1);
                }
            }
            for (int c = y1; c <= y2; c++) {
                if (col[c] > 0) {
                    count += (x2 - x1 + 1);
                }
            }
            for (int r = x1; r <= x2; r++) {
                for (int c = y1; c <= y2; c++) {
                    if (row[r] > 0 && col[c] > 0) {
                        count--;
                    }
                }
            }
            
            printf("%d\n", count);
        }
    }
    
    return 0;
}