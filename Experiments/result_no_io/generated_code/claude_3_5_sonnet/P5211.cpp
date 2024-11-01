#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200005
#define MAX_LOG 18

typedef long long ll;

int n, q;
ll a[MAX_N];
int log_table[MAX_N];
int st[MAX_N][MAX_LOG];

void build_sparse_table() {
    for (int i = 2; i <= n; i++)
        log_table[i] = log_table[i / 2] + 1;

    for (int i = 1; i <= n; i++)
        st[i][0] = i;

    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            int left = st[i][j - 1];
            int right = st[i + (1 << (j - 1))][j - 1];
            st[i][j] = (a[left] <= a[right]) ? left : right;
        }
    }
}

int query(int l, int r) {
    int k = log_table[r - l + 1];
    int left = st[l][k];
    int right = st[r - (1 << k) + 1][k];
    return (a[left] <= a[right]) ? left : right;
}

void update(int l, int r, ll d) {
    for (int i = l; i <= r; i++)
        a[i] += d;
}

int main() {
    scanf("%d %d", &n, &q);

    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);

    build_sparse_table();

    while (q--) {
        int op, l, r;
        scanf("%d %d %d", &op, &l, &r);

        if (op == 1) {
            ll d;
            scanf("%lld", &d);
            update(l, r, d);
            build_sparse_table();
        } else {
            printf("%d\n", query(l, r));
        }
    }

    return 0;
}