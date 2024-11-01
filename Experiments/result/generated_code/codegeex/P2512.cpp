#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int main() {
    int n;
    scanf("%d", &n);
    ll *a = (ll*)malloc(n * sizeof(ll));
    ll sum = 0, avg, ans = 0;
    
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
        sum += a[i];
    }
    
    avg = sum / n;
    
    for (int i = 0; i < n; i++) {
        a[i] -= avg;
    }
    
    for (int i = 1; i < n; i++) {
        a[i] += a[i - 1];
    }
    
    for (int i = 0; i < n; i++) {
        ans += abs(a[i]);
    }
    
    printf("%lld\n", ans);
    
    free(a);
    return 0;
}