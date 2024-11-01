#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 40005
#define MAXQ 100005
#define MAXLEN 10005

char s[MAXN][MAXLEN];
int n, q;
int len[MAXN];
int lcp[MAXN][MAXN];
int nxt[MAXN];
int pre[MAXN];
int pos[MAXN];
int x[MAXQ], y[MAXQ];
int cnt[MAXQ];
int ans[MAXN];
int task[MAXQ];
int task_cnt;

int calc_lcp(int i, int j) {
    int k = 0;
    while (k < len[i] && k < len[j] && s[i][k] == s[j][k]) k++;
    return k;
}

void init() {
    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n; j++) {
            lcp[i][j] = lcp[j][i] = calc_lcp(i, j);
        }
    }
}

long long solve() {
    long long res = 0;
    for (int i = 1; i <= n; i++) {
        nxt[i] = i+1;
        pre[i] = i-1;
    }
    nxt[n] = 0;
    pre[1] = 0;
    
    int cur = 1;
    for (int i = 2; i <= n; i++) {
        int best = 0, bestj = 0;
        for (int j = cur; j; j = nxt[j]) {
            int v = lcp[j][i];
            if (v > best) {
                best = v;
                bestj = j;
            }
        }
        res += (long long)best * best;
        
        nxt[pre[bestj]] = nxt[bestj];
        pre[nxt[bestj]] = pre[bestj];
        nxt[i] = nxt[bestj];
        pre[i] = bestj;
        nxt[bestj] = i;
        pre[nxt[i]] = i;
        
        if (bestj == cur) cur = i;
    }
    
    int p = 0;
    for (int i = cur; i; i = nxt[i]) {
        pos[i] = ++p;
        ans[p] = i;
    }
    
    return res;
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%s", s[i]);
        len[i] = strlen(s[i]);
    }
    for (int i = 1; i <= q; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }
    
    init();
    long long max_value = solve();
    
    for (int i = 1; i <= q; i++) {
        if (pos[x[i]] + 1 == pos[y[i]]) {
            task[++task_cnt] = i;
        }
    }
    
    printf("%lld\n", max_value);
    printf("%d", task_cnt);
    for (int i = 1; i <= task_cnt; i++) {
        printf(" %d", task[i]);
    }
    printf("\n");
    for (int i = 1; i <= n; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    
    return 0;
}