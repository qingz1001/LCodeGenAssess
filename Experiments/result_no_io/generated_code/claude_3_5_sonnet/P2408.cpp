#include <stdio.h>
#include <string.h>

#define MAX_N 100005

char s[MAX_N];
int sa[MAX_N], rk[MAX_N], tmp[MAX_N], lcp[MAX_N];
int n;

void build_sa(int m) {
    int i, j, p, *x = rk, *y = tmp;
    for (i = 0; i < m; i++) tmp[i] = 0;
    for (i = 0; i < n; i++) tmp[x[i] = s[i]]++;
    for (i = 1; i < m; i++) tmp[i] += tmp[i-1];
    for (i = n-1; i >= 0; i--) sa[--tmp[x[i]]] = i;
    for (j = 1, p = 1; p < n; j *= 2, m = p) {
        for (p = 0, i = n-j; i < n; i++) y[p++] = i;
        for (i = 0; i < n; i++) if (sa[i] >= j) y[p++] = sa[i] - j;
        for (i = 0; i < m; i++) tmp[i] = 0;
        for (i = 0; i < n; i++) tmp[x[y[i]]]++;
        for (i = 1; i < m; i++) tmp[i] += tmp[i-1];
        for (i = n-1; i >= 0; i--) sa[--tmp[x[y[i]]]] = y[i];
        for (tmp[sa[0]] = 0, i = 1, p = 1; i < n; i++)
            y[sa[i]] = (x[sa[i]] == x[sa[i-1]] && x[sa[i]+j] == x[sa[i-1]+j]) ? p-1 : p++;
        int *t = x; x = y; y = t;
    }
    for (i = 0; i < n; i++) rk[sa[i]] = i;
}

void build_lcp() {
    int i, j, k = 0;
    for (i = 0; i < n-1; i++) {
        j = sa[rk[i] - 1];
        while (s[i+k] == s[j+k]) k++;
        lcp[rk[i]] = k;
        if (k) k--;
    }
}

int main() {
    scanf("%d", &n);
    scanf("%s", s);
    
    build_sa(128);
    build_lcp();
    
    long long result = (long long)n * (n + 1) / 2;
    for (int i = 1; i < n; i++) {
        result -= lcp[i];
    }
    
    printf("%lld\n", result);
    
    return 0;
}