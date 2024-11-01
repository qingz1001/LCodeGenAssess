#include <stdio.h>
#include <string.h>

#define MAX_N 4000005
#define MAX_C 100005

int n, c, q;
int ci[MAX_C], ti[MAX_C];
int ai[MAX_N];
int sum[MAX_N];

int check(int mid) {
    memset(sum, 0, sizeof(sum));
    for (int i = 1; i <= mid; i++) {
        sum[ai[i]]++;
        sum[ai[i] + n]--;
    }
    for (int i = 1; i <= n; i++) {
        sum[i] += sum[i-1];
    }
    int total = 0;
    for (int i = 1; i <= c; i++) {
        int count = 0;
        for (int j = 1; j <= n - ci[i] + 1; j++) {
            if (sum[j] == 0 && sum[j+ci[i]-1] == 0) {
                count++;
                j += ci[i] - 1;
            }
        }
        total += (count < ti[i] ? count : ti[i]);
    }
    int ships = 0;
    for (int i = 1; i <= c; i++) {
        ships += ti[i];
    }
    return total < ships;
}

int solve() {
    int ships = 0;
    for (int i = 1; i <= c; i++) {
        ships += ci[i] * ti[i];
    }
    if (ships > n) return 0;

    int left = 1, right = q;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (check(mid)) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return left > q ? -1 : left;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &n, &c, &q);
        for (int i = 1; i <= c; i++) {
            scanf("%d%d", &ci[i], &ti[i]);
        }
        for (int i = 1; i <= q; i++) {
            scanf("%d", &ai[i]);
        }
        printf("%d\n", solve());
    }
    return 0;
}