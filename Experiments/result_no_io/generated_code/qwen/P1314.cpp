#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005
#define LL long long

int n, m, s;
struct {
    int w, v;
} stones[MAXN];
struct {
    int l, r;
} intervals[MAXN];

LL query(int W) {
    LL result = 0;
    for (int i = 0; i < m; ++i) {
        int l = intervals[i].l - 1, r = intervals[i].r - 1;
        int count = 0;
        for (int j = l; j <= r; ++j) {
            if (stones[j].w >= W) {
                ++count;
            }
        }
        LL sum = 0;
        for (int j = l; j <= r; ++j) {
            if (stones[j].w >= W) {
                sum += stones[j].v;
            }
        }
        result += (LL)count * count * sum;
    }
    return result;
}

int main() {
    scanf("%d %d %lld", &n, &m, &s);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &stones[i].w, &stones[i].v);
    }
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &intervals[i].l, &intervals[i].r);
    }

    int left = 0, right = 1000000;
    while (left < right) {
        int mid = (left + right) / 2;
        LL res = query(mid);
        if (res == s) {
            printf("0\n");
            return 0;
        } else if (res > s) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    LL min_diff = abs(s - query(left));
    LL diff_right = abs(s - query(left + 1));
    if (diff_right < min_diff) {
        min_diff = diff_right;
    }
    printf("%lld\n", min_diff);

    return 0;
}