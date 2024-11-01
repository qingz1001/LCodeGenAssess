#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000001
#define MAXM 100001

int a[MAXN];
int n, m;

void update(int x, int y) {
    for (int i = x - 1; i < n; i += x) {
        a[i] += y;
    }
}

int query(int j) {
    return a[j - 1];
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < m; i++) {
        int op, x, y, j;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d %d", &x, &y);
            update(x, y);
        } else if (op == 2) {
            scanf("%d", &j);
            printf("%d\n", query(j));
        }
    }

    return 0;
}