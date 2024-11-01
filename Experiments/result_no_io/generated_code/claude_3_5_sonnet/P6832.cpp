#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 10000001

char S[MAX_N];
int sa[MAX_N], rk[MAX_N], tmp[MAX_N], lcp[MAX_N];
int n, k;

void countSort() {
    static int cnt[MAX_N];
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++) cnt[rk[i]]++;
    for (int i = 1; i < k; i++) cnt[i] += cnt[i-1];
    for (int i = n-1; i >= 0; i--) sa[--cnt[rk[tmp[i]]]] = tmp[i];
}

void buildSA() {
    for (int i = 0; i < n; i++) {
        sa[i] = i;
        rk[i] = S[i];
    }
    for (k = 1; k <= n; k <<= 1) {
        for (int i = 0; i < n; i++) {
            tmp[i] = sa[i];
            sa[i] = i;
        }
        countSort();
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            tmp[sa[i]] = tmp[sa[i-1]] + (rk[sa[i]] != rk[sa[i-1]] || rk[sa[i]+k] != rk[sa[i-1]+k]);
        }
        memcpy(rk, tmp, n * sizeof(int));
        if (rk[sa[n-1]] == n-1) break;
    }
}

void buildLCP() {
    for (int i = 0, k = 0; i < n - 1; i++) {
        if (k) k--;
        while (S[i+k] == S[sa[rk[i]-1]+k]) k++;
        lcp[rk[i]] = k;
    }
}

int main() {
    scanf("%s", S);
    n = strlen(S);
    buildSA();
    buildLCP();
    
    int ans = 1;
    for (int i = 1; i < n; i++) {
        ans = (lcp[i] > ans) ? lcp[i] : ans;
    }
    
    printf("%d\n", ans);
    return 0;
}