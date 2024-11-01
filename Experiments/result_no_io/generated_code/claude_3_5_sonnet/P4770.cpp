#include <stdio.h>
#include <string.h>

#define MAXN 500005
#define MOD 1000000007

char S[MAXN], T[MAXN];
int sa[MAXN], rk[MAXN], tmp[MAXN], lcp[MAXN];
int n, m, k;
int cnt[MAXN], sum[MAXN], last[MAXN];

void get_sa() {
    int i, j, p;
    m = 128;
    n = strlen(S);
    for (i = 0; i < m; i++) cnt[i] = 0;
    for (i = 0; i < n; i++) cnt[S[i]]++;
    for (i = 1; i < m; i++) cnt[i] += cnt[i-1];
    for (i = n-1; i >= 0; i--) sa[--cnt[S[i]]] = i;
    rk[sa[0]] = p = 0;
    for (i = 1; i < n; i++) {
        if (S[sa[i]] != S[sa[i-1]]) p++;
        rk[sa[i]] = p;
    }
    for (k = 1; k <= n && p < n-1; k <<= 1) {
        for (i = 0; i < n; i++) cnt[rk[i]] = 0;
        for (i = 0; i < n; i++) cnt[rk[i]]++;
        for (i = 1; i < n; i++) cnt[i] += cnt[i-1];
        for (i = n-1; i >= 0; i--) {
            j = sa[i] - k;
            if (j < 0) j += n;
            tmp[--cnt[rk[j]]] = j;
        }
        for (i = 0; i < n; i++) sa[i] = tmp[i];
        tmp[sa[0]] = p = 0;
        for (i = 1; i < n; i++) {
            if (rk[sa[i]] != rk[sa[i-1]] || rk[(sa[i]+k)%n] != rk[(sa[i-1]+k)%n]) p++;
            tmp[sa[i]] = p;
        }
        for (i = 0; i < n; i++) rk[i] = tmp[i];
    }
}

void get_lcp() {
    int i, j, h = 0;
    for (i = 0; i < n; i++) rk[sa[i]] = i;
    for (i = 0; i < n; i++) {
        if (rk[i] == 0) continue;
        j = sa[rk[i]-1];
        while (S[i+h] == S[j+h]) h++;
        lcp[rk[i]] = h;
        if (h > 0) h--;
    }
}

int main() {
    int Q, l, r, i, j, ans;
    scanf("%s", S);
    get_sa();
    get_lcp();
    
    scanf("%d", &Q);
    while (Q--) {
        scanf("%s%d%d", T, &l, &r);
        l--; r--;
        m = strlen(T);
        
        for (i = 0; i <= n; i++) sum[i] = 0;
        for (i = 0; i < m; i++) {
            for (j = 0; j < n; j++) {
                if (S[sa[j]+i] != T[i]) break;
                sum[j+1]++;
            }
        }
        for (i = 1; i <= n; i++) sum[i] += sum[i-1];
        
        memset(last, -1, sizeof(last));
        ans = 0;
        for (i = 0; i < n; i++) {
            if (sa[i] >= l && sa[i] <= r) {
                if (last[lcp[i]] == -1) last[lcp[i]] = i;
            } else {
                j = sum[i] - sum[last[lcp[i]] == -1 ? 0 : last[lcp[i]]];
                ans = (ans + j) % MOD;
            }
        }
        
        printf("%d\n", ans);
    }
    
    return 0;
}