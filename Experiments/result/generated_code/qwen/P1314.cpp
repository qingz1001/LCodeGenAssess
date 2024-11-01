#include <stdio.h>
#include <stdlib.h>

#define MAXN 200001
#define MAXM 200001

int n, m, s;
int w[MAXN], v[MAXN];
int l[MAXM], r[MAXM];

long long calculate_y(int W) {
    long long y = 0;
    for (int i = 0; i < m; i++) {
        int cnt = 0;
        for (int j = l[i]; j <= r[i]; j++) {
            if (w[j] >= W) {
                cnt++;
                y += (long long)v[j];
            }
        }
        y += (long long)cnt * cnt;
    }
    return y;
}

int main() {
    scanf("%d %d %lld", &n, &m, &s);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &w[i], &v[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &l[i], &r[i]);
    }

    long long low = 0, high = 1000000, best_diff = 1e18, best_W = 0;

    while (low <= high) {
        long long mid = (low + high) / 2;
        long long y = calculate_y(mid);
        long long diff = abs(s - y);

        if (diff == 0) {
            printf("0\n");
            return 0;
        } else if (diff < best_diff) {
            best_diff = diff;
            best_W = mid;
        }

        if (y > s) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    printf("%lld\n", best_diff);
    return 0;
}