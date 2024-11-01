#include <stdio.h>
#include <string.h>

#define MAX_N 1000005
#define MOD 19930726

char s[MAX_N];
int n, K;
long long ans = 1;
int cnt = 0, len[MAX_N];

void manacher() {
    static char t[MAX_N * 2];
    static int p[MAX_N * 2];
    int m = 0;
    t[m++] = '$';
    t[m++] = '#';
    for (int i = 0; i < n; i++) {
        t[m++] = s[i];
        t[m++] = '#';
    }
    t[m] = 0;
    
    int mx = 0, id = 0;
    for (int i = 0; i < m; i++) {
        p[i] = mx > i ? (mx - i < p[2 * id - i] ? mx - i : p[2 * id - i]) : 1;
        while (t[i + p[i]] == t[i - p[i]]) p[i]++;
        if (i + p[i] > mx) {
            mx = i + p[i];
            id = i;
        }
        if (i % 2 == 0 && p[i] > 1) {
            len[cnt++] = p[i] - 1;
        }
    }
}

int cmp(const void *a, const void *b) {
    return *(int*)b - *(int*)a;
}

int main() {
    scanf("%d %d", &n, &K);
    scanf("%s", s);
    
    manacher();
    
    qsort(len, cnt, sizeof(int), cmp);
    
    if (cnt < K) {
        printf("-1\n");
        return 0;
    }
    
    for (int i = 0; i < K; i++) {
        ans = (ans * len[i]) % MOD;
    }
    
    printf("%lld\n", ans);
    
    return 0;
}