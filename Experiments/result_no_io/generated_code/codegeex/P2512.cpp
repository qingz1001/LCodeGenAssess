#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    long long a[1000005];
    long long sum = 0, avg, ans = 0;
    
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
        sum += a[i];
    }
    
    avg = sum / n;
    
    for (int i = 0; i < n; i++) {
        a[i] -= avg;
    }
    
    long long total = 0;
    for (int i = 0; i < n; i++) {
        total += a[i];
        ans += abs(total);
    }
    
    printf("%lld\n", ans);
    
    return 0;
}