#include <stdio.h>
#include <string.h>

#define MAXN 100005
#define MAXQ 300005

char s[MAXN];
int cnt[10][MAXN];

void preprocess() {
    int n = strlen(s);
    for (int i = 0; i < 10; ++i) {
        memset(cnt[i], 0, sizeof(int) * (n + 1));
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 10; ++j) {
            cnt[j][i] = cnt[j][i - 1];
        }
        cnt[s[i - 1] - '0'][i]++;
    }
}

int query(int l, int r, int d) {
    return cnt[d][r] - cnt[d][l - 1];
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    scanf("%s", s);
    preprocess();

    while (q--) {
        int l, r;
        scanf("%d %d", &l, &r);
        int ans = 0;
        for (int i = 1; i < l; ++i) {
            if (query(i, l - 1, s[l - 1] - '0') > 0) {
                ans += query(1, r, s[r - 1] - '0');
            }
        }
        for (int i = r + 1; i <= n; ++i) {
            if (query(r + 1, i - 1, s[r - 1] - '0') > 0) {
                ans += query(l, n, s[n - 1] - '0');
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}