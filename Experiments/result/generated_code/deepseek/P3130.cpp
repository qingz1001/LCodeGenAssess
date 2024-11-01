#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005
#define MAXQ 100005

typedef long long ll;

ll haybales[MAXN];
ll diff[MAXN];
ll prefix_sum[MAXN];

void update(int l, int r, int c) {
    diff[l] += c;
    diff[r + 1] -= c;
}

void apply_updates(int n) {
    for (int i = 1; i <= n; i++) {
        haybales[i] += diff[i];
        diff[i + 1] += diff[i];
    }
    for (int i = 1; i <= n; i++) {
        prefix_sum[i] = prefix_sum[i - 1] + haybales[i];
    }
}

ll query_min(int l, int r) {
    ll min_haybales = haybales[l];
    for (int i = l + 1; i <= r; i++) {
        if (haybales[i] < min_haybales) {
            min_haybales = haybales[i];
        }
    }
    return min_haybales;
}

ll query_sum(int l, int r) {
    return prefix_sum[r] - prefix_sum[l - 1];
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", &haybales[i]);
        prefix_sum[i] = prefix_sum[i - 1] + haybales[i];
    }

    char op;
    int a, b, c;
    while (q--) {
        scanf(" %c", &op);
        if (op == 'M') {
            scanf("%d %d", &a, &b);
            printf("%lld\n", query_min(a, b));
        } else if (op == 'S') {
            scanf("%d %d", &a, &b);
            printf("%lld\n", query_sum(a, b));
        } else if (op == 'P') {
            scanf("%d %d %d", &a, &b, &c);
            update(a, b, c);
        }
    }

    apply_updates(n);

    return 0;
}