#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005

int n, q;
long long s[MAXN];

void update(int l, int r, int d) {
    for (int i = l; i <= r; i++) {
        s[i] += d;
    }
}

int query(int l, int r) {
    long long min_val = s[r];
    int min_pos = r;
    for (int i = r - 1; i >= l; i--) {
        if (s[i] < min_val) {
            min_val = s[i];
            min_pos = i;
        }
    }
    return min_pos;
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &s[i]);
    }
    for (int i = 0; i < q; i++) {
        int type, l, r, d;
        scanf("%d %d %d", &type, &l, &r);
        if (type == 1) {
            scanf("%d", &d);
            update(l, r, d);
        } else if (type == 2) {
            printf("%d\n", query(l, r));
        }
    }
    return 0;
}