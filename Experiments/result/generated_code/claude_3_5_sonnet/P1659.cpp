#include <stdio.h>
#include <string.h>
#define MAX_N 1000005
#define MOD 19930726

char s[MAX_N];
int n, K;
long long ans = 1;
int cnt[MAX_N], len[MAX_N], tot;

void manacher() {
    int mx = 0, id = 0;
    for (int i = 0; i < n; i++) {
        cnt[i] = i < mx ? (cnt[2 * id - i] < mx - i ? cnt[2 * id - i] : mx - i) : 1;
        while (i - cnt[i] >= 0 && i + cnt[i] < n && s[i - cnt[i]] == s[i + cnt[i]]) cnt[i]++;
        if (i + cnt[i] > mx) {
            mx = i + cnt[i];
            id = i;
        }
    }
}

int cmp(const void *a, const void *b) {
    return *(int*)b - *(int*)a;
}

int main() {
    scanf("%d%d", &n, &K);
    scanf("%s", s);
    
    manacher();
    
    for (int i = 0; i < n; i++) {
        if (cnt[i] > 1) {
            len[tot++] = cnt[i] * 2 - 1;
        }
    }
    
    qsort(len, tot, sizeof(int), cmp);
    
    if (tot < K) {
        printf("-1\n");
        return 0;
    }
    
    for (int i = 0; i < K; i++) {
        ans = (ans * len[i]) % MOD;
    }
    
    printf("%lld\n", ans);
    
    return 0;
}