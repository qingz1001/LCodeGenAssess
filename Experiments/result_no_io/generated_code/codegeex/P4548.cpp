#include <stdio.h>
#include <string.h>

#define MOD 10000
#define MAXN 100005

int n, t;
int nxt[MAXN];
long long ans;

void kmp_pre(char *p, int m) {
    int j = 0;
    nxt[0] = -1;
    for (int i = 1; i < m; i++) {
        while (j >= 0 && p[j] != p[i]) j = nxt[j];
        nxt[i] = ++j;
    }
}

void kmp_calc(char *p, int m) {
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j >= 0 && p[j] != i + 1) j = nxt[j];
        j++;
        if (j == m) {
            ans = (ans + i - m + 2) % MOD;
            j = nxt[j];
        }
    }
}

int main() {
    scanf("%d%d", &n, &t);
    while (t--) {
        int m;
        char p[MAXN];
        scanf("%d", &m);
        for (int i = 0; i < m; i++) scanf("%d", &p[i]);
        ans = 0;
        kmp_pre(p, m);
        kmp_calc(p, m);
        printf("%04lld\n", ans);
    }
    return 0;
}