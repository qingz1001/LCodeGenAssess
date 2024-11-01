#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 35005
#define INF 0x3f3f3f3f

int n, a[MAXN], f[MAXN], g[MAXN], pre[MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    for (int i = 1; i <= n; i++) {
        int k = 0;
        for (int j = 0; j < i; j++) {
            if (a[i] > a[j] && f[i] > f[j]) {
                f[i] = f[j];
                k = j;
            }
        }
        f[i]++;
        pre[i] = k;
    }
    
    int ans = INF, pos = 0;
    for (int i = 1; i <= n; i++) {
        if (ans > f[i]) {
            ans = f[i];
            pos = i;
        }
    }
    
    printf("%d\n", n - ans);
    
    memset(g, 0, sizeof(g));
    for (int i = pos, j = a[pos]; i; i = pre[i]) {
        if (a[i] < j) {
            g[i] = j - a[i];
        }
        j = a[i] + g[i];
    }
    
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += g[i];
    }
    
    printf("%lld\n", sum);
    
    return 0;
}