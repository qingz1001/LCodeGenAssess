#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 200005

int n, q;
long long s[MAXN];

void update(int l, int r, long long d) {
    for (int i = l; i <= r; i++) {
        s[i] += d;
    }
}

int query(int l, int r) {
    long long min_val = LLONG_MAX;
    int min_pos = l;
    for (int i = l; i <= r; i++) {
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
    while (q--) {
        int type, l, r;
        long long d;
        scanf("%d %d %d", &type, &l, &r);
        if (type == 1) {
            scanf("%lld", &d);
            update(l, r, d);
        } else if (type == 2) {
            printf("%d\n", query(l, r));
        }
    }
    return 0;
}