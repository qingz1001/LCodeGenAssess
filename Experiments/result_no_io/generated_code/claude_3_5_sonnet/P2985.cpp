#include <stdio.h>
#include <stdlib.h>

#define MAXN 50005
#define MAXD 50005

int n, d;
int h[MAXN];
int ans[MAXN];
long long sum[MAXN];

int check(long long x) {
    int cur = 1;
    long long happy = 0;
    
    for (int i = 1; i <= n; i++) {
        if (happy < x) {
            if (cur > d) return 0;
            happy = (happy >> 1) + sum[i] - sum[i-1];
            ans[i] = cur++;
        } else {
            happy >>= 1;
            ans[i] = cur;
        }
    }
    
    return happy >= x;
}

int main() {
    scanf("%d %d", &n, &d);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &h[i]);
        sum[i] = sum[i-1] + h[i];
    }
    
    long long l = 0, r = sum[n], mid;
    while (l < r) {
        mid = (l + r + 1) >> 1;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    
    check(l);
    
    printf("%lld\n", l);
    for (int i = 1; i <= n; i++) {
        printf("%d\n", ans[i]);
    }
    
    return 0;
}