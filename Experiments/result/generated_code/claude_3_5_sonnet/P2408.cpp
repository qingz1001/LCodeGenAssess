#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 100005

char s[MAX_N];
int n;
int sa[MAX_N], rk[MAX_N], tmp[MAX_N], lcp[MAX_N];

void get_sa() {
    int i, j, k;
    int m = 128;
    
    memset(rk, 0, sizeof(rk));
    for (i = 0; i < n; i++) sa[i] = i, rk[i] = s[i];
    for (k = 1; k <= n; k <<= 1) {
        int p = 0;
        for (i = n - k; i < n; i++) tmp[p++] = i;
        for (i = 0; i < n; i++) if (sa[i] >= k) tmp[p++] = sa[i] - k;
        
        memset(sa, 0, sizeof(sa));
        for (i = 0; i < n; i++) sa[rk[tmp[i]]]++;
        for (i = 1; i < m; i++) sa[i] += sa[i-1];
        for (i = n-1; i >= 0; i--) sa[--sa[rk[tmp[i]]]] = tmp[i];
        
        memcpy(tmp, rk, sizeof(rk));
        p = 1; rk[sa[0]] = 0;
        for (i = 1; i < n; i++)
            rk[sa[i]] = (tmp[sa[i]] == tmp[sa[i-1]] && tmp[sa[i]+k] == tmp[sa[i-1]+k]) ? p-1 : p++;
        if (p >= n) break;
        m = p;
    }
}

void get_lcp() {
    int i, j, k = 0;
    for (i = 0; i < n - 1; i++) {
        j = sa[rk[i] - 1];
        while (s[i + k] == s[j + k]) k++;
        lcp[rk[i]] = k;
        if (k) k--;
    }
}

int main() {
    scanf("%d", &n);
    scanf("%s", s);
    
    get_sa();
    get_lcp();
    
    long long ans = (long long)n * (n + 1) / 2;
    for (int i = 1; i < n; i++) {
        ans -= lcp[i];
    }
    
    printf("%lld\n", ans);
    
    return 0;
}