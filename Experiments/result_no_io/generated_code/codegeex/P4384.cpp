#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXQ 300005

int n, q;
char s[MAXN];
int nxt[MAXN][10];

void build_nxt() {
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < 10; j++) {
            nxt[i][j] = -1;
        }
        nxt[i][s[i] - '0'] = i + 1;
        for (int j = 0; j < 10; j++) {
            nxt[i][j] = nxt[i + 1][j];
        }
    }
}

int main() {
    scanf("%d %d", &n, &q);
    scanf("%s", s);
    build_nxt();
    while (q--) {
        int l, r;
        scanf("%d %d", &l, &r);
        long long ans = 0;
        for (int i = 1; i < n; i++) {
            if (nxt[i][s[i] - '0'] != -1 && nxt[i][s[i] - '0'] < l) {
                ans += n - nxt[i][s[i] - '0'];
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}