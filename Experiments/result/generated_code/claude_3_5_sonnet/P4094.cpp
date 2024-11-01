#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 100005
#define min(a,b) ((a)<(b)?(a):(b))

char s[MAXN];
int n, m;
int sa[MAXN], rk[MAXN], tmp[MAXN], lcp[MAXN];
int st[MAXN][20], lg[MAXN];

void get_sa() {
    int i, j, k;
    int m = 128;
    for (i = 1; i <= n; i++) rk[i] = s[i], sa[i] = i;
    for (k = 1; k <= n; k <<= 1) {
        for (i = n - k + 1; i <= n; i++) tmp[i - n + k] = i;
        for (i = 1, j = k; i <= n; i++) if (sa[i] > k) tmp[j++] = sa[i] - k;
        memset(sa, 0, sizeof(sa));
        for (i = 1; i <= m; i++) sa[i] = 0;
        for (i = 1; i <= n; i++) sa[rk[tmp[i]]]++;
        for (i = 1; i <= m; i++) sa[i] += sa[i - 1];
        for (i = n; i >= 1; i--) sa[sa[rk[tmp[i]]]--] = tmp[i];
        memcpy(tmp, rk, sizeof(rk));
        for (i = 1, m = 0; i <= n; i++) {
            if (tmp[sa[i]] != tmp[sa[i - 1]] || tmp[sa[i] + k] != tmp[sa[i - 1] + k])
                rk[sa[i]] = ++m;
            else
                rk[sa[i]] = m;
        }
        if (m == n) break;
    }
}

void get_lcp() {
    int i, j, k = 0;
    for (i = 1; i <= n; i++) rk[sa[i]] = i;
    for (i = 1; i <= n; i++) {
        if (rk[i] == 1) continue;
        if (k) k--;
        j = sa[rk[i] - 1];
        while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k++;
        lcp[rk[i]] = k;
    }
}

void init_st() {
    int i, j;
    for (i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
    for (i = 1; i <= n; i++) st[i][0] = lcp[i];
    for (j = 1; (1 << j) <= n; j++)
        for (i = 1; i + (1 << j) - 1 <= n; i++)
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
}

int query(int l, int r) {
    int k = lg[r - l + 1];
    return min(st[l][k], st[r - (1 << k) + 1][k]);
}

int lcp_query(int a, int b) {
    if (a == b) return n - a + 1;
    a = rk[a], b = rk[b];
    if (a > b) {
        int t = a; a = b; b = t;
    }
    return query(a + 1, b);
}

int main() {
    scanf("%d%d", &n, &m);
    scanf("%s", s + 1);
    get_sa();
    get_lcp();
    init_st();
    
    int a, b, c, d;
    while (m--) {
        scanf("%d%d%d%d", &a, &b, &c, &d);
        int ans = 0;
        for (int i = a; i <= b; i++) {
            ans = max(ans, min(b - i + 1, lcp_query(i, c)));
        }
        printf("%d\n", ans);
    }
    return 0;
}