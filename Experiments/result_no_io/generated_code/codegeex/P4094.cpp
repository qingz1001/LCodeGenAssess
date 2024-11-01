#include <stdio.h>
#include <string.h>

const int N = 100005;
int n, m, sa[N], rk[N], ork[N], buc[N], id[N], cnt[N];
char s[N];

int cmp(int a, int b, int w) {
    return ork[a] == ork[b] && ork[a + w] == ork[b + w];
}

void build(int m) {
    int i, p, *x = rk, *y = ork;
    for (i = 0; i < m; i++) cnt[i] = 0;
    for (i = 0; i < n; i++) cnt[x[i] = s[i]]++;
    for (i = 1; i < m; i++) cnt[i] += cnt[i - 1];
    for (i = n - 1; ~i; i--) sa[--cnt[x[i]]] = i;
    for (p = 1; p < n; p <<= 1) {
        for (i = n - p, y[sa[i]] = 0, i--; ~i; i--) y[sa[i]] = cmp(sa[i], sa[i + p], p) ? y[sa[i + p]] : p + 1;
        memcpy(cnt, y, m << 2);
        for (i = 0; i < m; i++) cnt[i] += cnt[i - 1];
        for (i = n - 1; ~i; i--) sa[--cnt[y[i]]] = i;
        memcpy(x, y, n << 2);
        if ((m = y[sa[0]]) >= n) break;
    }
}

int main() {
    scanf("%d%d%s", &n, &m, s);
    build(128);
    while (m--) {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        a--; b--; c--; d--;
        while (b - a + 1 > d - c + 1) b--;
        while (d - c + 1 > b - a + 1) c++;
        while (a < b && c < d && s[sa[a]] == s[sa[c]]) a++, c++;
        printf("%d\n", c - a + 1);
    }
    return 0;
}