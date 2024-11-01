#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000005
#define MAXS 105
#define INF 0x3f3f3f3f

typedef long long ll;

int n, s;
ll l[MAXN], pref[MAXN], d[MAXS];
ll sum;

int check(ll x) {
    int cnt = 1, last = 0;
    for (int i = 1; i <= n; i++) {
        if (pref[i] - pref[last] > x) {
            if (i == last + 1) return 0;
            cnt++;
            last = i - 1;
            i--;
        }
    }
    if (sum - (pref[n] - pref[last]) > x) {
        if (last == n - 1) return 0;
        cnt++;
    }
    return cnt;
}

int main() {
    scanf("%d%d", &n, &s);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &l[i]);
        sum += l[i];
        pref[i] = pref[i-1] + l[i];
    }

    for (int i = 1; i <= s; i++) {
        scanf("%lld", &d[i]);
    }

    for (int i = 1; i <= s; i++) {
        if (d[i] < sum) {
            int left = 1, right = n, ans = INF;
            while (left <= right) {
                int mid = (left + right) >> 1;
                int res = check(d[i] * mid);
                if (res) {
                    ans = mid;
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            if (ans == INF) {
                printf("NIE\n");
            } else {
                printf("%d\n", ans);
            }
        } else {
            printf("1\n");
        }
    }

    return 0;
}