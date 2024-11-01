#include <stdio.h>
#include <string.h>

#define MAXN 5000005

char s[MAXN];
int n, sa[MAXN], rk[MAXN], tmp[MAXN], lcp[MAXN];

void get_sa() {
    int i, j, p, w, d;
    memset(rk, 0, sizeof(rk));
    for (i = 0; i < n; i++) sa[i] = i, rk[i] = s[i];
    for (w = 1; w < n; w <<= 1) {
        for (i = 0; i < n; i++) {
            sa[i] = i;
            tmp[i] = rk[i] * (n + 1) + (i + w < n ? rk[i + w] : 0);
        }
        for (p = 0; p < n; p = j) {
            for (i = p, j = p + 1; j < n && tmp[sa[j]] == tmp[sa[i]]; j++);
            for (d = p; d < j; d++) rk[sa[d]] = p;
        }
    }
}

int main() {
    int i, ans = 0;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf(" %c", &s[i]);
        s[i + n] = s[i];
    }
    n *= 2;
    get_sa();
    for (i = 0; i < n; i++) {
        if (sa[i] < n / 2) {
            ans = sa[i];
            break;
        }
    }
    printf("%d\n", ans);
    return 0;
}