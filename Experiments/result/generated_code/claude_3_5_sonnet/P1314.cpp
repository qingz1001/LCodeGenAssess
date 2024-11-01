#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 200001
#define MAX_M 200001

typedef long long ll;

struct Stone {
    int w, v;
} stones[MAX_N];

struct Query {
    int l, r;
} queries[MAX_M];

int n, m;
ll s;
int w[MAX_N], v[MAX_N];
int sorted_w[MAX_N];

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

ll calc(int W) {
    static int cnt[MAX_N], sum[MAX_N];
    memset(cnt, 0, sizeof(cnt));
    memset(sum, 0, sizeof(sum));

    for (int i = 1; i <= n; i++) {
        cnt[i] = cnt[i-1] + (stones[i].w >= W);
        sum[i] = sum[i-1] + (stones[i].w >= W ? stones[i].v : 0);
    }

    ll result = 0;
    for (int i = 0; i < m; i++) {
        int l = queries[i].l, r = queries[i].r;
        ll c = cnt[r] - cnt[l-1];
        ll s = sum[r] - sum[l-1];
        result += c * s;
    }
    return result;
}

int main() {
    scanf("%d%d%lld", &n, &m, &s);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &stones[i].w, &stones[i].v);
        sorted_w[i] = stones[i].w;
    }

    for (int i = 0; i < m; i++) {
        scanf("%d%d", &queries[i].l, &queries[i].r);
    }

    qsort(sorted_w + 1, n, sizeof(int), cmp);

    ll min_diff = LLONG_MAX;
    int left = 1, right = n;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int W = sorted_w[mid];
        ll y = calc(W);

        min_diff = llabs(s - y) < min_diff ? llabs(s - y) : min_diff;

        if (y > s) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    printf("%lld\n", min_diff);
    return 0;
}