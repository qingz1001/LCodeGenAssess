#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005

typedef long long ll;

int n, f;
ll values[MAXN];
ll prefix_sum[MAXN];

void add_range(int l, int r, ll k) {
    prefix_sum[l] += k;
    if (r + 1 < n) {
        prefix_sum[r + 1] -= k;
    }
}

void update_main(ll k) {
    prefix_sum[0] += k;
}

void decrease_main(ll k) {
    prefix_sum[0] -= k;
}

ll query_range(int l, int r) {
    return prefix_sum[l] + (prefix_sum[n - 1] - prefix_sum[r]);
}

int main() {
    scanf("%d %d", &n, &f);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &values[i]);
    }

    // Initialize prefix sum array
    for (int i = 0; i < n; ++i) {
        prefix_sum[i] = values[i];
    }
    for (int i = 1; i < n; ++i) {
        prefix_sum[i] += prefix_sum[i - 1];
    }

    for (int i = 0; i < f; ++i) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            int l, r;
            ll k;
            scanf("%d %d %lld", &l, &r, &k);
            add_range(l, r - 1, k);
        } else if (type == 2) {
            ll k;
            scanf("%lld", &k);
            update_main(k);
        } else if (type == 3) {
            ll k;
            scanf("%lld", &k);
            decrease_main(k);
        } else if (type == 4) {
            int l, r;
            scanf("%d %d", &l, &r);
            printf("%lld\n", query_range(l, r - 1));
        } else if (type == 5) {
            printf("%lld\n", prefix_sum[0]);
        }
    }

    return 0;
}