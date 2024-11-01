#include <stdio.h>
#include <string.h>

#define MAXN 200005

int t, n, k;
char s[MAXN];

void solve() {
    int l = 1, r = n, mid, cnt, max_covered;
    while (l < r) {
        mid = (l + r) / 2;
        max_covered = 0;
        cnt = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '1') {
                if (i > max_covered) {
                    cnt++;
                    max_covered = i + mid - 1;
                }
                if (max_covered >= n - 1) {
                    break;
                }
            }
        }
        if (cnt <= k) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    printf("%d\n", l);
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%s", &n, &k, s);
        solve();
    }
    return 0;
}