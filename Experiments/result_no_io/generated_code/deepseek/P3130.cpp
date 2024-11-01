#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 200000
#define MAXQ 100000

typedef long long ll;

ll haybales[MAXN + 1];
ll diff[MAXN + 1];
ll prefix_sum[MAXN + 1];

void update_diff(int l, int r, ll val) {
    diff[l] += val;
    if (r + 1 <= MAXN) diff[r + 1] -= val;
}

void build_prefix_sum() {
    for (int i = 1; i <= MAXN; i++) {
        haybales[i] += diff[i];
        if (i + 1 <= MAXN) diff[i + 1] += diff[i];
        prefix_sum[i] = prefix_sum[i - 1] + haybales[i];
    }
}

ll query_sum(int l, int r) {
    return prefix_sum[r] - prefix_sum[l - 1];
}

ll query_min(int l, int r) {
    ll min_val = LLONG_MAX;
    for (int i = l; i <= r; i++) {
        if (haybales[i] < min_val) min_val = haybales[i];
    }
    return min_val;
}

int main() {
    int N, Q;
    scanf("%d %d", &N, &Q);

    for (int i = 1; i <= N; i++) {
        scanf("%lld", &haybales[i]);
        prefix_sum[i] = prefix_sum[i - 1] + haybales[i];
    }

    char op;
    int A, B, C;
    for (int i = 0; i < Q; i++) {
        scanf(" %c", &op);
        if (op == 'P') {
            scanf("%d %d %d", &A, &B, &C);
            update_diff(A, B, C);
        } else if (op == 'M') {
            scanf("%d %d", &A, &B);
            build_prefix_sum();
            printf("%lld\n", query_min(A, B));
        } else if (op == 'S') {
            scanf("%d %d", &A, &B);
            build_prefix_sum();
            printf("%lld\n", query_sum(A, B));
        }
    }

    return 0;
}