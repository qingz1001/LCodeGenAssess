#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n, m;
int a[MAXN];

int count_color_in_range(int l, int r, int c) {
    int count = 0;
    for (int i = l; i <= r; i++) {
        if (a[i] == c) {
            count++;
        }
    }
    return count;
}

void swap(int x) {
    int temp = a[x];
    a[x] = a[x + 1];
    a[x + 1] = temp;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < m; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int l, r, c;
            scanf("%d %d %d", &l, &r, &c);
            printf("%d\n", count_color_in_range(l, r, c));
        } else if (op == 2) {
            int x;
            scanf("%d", &x);
            swap(x);
        }
    }

    return 0;
}