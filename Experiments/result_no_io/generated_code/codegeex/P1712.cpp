#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define MAXN 500005

struct Interval {
    int l, r;
    bool operator<(const Interval& other) const {
        return r < other.r;
    }
};

Interval intervals[MAXN];
int count[MAXN];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &intervals[i].l, &intervals[i].r);
    }

    std::sort(intervals, intervals + n);

    int ans = -1;
    int left = 0, right = 0;
    while (right < n) {
        while (right < n && count[right] < m) {
            count[intervals[right].l]++;
            count[intervals[right].r + 1]--;
            right++;
        }
        if (count[right] < m) break;

        for (int i = left; i <= right; i++) {
            count[intervals[i].l]--;
            count[intervals[i].r + 1]++;
        }

        while (count[left] == 0) {
            left++;
        }

        if (count[left] == m) {
            ans = std::min(ans, intervals[right].r - intervals[left].l);
        }

        for (int i = left; i <= right; i++) {
            count[intervals[i].l]++;
            count[intervals[i].r + 1]--;
        }
        left++;
    }

    printf("%d\n", ans);
    return 0;
}