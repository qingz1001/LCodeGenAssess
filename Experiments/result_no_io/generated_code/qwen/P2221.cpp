#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n, m;
long long fee[MAXN];

void update(int l, int r, int v) {
    for (int i = l; i <= r; i++) {
        fee[i] += v;
    }
}

long long query(int l, int r) {
    long long sum = 0;
    for (int i = l; i <= r; i++) {
        sum += fee[i];
    }
    return sum;
}

int gcd(long long a, long long b) {
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        fee[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        char op;
        scanf(" %c", &op);
        if (op == 'C') {
            int l, r, v;
            scanf("%d %d %d", &l, &r, &v);
            update(l, r, v);
        } else if (op == 'Q') {
            int l, r;
            scanf("%d %d", &l, &r);
            long long total_fee = query(l, r);
            long long pairs = (r - l + 1) * (r - l) / 2;
            long long g = gcd(total_fee, pairs);
            printf("%lld/%lld\n", total_fee / g, pairs / g);
        }
    }

    return 0;
}