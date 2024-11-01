#include <stdio.h>
#include <string.h>

#define MAXN 100005
#define MAXQ 300005

char s[MAXN];
int n, q;
int l[MAXQ], r[MAXQ];
int ans[MAXQ];

void solve() {
    for (int k = 0; k < q; k++) {
        int len = r[k] - l[k] + 1;
        int count = 0;
        for (int i = 1; i <= n - len + 1; i++) {
            for (int j = i + 1; j <= n - len + 1; j++) {
                if (strncmp(s + l[k] - 1, s + i - 1, len) == 0 ||
                    strncmp(s + l[k] - 1, s + j - 1, len) == 0) {
                    count++;
                }
            }
        }
        ans[k] = count;
    }
}

int main() {
    scanf("%d %d", &n, &q);
    scanf("%s", s);
    for (int i = 0; i < q; i++) {
        scanf("%d %d", &l[i], &r[i]);
    }
    solve();
    for (int i = 0; i < q; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}