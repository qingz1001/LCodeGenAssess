#include <stdio.h>
#include <string.h>

#define MAXN 100005

char s[MAXN];
int cnt[MAXN];

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    scanf("%s", s);

    for (int i = 0; i < n - 1; i++) {
        if (s[i] == s[i + 1]) {
            cnt[i]++;
        }
    }

    for (int i = n - 2; i >= 0; i--) {
        cnt[i] += cnt[i + 1];
    }

    while (q--) {
        int l, r;
        scanf("%d %d", &l, &r);
        if (l > r) {
            printf("0\n");
        } else if (l == 1 && r == n) {
            printf("%d\n", cnt[0]);
        } else {
            int ans = 0;
            if (l > 1) {
                ans += cnt[l - 2];
            }
            if (r < n) {
                ans -= cnt[r - 1];
            }
            printf("%d\n", ans);
        }
    }

    return 0;
}