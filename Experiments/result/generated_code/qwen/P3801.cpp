#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n, m, q;
int row[MAXN], col[MAXN];

void update(int *arr, int size, int pos) {
    for (; pos <= size; pos += pos & -pos)
        arr[pos]++;
}

int query(int *arr, int size, int pos) {
    int sum = 0;
    for (; pos > 0; pos -= pos & -pos)
        sum += arr[pos];
    return sum;
}

int main() {
    scanf("%d %d %d", &n, &m, &q);
    memset(row, 0, sizeof(row));
    memset(col, 0, sizeof(col));

    while (q--) {
        int op, x1, y1, x2, y2;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d %d", &x1, &y1);
            update(row, n, x1);
            update(col, m, y1);
        } else {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            int ans = (query(row, n, x2) - query(row, n, x1 - 1)) * (query(col, m, y2) - query(col, m, y1 - 1));
            printf("%d\n", ans);
        }
    }

    return 0;
}