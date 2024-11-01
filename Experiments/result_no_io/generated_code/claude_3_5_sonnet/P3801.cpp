#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 100005

int n, m, q;
int row[MAXN], col[MAXN];

void update(int x, int y) {
    row[x] ^= 1;
    col[y] ^= 1;
}

int query(int x1, int y1, int x2, int y2) {
    int total = (x2 - x1 + 1) * (y2 - y1 + 1);
    int row_count = 0, col_count = 0;
    
    for (int i = x1; i <= x2; i++) {
        row_count += row[i];
    }
    for (int j = y1; j <= y2; j++) {
        col_count += col[j];
    }
    
    int fog_count = row_count * (y2 - y1 + 1) + col_count * (x2 - x1 + 1) - 2 * row_count * col_count;
    return fog_count;
}

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
            update(x, y);
        } else {
            int x1, y1, x2, y2;
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            printf("%d\n", query(x1, y1, x2, y2));
        }
    }
    
    return 0;
}