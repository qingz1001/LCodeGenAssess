#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 20001

int n, k;
int s[MAXN], h[MAXN], nxt[MAXN][22], f[MAXN][22], lg[MAXN];

int main() {
    int i, j, l, p, q, ans;
    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++) {
        scanf("%d", &s[i]);
    }
    h[1] = s[1];
    for (i = 2; i <= n; i++) {
        h[i] = h[i-1] * 233 + s[i];
    }
    nxt[1][0] = 0;
    for (i = 1; i <= n; i++) {
        nxt[i][0] = i - 1;
    }
    for (l = 1; l <= 20; l++) {
        for (i = 1; i + (1 << l) - 1 <= n; i++) {
            nxt[i][l] = nxt[nxt[i][l-1]][l-1];
        }
    }
    lg[1] = 0;
    for (i = 2; i <= n; i++) {
        lg[i] = lg[i/2] + 1;
    }
    ans = 0;
    for (i = 1; i <= n; i++) {
        for (l = 20; l >= 0; l--) {
            if (i + (1 << l) - 1 <= n && nxt[i][l] && f[nxt[i][l]][l] >= k) {
                i = nxt[i][l] + (1 << l) - 1;
                ans = (1 << l);
                break;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}