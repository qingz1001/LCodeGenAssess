#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 20001
#define MAXM 1000001

int n, k;
int a[MAXN];
int sa[MAXN], rk[MAXN], tmp[MAXN], lcp[MAXN];
int cnt[MAXM], x[MAXN], y[MAXN];

void radix_sort(int *s, int *a, int *b, int n, int m) {
    for (int i = 0; i <= m; i++) cnt[i] = 0;
    for (int i = 0; i < n; i++) cnt[s[a[i]]]++;
    for (int i = 1; i <= m; i++) cnt[i] += cnt[i-1];
    for (int i = n-1; i >= 0; i--) b[--cnt[s[a[i]]]] = a[i];
}

void suffix_array() {
    int m = MAXM - 1;
    int *x = rk, *y = tmp;
    for (int i = 0; i < n; i++) x[i] = a[i], y[i] = i;
    radix_sort(x, y, sa, n, m);
    for (int k = 1, p = 0; k <= n; k <<= 1, m = p) {
        p = 0;
        for (int i = n-k; i < n; i++) y[p++] = i;
        for (int i = 0; i < n; i++) if (sa[i] >= k) y[p++] = sa[i] - k;
        radix_sort(x, y, sa, n, m);
        int *t = x; x = y; y = t;
        x[sa[0]] = 0; p = 1;
        for (int i = 1; i < n; i++)
            x[sa[i]] = (y[sa[i-1]] == y[sa[i]] && y[sa[i-1]+k] == y[sa[i]+k]) ? p-1 : p++;
    }
    for (int i = 0; i < n; i++) rk[sa[i]] = i;
}

void lcp_array() {
    int h = 0;
    for (int i = 0; i < n; i++) {
        if (rk[i] == 0) continue;
        int j = sa[rk[i]-1];
        while (i+h < n && j+h < n && a[i+h] == a[j+h]) h++;
        lcp[rk[i]] = h;
        if (h > 0) h--;
    }
}

int check(int len) {
    int cnt = 1;
    for (int i = 1; i < n; i++) {
        if (lcp[i] >= len) {
            cnt++;
            if (cnt >= k) return 1;
        } else {
            cnt = 1;
        }
    }
    return 0;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    suffix_array();
    lcp_array();
    
    int left = 0, right = n, ans = 0;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (check(mid)) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    printf("%d\n", ans);
    return 0;
}