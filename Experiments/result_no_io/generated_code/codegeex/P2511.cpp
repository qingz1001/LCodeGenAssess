#include <stdio.h>
#include <stdlib.h>

#define MAXN 50005
#define MAXM 1001
#define MOD 10007

int n, m, len[MAXN], sum[MAXN], max_len, total_ways, max_sum;

int can_cut(int max_segment_length) {
    int cuts = 0, current_length = 0, i;
    for (i = 1; i <= n; i++) {
        if (len[i] > max_segment_length) return 0;
        if (current_length + len[i] > max_segment_length) {
            current_length = len[i];
            cuts++;
        } else {
            current_length += len[i];
        }
    }
    return cuts <= m;
}

int main() {
    int i, j, l, r, mid, count, ways[MAXM];

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%d", &len[i]);
        max_len = len[i] > max_len ? len[i] : max_len;
        sum[i] = sum[i-1] + len[i];
    }

    l = 1;
    r = sum[n];
    while (l <= r) {
        mid = (l + r) / 2;
        if (can_cut(mid)) {
            max_sum = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    ways[0] = 1;
    for (i = 1; i <= n; i++) {
        for (j = m; j >= 1; j--) {
            for (l = 1, count = 0; l <= i && count <= j; l++, count++) {
                ways[j] = (ways[j] + ways[j - count] * (i - l + 1)) % MOD;
            }
        }
    }

    printf("%d %d\n", max_sum, ways[m]);
    return 0;
}