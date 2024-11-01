#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 10000001

char s[MAX_LEN];
int sa[MAX_LEN], rk[MAX_LEN], tmp[MAX_LEN], lcp[MAX_LEN];

void get_sa(int n, int m) {
    int i, j, p;
    for (i = 0; i < n; i++) rk[i] = s[i], sa[i] = i;
    for (j = 1; j <= n; j <<= 1) {
        p = 0;
        for (i = n - j; i < n; i++) tmp[p++] = i;
        for (i = 0; i < n; i++) if (sa[i] >= j) tmp[p++] = sa[i] - j;
        memset(sa, 0, sizeof(int) * m);
        for (i = 0; i < n; i++) sa[rk[tmp[i]]]++;
        for (i = 1; i < m; i++) sa[i] += sa[i - 1];
        for (i = n - 1; i >= 0; i--) sa[--sa[rk[tmp[i]]]] = tmp[i];
        memcpy(tmp, rk, sizeof(int) * n);
        p = 1; rk[sa[0]] = 0;
        for (i = 1; i < n; i++)
            rk[sa[i]] = tmp[sa[i - 1]] == tmp[sa[i]] && tmp[sa[i - 1] + j] == tmp[sa[i] + j] ? p - 1 : p++;
        if (p >= n) break;
        m = p;
    }
}

void get_lcp(int n) {
    int i, j, k = 0;
    for (i = 0; i < n; i++) rk[sa[i]] = i;
    for (i = 0; i < n; i++) {
        if (k) k--;
        if (!rk[i]) continue;
        j = sa[rk[i] - 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
        lcp[rk[i]] = k;
    }
}

int main() {
    scanf("%s", s);
    int n = strlen(s);
    get_sa(n + 1, 128);
    get_lcp(n);
    
    int ans = 1;
    for (int i = 1; i <= n; i++) {
        ans = (lcp[i] > ans) ? lcp[i] : ans;
    }
    
    printf("%d\n", ans);
    return 0;
}