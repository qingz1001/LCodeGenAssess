#include <stdio.h>

long long solve(long long n, int k) {
    if (n <= k) return 0;
    
    long long ans = 0;
    while (n > k) {
        long long next_n = (n + 1) / 2;
        ans += n - next_n;
        n = next_n;
    }
    return ans;
}

int main() {
    long long n;
    int k;
    scanf("%lld %d", &n, &k);
    
    long long result = solve(n, k);
    printf("%lld\n", result);
    
    return 0;
}