#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005

typedef struct {
    int l, r;
} Interval;

int compare(const void *a, const void *b) {
    return ((Interval *)a)->l - ((Interval *)b)->l;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    Interval intervals[MAXN];
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &intervals[i].l, &intervals[i].r);
    }
    
    qsort(intervals, n, sizeof(Interval), compare);
    
    int ans = -1;
    for (int i = 0; i <= n - m; i++) {
        int max_len = 0, min_len = 1e9;
        for (int j = i; j < i + m; j++) {
            if (max_len < intervals[j].r - intervals[j].l + 1) {
                max_len = intervals[j].r - intervals[j].l + 1;
            }
            if (min_len > intervals[j].r - intervals[j].l + 1) {
                min_len = intervals[j].r - intervals[j].l + 1;
            }
        }
        if (ans == -1 || ans > max_len - min_len) {
            ans = max_len - min_len;
        }
    }
    
    printf("%d\n", ans);
    
    return 0;
}