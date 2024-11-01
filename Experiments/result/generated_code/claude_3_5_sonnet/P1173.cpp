#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_C 100000

typedef long long ll;

int T, n, m, c;
ll x[MAX_C], y[MAX_C];

int cmp(const void *a, const void *b) {
    ll *pa = (ll*)a, *pb = (ll*)b;
    return *pa > *pb ? 1 : -1;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &c);
        for (int i = 0; i < c; i++) {
            scanf("%lld%lld", &x[i], &y[i]);
        }
        
        if (c == n * m) {
            printf("-1\n");
            continue;
        }
        
        if (c == 0) {
            printf(n == 1 && m == 1 ? "-1\n" : "0\n");
            continue;
        }
        
        qsort(x, c, sizeof(ll), cmp);
        qsort(y, c, sizeof(ll), cmp);
        
        ll max_gap_x = x[0] - 1 > n - x[c-1] ? x[0] - 1 : n - x[c-1];
        ll max_gap_y = y[0] - 1 > m - y[c-1] ? y[0] - 1 : m - y[c-1];
        
        for (int i = 1; i < c; i++) {
            ll gap_x = x[i] - x[i-1] - 1;
            ll gap_y = y[i] - y[i-1] - 1;
            max_gap_x = gap_x > max_gap_x ? gap_x : max_gap_x;
            max_gap_y = gap_y > max_gap_y ? gap_y : max_gap_y;
        }
        
        if (max_gap_x >= 2 || max_gap_y >= 2) {
            printf("0\n");
        } else if (max_gap_x == 1 || max_gap_y == 1) {
            printf("1\n");
        } else {
            printf("2\n");
        }
    }
    return 0;
}